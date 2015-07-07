#ifndef EVALUATION_SCHEMA
#define EVALUATION_SCHEMA

#include "db_schema.h"

class EvaluationSchema : public DatabaseSchema
{
public:

    EvaluationSchema();

#define OVERRIDES_OF_BASE {
    void initializeHeaders();
    void initializeColumnTypes();
#define OVERRIDES_OF_BASE }

};

#endif // EVALUATION_SCHEMA

