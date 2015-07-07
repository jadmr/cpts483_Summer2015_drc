#ifndef SESSION_SCHEMA
#define SESSION_SCHEMA

#include "db_schema.h"

class SessionSchema : public DatabaseSchema
{
public:

    SessionSchema();

#define OVERRIDES_OF_BASE {
    void initializeHeaders();
    void initializeColumnTypes();
#define OVERRIDES_OF_BASE }

};

#endif // SESSION_SCHEMA

