#ifndef USER_TABLE_TEST_H
#define USER_TABLE_TEST_H

#include "db_test_base.h"

class USER_TABLE_TEST : public DB_TEST_BASE
{
    Q_OBJECT

public:

    USER_TABLE_TEST();

private Q_SLOTS:

    void CheckCreateUserTable();
    void CheckUserColumn();
    void CheckInsertEmptyUserObject();
    void CheckInsertFullUserObject();

protected slots:

    void initTestCase();
    void cleanupTestCase();
};

#endif // USER_TABLE_TEST_H

