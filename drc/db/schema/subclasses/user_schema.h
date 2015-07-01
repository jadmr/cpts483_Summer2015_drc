#ifndef USER_SCHEMA
#define USER_SCHEMA

#include "db_schema.h"

class UserSchema : public DatabaseSchema
{
public:

    UserSchema();

#define OVERRIDES_OF_BASE {
    void initializeHeaders();
    void initializeColumnTypes();
#define OVERRIDES_OF_BASE }

};

#endif // USER_SCHEMA

