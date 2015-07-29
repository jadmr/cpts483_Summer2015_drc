#ifndef NOTES_TABLE_TEST_H
#define NOTES_TABLE_TEST_H

#include "db_test_base.h"

class NOTES_TABLE_TEST : public DB_TEST_BASE
{
    Q_OBJECT

public:
    NOTES_TABLE_TEST();

private Q_SLOTS:

    void CheckCreateNotesTable();
    void CheckNotesColumn();
    void CheckInsertEmptyNoteObject();
    void CheckInsertFullNoteObject();

protected slots:

    void initTestCase();
    void cleanupTestCase();
};

#endif // NOTES_TABLE_TEST_H

