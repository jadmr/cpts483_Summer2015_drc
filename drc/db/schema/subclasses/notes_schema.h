#ifndef NOTES_SCHEMA
#define NOTES_SCHEMA

#include "db_schema.h"

class NotesSchema : public DatabaseSchema
{
public:

    NotesSchema();

#define OVERRIDES_OF_BASE {
    void initializeHeaders();
    void initializeColumnTypes();
#define OVERRIDES_OF_BASE }

};

#endif // NOTES_SCHEMA

