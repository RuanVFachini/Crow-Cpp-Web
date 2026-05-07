// CrowApi.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "crow.h"
#include "middlewares/auth_middleware.h"
#include "routes/auth_routes.h"
#include "routes/todo_routes.h"
#include "types/app_types.h"

int main(int argc, char** array) {
    std::vector<Todo> todos = {};

    crow::logger::setLogLevel(crow::LogLevel::Debug);

    APP app;

    registerTodoRoutes(app, todos);
    registerAuthRoutes(app);

    // CROW_ROUTE(app, "/")([]() {
    //     auto page = crow::mustache::load_text("index.html");

    //     return page;
    // });

    app.port(18080).multithreaded().run();

    return 0;
}
