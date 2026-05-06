// CrowApi.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "crow.h"
#include "routes/todo_routes.h"

int main(int argc, char** array) {
    std::vector<Todo> todos = {};

    crow::SimpleApp app;

    registerTodoRoutes(app, todos);

    CROW_ROUTE(app, "/")([]() {
        auto page = crow::mustache::load_text("index.html");

        return page;
    });

    app.port(18080).multithreaded().run();

    return 0;
}
