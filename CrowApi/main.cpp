// CrowApi.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "crow.h"

struct Todo {
    int id;
    std::string description;
    bool completed;

    static Todo fromJson(crow::json::rvalue $body, int id) {
        return Todo{id, $body["description"].s(), false};
    }

    crow::json::wvalue toJson() const {
        crow::json::wvalue item;
        item["id"] = this->id;
        item["description"] = this->description;
        item["completed"] = this->completed;

        return item;
    }
};

int main(int argc, char** array) {
    std::vector<Todo> todos = {};

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        auto page = crow::mustache::load_text("index.html");

        return page;
    });

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

    app.port(18080).multithreaded().run();

    return 0;
}
