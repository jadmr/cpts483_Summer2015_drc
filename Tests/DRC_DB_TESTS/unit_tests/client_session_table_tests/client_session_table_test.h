#ifndef CLIENT_SESSION_TABLE_TEST_H
#define CLIENT_SESSION_TABLE_TEST_H

#include "db_test_base.h"

class CLIENT_SESSION_TABLE_TEST : public DB_TEST_BASE
{
    Q_OBJECT
public:
    CLIENT_SESSION_TABLE_TEST();

private Q_SLOTS:

    void CheckCreateClientSessionTable();
    void CheckClientSessionColumn();
    void CheckInsertEmptyClientSessionObject();
    void CheckInsertFullClientSessionObject();

protected slots:

    void initTestCase();
    void cleanupTestCase();
};

#endif // CLIENT_SESSION_TABLE_TEST_H

