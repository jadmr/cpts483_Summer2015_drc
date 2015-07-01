#ifndef MEDIATION_SCHEMA
#define MEDIATION_SCHEMA

#include "db_schema.h"

class MediationSchema : public DatabaseSchema
{
public:

    MediationSchema();

#define OVERRIDES_OF_BASE {
    void initializeHeaders();
    void initializeColumnTypes();
#define OVERRIDES_OF_BASE }

};

#endif // MEDIATION_SCHEMA

