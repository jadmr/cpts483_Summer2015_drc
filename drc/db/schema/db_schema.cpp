#include "db_schema.h"

// Constructor
DatabaseSchema::DatabaseSchema()
{

}

#define SETTER_GETTER_METHODS {

void DatabaseSchema::setTableName(QString tableName)
{
    this->tableName = tableName;
}

void DatabaseSchema::setHeader(QVector<QString> headers)
{
    this->headers = headers;
}

void DatabaseSchema::setColumnType(QVector<RECORD_TYPE> columnType)
{
    this->columnType = columnType;
}

QString DatabaseSchema::getTableName() const
{
    return tableName;
}

QVector<QString> DatabaseSchema::getHeader() const
{
    return headers;
}

QVector<RECORD_TYPE> DatabaseSchema::getColumnType() const
{
    return columnType;
}

QString DatabaseSchema::getPrimaryID() const
{
    return headers[0];
}

#define SETTER_GETTER_METHODS }
