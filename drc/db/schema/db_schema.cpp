#include "db_schema.h"

// Constructor
DatabaseSchema::DatabaseSchema()
{

}

#define SETTER_GETTER_METHODS {

void DatabaseSchema::setHeader(QVector<QString> headers)
{
    this->headers = headers;
}

void DatabaseSchema::setColumnType(QVector<RECORD_TYPE> columnType)
{
    this->columnType = columnType;
}

QVector<QString> DatabaseSchema::getHeader() const
{
    return headers;
}

QVector<RECORD_TYPE> DatabaseSchema::getColumnType() const
{
    return columnType;
}

#define SETTER_GETTER_METHODS }
