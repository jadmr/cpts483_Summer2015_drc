#ifndef CLIENT_TABLE_TEST_H
#define CLIENT_TABLE_TEST_H

#include "db_test_base.h"

class CLIENT_TABLE_TEST : public DB_TEST_BASE
{
    Q_OBJECT

public:
    CLIENT_TABLE_TEST();

private Q_SLOTS:

    void CheckCreateClientTable();
    void CheckClientColumn();
    void CheckInsertEmptyClientObject();
    void CheckInsertFullClientObject();

protected slots:

    void initTestCase();
    void cleanupTestCase();
};

#endif // CLIENT_TABLE_TEST_H

