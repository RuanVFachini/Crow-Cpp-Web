#include "DbFactory.h"

std::unique_ptr<soci::connection_pool> DbFactory::pool;

void DbFactory::init(int size) {
    pool = std::make_unique<soci::connection_pool>(size);

    for (int i = 0; i < size; i++) {
        soci::session& sql = pool->at(i);
        sql.open(soci::postgresql, CONNECTION_STRING);
    }
}

soci::session DbFactory::acquire() { return soci::session(*pool); }
