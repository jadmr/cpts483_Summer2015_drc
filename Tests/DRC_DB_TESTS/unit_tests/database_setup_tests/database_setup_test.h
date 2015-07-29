#ifndef DATABASE_SETUP_TEST_H
#define DATABASE_SETUP_TEST_H

#include "db_test_base.h"

class DATABASE_SETUP_TEST : public DB_TEST_BASE
{
    Q_OBJECT

public:
    DATABASE_SETUP_TEST();

private Q_SLOTS:

    void OpenDatabase();
    void CorrectDatabaseName();
    void ForeignKeysActive();

protected slots:

    void initTestCase();
    void cleanupTestCase();
};

#endif // DATABASE_SETUP_TEST_H

