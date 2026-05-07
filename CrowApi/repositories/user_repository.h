#pragma once

#include <soci/soci.h>

#include <optional>
#include <string>

#include "../types/app_types.h"
#include "db_connection.h"

namespace UserRepository {

static std::optional<User> findByEmail(const std::string& email) {
    auto sql = DbFactory::connect();
    soci::row row;
    soci::statement st =
        (sql.prepare << "select id, name, email, password from users where email = :id",
         soci::use(email), soci::into(row));

    if (!st.execute(true)) {
        return std::nullopt;
    }

    return User{row.get<int>(0), row.get<std::string>(1), row.get<std::string>(2),
                row.get<std::string>(3)};
}

static const User& save(const User& user) { return user; }
}  // namespace UserRepository
