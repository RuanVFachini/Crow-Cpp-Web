// CrowApi.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "crow.h"

int main(int argc, char **array)
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([](){
		auto page = crow::mustache::load_text("index.html");

		return page;
		});

	CROW_ROUTE(app, "/api/todos")
	 	.methods("POST"_method)([](
		const crow::request& req){

		 auto x = crow::json::load(req.body);
          if (!x)
              return crow::response(400);

		 crow::json::wvalue res;
		 res["mensagem"] = "Olá";

		return crow::response(200, res);
	});

	app.port(18080)
		.multithreaded()
		.run();

	return 0;
}