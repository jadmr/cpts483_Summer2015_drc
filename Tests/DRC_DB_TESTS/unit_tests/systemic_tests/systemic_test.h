#ifndef SYSTEMIC_TEST_H
#define SYSTEMIC_TEST_H

#include "db_test_base.h"

class SYSTEMIC_TEST : public DB_TEST_BASE
{
    Q_OBJECT

public:
    SYSTEMIC_TEST();

private Q_SLOTS:

    void CheckInsertEntireMediationObject();

protected slots:

    void initTestCase();
    void cleanupTestCase();
};

#endif // SYSTEMIC_TEST_H

