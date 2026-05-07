#pragma once
#include <soci/postgresql/soci-postgresql.h>
#include <soci/soci.h>

#define CONNECTION_STRING "dbname=postgres user=postgres password=postgres host=localhost port=5432"

class DbFactory {
   private:
    static std::unique_ptr<soci::connection_pool> pool;

   public:
    static void init(int size);
    static soci::session acquire();
};
