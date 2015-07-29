#ifndef EVALUATION_TABLE_TEST_H
#define EVALUATION_TABLE_TEST_H

#include "db_test_base.h"

class EVALUATION_TABLE_TEST : public DB_TEST_BASE
{
    Q_OBJECT

public:
    EVALUATION_TABLE_TEST();

private Q_SLOTS:

    void CheckCreateEvaluationTable();
    void CheckEvaluationColumn();
    void CheckInsertEmptyEvaluationObject();
    void CheckInsertFullEvaluationObject();

protected slots:

    void initTestCase();
    void cleanupTestCase();
};

#endif // EVALUATION_TABLE_TEST_H

