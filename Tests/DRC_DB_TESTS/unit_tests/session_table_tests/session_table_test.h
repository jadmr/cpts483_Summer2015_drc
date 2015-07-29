#ifndef SESSION_TABLE_TEST_H
#define SESSION_TABLE_TEST_H

#include "db_test_base.h"

class SESSION_TABLE_TEST : public DB_TEST_BASE
{
    Q_OBJECT

public:
    SESSION_TABLE_TEST();

private Q_SLOTS:

    void CheckCreateSessionTable();
    void CheckSessionColumn();
    void CheckInsertEmptySessionObject();
    void CheckInsertFullSessionObject();

protected slots:

    void initTestCase();
    void cleanupTestCase();
};

#endif // SESSION_TABLE_TEST_H

