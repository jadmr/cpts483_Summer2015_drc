#ifndef DB_SCHEMA
#define DB_SCHEMA

#include <QVector>
#include <QString>

#include "rec_type.h"

/*
 * Abstract class that contains metadata about the database
 * TODO: replace headers this with sql calls (maybe)
 */

class DatabaseSchema
{

public:

    DatabaseSchema();

#define SETTER_GETTER_METHODS {
    void setHeader(QVector<QString>);
    void setColumnType(QVector<RECORD_TYPE>);

    QVector<QString> getHeader() const;
    QVector<RECORD_TYPE> getColumnType() const;
#define SETTER_GETTER_METHODS }

protected:

#define PROTECTED_VARIABLES {
    QVector<QString> headers;
    QVector<RECORD_TYPE> columnType;
#define PROTECTED_VARIABLES }

#define INITIALIZATION_METHODS {
    virtual void initializeHeaders() = 0;
    virtual void initializeColumnTypes() = 0;
#define INITIALIZATION_METHODS }

};

#endif // DB_SCHEMA
