#include "user_schema.h"


UserSchema::UserSchema() : DatabaseSchema()
{
    setTableName("User_Table");

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

    userColumnType.append(PRIMARY_ID);
    userColumnType.append(USER_NAME);
    userColumnType.append(PASSWORD);
    userColumnType.append(ADMIN_BOOL);

    setColumnType(userColumnType);
}

#define OVERRIDES_OF_BASE }
