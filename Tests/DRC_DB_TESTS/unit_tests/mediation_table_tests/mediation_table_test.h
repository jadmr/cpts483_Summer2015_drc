#ifndef MEDIATION_TABLE_TEST_H
#define MEDIATION_TABLE_TEST_H

#include "db_test_base.h"

class MEDIATION_TABLE_TEST : public DB_TEST_BASE
{
    Q_OBJECT

public:
    MEDIATION_TABLE_TEST();

private Q_SLOTS:

    /*
     * These are called "process",
     * but they refer to "mediation_process"
     */

    void CheckCreateMediationTable();
    void CheckProcessColumn();
    void CheckInsertEmptyProcessObject();
    void CheckInsertFullProcessObject();

protected slots:

    void initTestCase();
    void cleanupTestCase();
};

#endif // MEDIATION_TABLE_TEST_H

