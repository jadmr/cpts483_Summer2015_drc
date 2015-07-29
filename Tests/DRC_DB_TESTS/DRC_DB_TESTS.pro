#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T21:20:02
#
#-------------------------------------------------

QT       += sql testlib
QT       += widgets
QT       -= gui
QT       += printsupport

TARGET = tst_drc_db_tests
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += C++11

TEMPLATE = app

INCLUDEPATH += ../../drc/drc_shared/models/ \
    ../../drc/db/ \
    ../../drc/gui/ \
    ../../drc/drc_shared/mediator \
    ../../drc/bl/ \
    ../../drc/drc_shared/ \
    column_enumerations/ \
    unit_tests/ \
    ../../drc


SOURCES += tst_drc_db_tests.cpp \
    ../../drc/db/drcdb.cpp \
    ../../drc/drc_shared/models/Person.cpp \
    ../../drc/drc_shared/models/CurrentUser.cpp \
    ../../drc/drc_shared/models/mediationprocess.cpp \
    ../../drc/drc_shared/models/mediationsession.cpp \
    ../../drc/drc_shared/models/party.cpp \
    ../../drc/drc_shared/drctypes.cpp \
    ../../drc/drc_shared/mediator/Mediator.cpp \
    ../../drc/drc_shared/models/User.cpp \
    ../../drc/bl/Crypto/SHA256_Crypto.cpp \
    ../../drc/drc_shared/models/clientsessiondata.cpp \
    ../../drc/drc_shared/models/reswareport.cpp \
    ../../drc/drc_shared/models/mediationevaluation.cpp \
    ../../drc/drc_shared/models/monthlyreport.cpp \
    ../../drc/drc_shared/models/Note.cpp \
    unit_tests/db_test_base.cpp \
    unit_tests/person_table_tests/person_table_test.cpp \
    unit_tests/mediation_table_tests/mediation_table_test.cpp \
    unit_tests/session_table_tests/session_table_test.cpp \
    unit_tests/client_table_tests/client_table_test.cpp \
    unit_tests/client_session_table_tests/client_session_table_test.cpp \
    unit_tests/notes_table_tests/notes_table_test.cpp \
    unit_tests/evaluation_table_tests/evaluation_table_test.cpp \
    unit_tests/systemic_tests/systemic_test.cpp \
    unit_tests/database_setup_tests/database_setup_test.cpp \
    test_main.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../drc/db/drcdb.h \
    ../../drc/drc_shared/models/DBBaseObject.h \
    ../../drc/drc_shared/models/Person.h \
    ../../drc/db/Filter.h \
    ../../drc/drc_shared/models/mediationprocess.h \
    ../../drc/drc_shared/models/mediationsession.h \
    ../../drc/drc_shared/models/party.h \
    ../../drc/drc_shared/drctypes.h \
    ../../drc/drc_shared/mediator/Mediator.h \
    ../../drc/drc_shared/mediator/MediatorArg.h \
    ../../drc/drc_shared/mediator/MediatorKeys.h \
    ../../drc/drc_shared/models/User.h \
    ../../drc/drc_shared/models/DRCModels.h \
    ../../drc/bl/Crypto/SHA256_Crypto.h \
    ../../drc/drc_shared/models/clientsessiondata.h \
    ../../drc/drc_shared/models/reswareport.h \
    ../../drc/drc_shared/models/mediationevaluation.h \
    ../../drc/drc_shared/models/monthlyreport.h \
    ../../drc/drc_shared/models/Note.h \
    initialization_methods/initialization_methods.h \
    allocation_methods/allocation_methods.h \
    column_enumerations/note_column_enum.h \
    column_enumerations/person_column_enum.h \
    column_enumerations/process_column_enum.h \
    column_enumerations/session_column_enum.h \
    column_enumerations/client_session_column_enum.h \
    column_enumerations/mediation_evaluation_column_enum.h \
    unit_tests/db_test_base.h \
    unit_tests/person_table_tests/person_table_test.h \
    unit_tests/mediation_table_tests/mediation_table_test.h \
    unit_tests/session_table_tests/session_table_test.h \
    unit_tests/client_table_tests/client_table_test.h \
    unit_tests/client_session_table_tests/client_session_table_test.h \
    unit_tests/notes_table_tests/notes_table_test.h \
    unit_tests/evaluation_table_tests/evaluation_table_test.h \
    unit_tests/systemic_tests/systemic_test.h \
    column_enumerations/client_column_enum.h \
    unit_tests/database_setup_tests/database_setup_test.h
