#pragma once

#include <soci/postgresql/soci-postgresql.h>
#include <soci/soci.h>

#define CONNECTION_STRING ""

namespace DbFactory {
static soci::session connect() {
    soci::session sql(soci::postgresql, CONNECTION_STRING);
    return sql;
}
}  // namespace DbFactory
