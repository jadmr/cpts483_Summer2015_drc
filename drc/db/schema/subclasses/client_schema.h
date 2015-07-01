#ifndef CLIENT_SCHEMA
#define CLIENT_SCHEMA

#include "db_schema.h"

class ClientSchema : public DatabaseSchema
{
public:

    ClientSchema();

protected:

#define OVERRIDES_OF_BASE {
    void initializeHeaders();
    void initializeColumnTypes();
#define OVERRIDES_OF_BASE }

};

#endif // CLIENT_SCHEMA

