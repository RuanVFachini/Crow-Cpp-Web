#include <optional>
#include <ranges>

#include "../auth/jwt_helper.h"
#include "../repositories/user_repository.h"
#include "../types/app_types.h"

inline void registerAuthRoutes(APP& app) {
    CROW_ROUTE(app, "/api/auth/register")
        .methods(crow::HTTPMethod::POST)([](const crow::request& req) {
            auto data = crow::json::load(req.body);
            if (!data) return crow::response(400);

            auto user = UserRepository::save(User::fromJson(data, 0));

            return crow::response(200, user.toJson());
        });

    CROW_ROUTE(app, "/api/auth/login")
        .methods(crow::HTTPMethod::POST)([](const crow::request& req) {
            auto data = crow::json::load(req.body);
            if (!data) return crow::response(400);

            auto login = Login::fromJson(data);
            auto user = UserRepository::findByEmail(login.email);

            if (!user || user->password != login.password) return crow::response(401);

            auto token = JwtHelper::createToken(user.value());

            return crow::response(200, Token{token}.toJson());
        });
}
