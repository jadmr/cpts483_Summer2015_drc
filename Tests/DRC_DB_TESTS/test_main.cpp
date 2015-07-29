#include <QtTest>

#include "client_session_table_tests/client_session_table_test.h"
#include "client_table_tests/client_table_test.h"
#include "database_setup_tests/database_setup_test.h"
#include "evaluation_table_tests/evaluation_table_test.h"
#include "mediation_table_tests/mediation_table_test.h"
#include "notes_table_tests/notes_table_test.h"
#include "person_table_tests/person_table_test.h"
#include "session_table_tests/session_table_test.h"
#include "systemic_tests/systemic_test.h"

int main(int argc, char *argv[])
{
    int status = 0;
    auto ASSERT_TEST = [&status, argc, argv](QObject* obj)
                       {
                           status |= QTest::qExec(obj, argc, argv);
                           delete obj;
                       };

    ASSERT_TEST(new CLIENT_SESSION_TABLE_TEST());
    ASSERT_TEST(new CLIENT_TABLE_TEST());
    ASSERT_TEST(new DATABASE_SETUP_TEST());
    ASSERT_TEST(new EVALUATION_TABLE_TEST());
    ASSERT_TEST(new MEDIATION_TABLE_TEST());
    ASSERT_TEST(new NOTES_TABLE_TEST());
    ASSERT_TEST(new PERSON_TABLE_TEST());
    ASSERT_TEST(new SESSION_TABLE_TEST());
    ASSERT_TEST(new SYSTEMIC_TEST());

    return status;
}
