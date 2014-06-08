#-------------------------------------------------
#
# Project created by QtCreator 2014-05-23T19:38:12
#
#-------------------------------------------------

QT      += core gui
QT	+= sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = drc
TEMPLATE = app

INCLUDEPATH += bl/ \
    db/ \
    drc_shared/ \
    drc_shared/mediator/ \
    drc_shared/models/ \
    gui/

SOURCES += main.cpp\
    bl/drcbl.cpp \
    db/drcdb.cpp \    
    drc_shared/mediator/Mediator.cpp \
    drc_shared/mediator/AsyncMediatorCall.cpp \
    drc_shared/models/Person.cpp \
    DRCClient.cpp \
    drc_shared/models/Intake.cpp \
    gui/fruitnameform.cpp \
    gui/intakeform.cpp \
    gui/particapants.cpp \
    bl/fruitnameprocessor.cpp \
    bl/intakeformprocessor.cpp \
    gui/loginform.cpp \
    bl/Crypto/SHA256_Crypto.cpp \
    drc_shared/mediator/asyncmediatorworker.cpp \
    gui/queryform.cpp \
    drc_shared/models/Fruit.cpp \
    gui/contactrecorddataview.cpp \
    bl/userloginprocessor.cpp \
    drc_shared/models/User.cpp \
    gui/mediationsession.cpp \
    gui/attorneyandsupportformediationsessionview.cpp \
    gui/detailsview.cpp \
    gui/childrenview.cpp \
    drc_shared/models/CurrentUser.cpp \
    gui/persondetailsform.cpp \
    gui/mediationprocessview.cpp

HEADERS  += \
    bl/drcbl.h \
    db/drcdb.h \
    drc_shared/mediator/Mediator.h \
    drc_shared/mediator/MediatorArg.h \
    drc_shared/mediator/MediatorKeys.h \
    drc_shared/mediator/AsyncMediatorCall.h \
    drc_shared/models/Person.h \
    DRCClient.h \
    drc_shared/models/Intake.h \
    gui/fruitnameform.h \
    drc_shared/models/DRCModels.h \
    gui/intakeform.h \
    gui/particapants.h \
    bl/fruitnameprocessor.h \
    bl/intakeformprocessor.h \
    db/Filter.h \
    db/FilterTypes.h \
    drc_shared/models/Fruit.h \
    drc_shared/models/User.h \
    drc_shared/models/UserType.h \
    db/sqlite3.h \
    bl/Processor.h \
    bl/userloginprocessor.h \
    bl/Crypto/SHA256_Crypto.h \
    gui/loginform.h \
    bl/Crypto/SHA256_Crypto.h \
    drc_shared/mediator/asyncmediatorworker.h \
    gui/queryform.h \
    gui/contactrecorddataview.h \
    drc_shared/models/DBBaseObject.h \
    gui/mediationsession.h \
    gui/attorneyandsupportformediationsessionview.h \
    gui/detailsview.h \
    gui/childrenview.h \
    drc_shared/models/CurrentUser.h \
    gui/persondetailsform.h \
    gui/mediationprocessview.h

FORMS    += \
    DRCClient.ui \
    gui/fruitnameform.ui \
    gui/intakeform.ui \
    gui/particapants.ui \
    gui/loginform.ui \
    gui/queryform.ui \
    gui/contactrecorddataview.ui \
    gui/mediationsession.ui \
    gui/attorneyandsupportformediationsessionview.ui \
    gui/detailsview.ui \
    gui/childrenview.ui \
    gui/persondetailsform.ui \
    gui/mediationprocessview.ui


CONFIG += c++11

OTHER_FILES += \
    
