#pragma once

#define APP crow::App<AuthMiddleware>

struct User {
    int id;
    std::string name;
    std::string email;
    std::string password;

    static User fromJson(crow::json::rvalue $body, int id) {
        return User{id, $body["name"].s(), $body["email"].s(), $body["password"].s()};
    }

    crow::json::wvalue toJson() const {
        crow::json::wvalue item;
        item["id"] = this->id;
        item["name"] = this->name;
        item["email"] = this->email;
        item["password"] = this->password;

        return item;
    }
};

struct Login {
    std::string email;
    std::string password;

    static Login fromJson(crow::json::rvalue $body) {
        return Login{$body["email"].s(), $body["password"].s()};
    }
};

struct Token {
    std::string access_token;

    crow::json::wvalue toJson() const {
        crow::json::wvalue item;
        item["access_token"] = this->access_token;

        return item;
    }
};

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
