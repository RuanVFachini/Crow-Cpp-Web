#include "../types/app_types.h"

inline void registerTodoRoutes(APP& app, std::vector<Todo>& todos) {
    CROW_ROUTE(app, "/api/todos")
        .methods(crow::HTTPMethod::POST)([&todos](const crow::request& req) {
            auto data = crow::json::load(req.body);
            if (!data) return crow::response(400);

            long id = todos.size() + 1;
            auto todo = Todo::fromJson(data, (int)id);
            todos.push_back(todo);

            return crow::response(200, todo.toJson());
        });

    CROW_ROUTE(app, "/api/todos")([&todos](const crow::request& req) {
        crow::json::wvalue res;
        crow::json::wvalue::list lista;

        for (const auto& todo : todos) {
            lista.push_back(todo.toJson());
        }

        res["todos"] = std::move(lista);
        return crow::response(200, res);
    });

    CROW_ROUTE(app, "/api/todos/<int>/complete")
        .methods(crow::HTTPMethod::POST)([&todos](const crow::request& req, int id) {
            auto& todo = todos.at(id);
            todo.completed = true;

            return crow::response(200, todo.toJson());
        });
}
