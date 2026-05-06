#include "../auth/jwt_helper.h"

struct AuthMiddleware {
    struct context {};

    void before_handle(crow::request& req, crow::response& res, context&) {
        try {
            if (req.url == "/login") return;

            auto auth = req.get_header_value("Authorization");

            if (auth.empty()) {
                res.code = 401;
                res.end("Unauthorized");
                return;
            }

            std::string prefix = SCHEMA;

            if (!auth.starts_with(prefix)) {
                res.code = 401;
                res.end("Unauthorized");
                return;
            }

            auto token = auth.substr(prefix.length(), auth.length() - prefix.length());
            auto result = JwtHelper::decodeToken(token);

            if (!result.success) {
                res.code = 401;
                res.end("Unauthorized");
                return;
            }

        } catch (const std::exception& e) {
            res.code = 401;
            res.end("Unauthorized");
            return;
        }
    }

    void after_handle(crow::request&, crow::response&, context&) {
        // opcional
    }
};
