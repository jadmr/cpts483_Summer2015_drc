#include "user_schema.h"


UserSchema::UserSchema() : DatabaseSchema()
{
    initializeHeaders();
    initializeColumnTypes();
}


#define OVERRIDES_OF_BASE {

void UserSchema::initializeHeaders()
{
    QVector<QString> userHeaders;

    userHeaders.append("user_id");
    userHeaders.append("user_name");
    userHeaders.append("user_password");
    userHeaders.append("Admin");

    setHeader(userHeaders);
}

void UserSchema::initializeColumnTypes()
{
    QVector<RECORD_TYPE> userColumnType;

    userColumnType.append(ID);
    userColumnType.append(STRING);
    userColumnType.append(STRING);
    userColumnType.append(BOOL);

    setColumnType(userColumnType);
}

#define OVERRIDES_OF_BASE }
