#ifndef PERSON_SCHEMA
#define PERSON_SCHEMA

#include "db_schema.h"

class PersonSchema : public DatabaseSchema
{
public:

    PersonSchema();

#define OVERRIDES_OF_BASE {
    void initializeHeaders();
    void initializeColumnTypes();
#define OVERRIDES_OF_BASE }

};

#endif // PERSON_SCHEMA

