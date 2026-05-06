#include <ranges>

#include "../auth/jwt_helper.h"
#include "../types/app_types.h"

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
            auto user = std::find_if(users.begin(), users.end(),
                                     [&](const User& u) { return u.email == login.email; });

            if (user == users.end()) return crow::response(401);

            auto token = JwtHelper::createToken(*user);

            return crow::response(200, Token{token}.toJson());
        });
}
