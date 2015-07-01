#ifndef CLIENT_SESSION_SCHEMA
#define CLIENT_SESSION_SCHEMA

#include "db_schema.h"

class ClientSessionSchema : public DatabaseSchema
{
public:

    ClientSessionSchema();

#define OVERRIDES_OF_BASE {
    void initializeHeaders();
    void initializeColumnTypes();
#define OVERRIDES_OF_BASE }

};

#endif // CLIENT_SESSION_SCHEMA

