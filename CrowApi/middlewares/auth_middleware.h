struct AuthMiddleware {
    struct context {};

    void before_handle(crow::request& req, crow::response& res, context&) {
        if (req.url == "/login") return;

        auto auth = req.get_header_value("Authorization");

        bool valid = false;

        if (auth.empty() || !valid) {
            res.code = 401;
            res.end("Unauthorized");
            return;
        }
    }

    void after_handle(crow::request&, crow::response&, context&) {
        // opcional
    }
};
