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
};

int main(int argc, char** array) {
    std::vector<Todo> todos = {};

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        auto page = crow::mustache::load_text("index.html");

        return page;
    });

    CROW_ROUTE(app, "/api/todos").methods("POST"_method)([&todos](const crow::request& req) {
        auto data = crow::json::load(req.body);
        if (!data) return crow::response(400);

        long id = todos.size() + 1;
        todos.push_back(Todo::fromJson(data, (int)id));

        crow::json::wvalue res;
        res["mensagem"] = "Olá";
        return crow::response(200, res);
    });

    CROW_ROUTE(app, "/api/todos")([&todos](const crow::request& req) {
        crow::json::wvalue res;
        crow::json::wvalue::list lista;

        for (const auto& todo : todos) {
            crow::json::wvalue item;
            item["id"] = todo.id;
            item["description"] = todo.description;
            item["completed"] = todo.completed;

            lista.push_back(item);
        }

        res["todos"] = std::move(lista);
        return crow::response(200, res);
    });

    app.port(18080).multithreaded().run();

    return 0;
}
