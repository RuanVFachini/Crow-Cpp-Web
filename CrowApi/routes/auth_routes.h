#include <jwt-cpp/jwt.h>

#include <ranges>

#include "../types/app_types.h"

#define JWT_TYPE "JWT"
#define JWT_ISSUER "my-app-issuer"
#define JWT_SECRET "a83c513180b98b28d68e45eec62c5343e08cd0b8d59041a4b2bd1e52c376161f"

struct User {
    int id;
    std::string name;
    std::string email;
    std::string password;

    static User fromJson(crow::json::rvalue $body, int id) {
        return User{id, $body["name"].s(), $body["email"].s(), $body["password"].s()};
    }

    crow::json::wvalue toJson() const {
        crow::json::wvalue item;
        item["id"] = this->id;
        item["name"] = this->name;
        item["email"] = this->email;
        item["password"] = this->password;

        return item;
    }
};

struct Login {
    std::string email;
    std::string password;

    static Login fromJson(crow::json::rvalue $body) {
        return Login{$body["email"].s(), $body["password"].s()};
    }
};

struct Token {
    std::string access_token;

    crow::json::wvalue toJson() const {
        crow::json::wvalue item;
        item["access_token"] = this->access_token;

        return item;
    }
};

inline void registerAuthRoutes(APP& app, std::vector<User>& users) {
    CROW_ROUTE(app, "/api/auth/register")
        .methods(crow::HTTPMethod::POST)([&users](const crow::request& req) {
            auto data = crow::json::load(req.body);
            if (!data) return crow::response(400);

            long id = users.size() + 1;
            auto user = User::fromJson(data, (int)id);
            users.push_back(user);

            return crow::response(200, user.toJson());
        });

    CROW_ROUTE(app, "/api/auth/login")
        .methods(crow::HTTPMethod::POST)([&users](const crow::request& req) {
            auto data = crow::json::load(req.body);
            if (!data) return crow::response(400);

            auto login = Login::fromJson(data);
            User* user = nullptr;

            auto size = (int)users.size();
            for (int i = 0; i < size; i++) {
                if (users.at(i).email == login.email) {
                    user = &users.at(i);
                }
            }

            if (user == nullptr) return crow::response(401);

            auto token = jwt::create()
                             .set_issuer(JWT_ISSUER)
                             .set_type(JWT_TYPE)
                             .set_issued_now()
                             .set_expires_in(std::chrono::seconds{36000})
                             .set_payload_claim("email", jwt::claim(user->email))
                             .sign(jwt::algorithm::hs256(JWT_SECRET));

            return crow::response(200, Token{token}.toJson());
        });
}
