#ifndef PERSON_TABLE_TEST_H
#define PERSON_TABLE_TEST_H

#include "db_test_base.h"

class PERSON_TABLE_TEST : public DB_TEST_BASE
{
    Q_OBJECT

public:
    PERSON_TABLE_TEST();

private Q_SLOTS:

    void CheckCreatePersonTable();
    void CheckPersonColumn();
    void CheckInsertEmptyPersonObject();
    void CheckInsertFullPersonObject();

protected slots:

    void initTestCase();
    void cleanupTestCase();
};

#endif // PERSON_TABLE_TEST_H

