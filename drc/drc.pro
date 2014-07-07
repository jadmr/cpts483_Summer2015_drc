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
    gui/loginform.cpp \
    bl/Crypto/SHA256_Crypto.cpp \
    drc_shared/mediator/asyncmediatorworker.cpp \
    gui/queryform.cpp \
    gui/contactrecorddataview.cpp \
    bl/userloginprocessor.cpp \
    bl/stateupdate.cpp \
    drc_shared/models/User.cpp \
    gui/persondetailsform.cpp \
    gui/mediationprocessview.cpp \
    gui/partyform.cpp \
    drc_shared/models/party.cpp \
    drc_shared/models/mediationprocess.cpp \
    gui/mediationprocessstatusform.cpp \
    gui/searchwizard/searchwizard.cpp \
    gui/searchwizard/searchwizardintro.cpp \
    gui/searchwizard/searchwizardselecttype.cpp \
    gui/searchwizard/searchwizardparameters.cpp \
    gui/searchwizard/searchwizardresults.cpp \
    gui/Mock_Server/mock_server.cpp \
    drc_shared/CurrentUser.cpp \
    drc_shared/drctypes.cpp \
    gui/toolbarmanager.cpp \
    gui/Mock_Server/dummy.cpp \
    gui/mediationbrowser.cpp \
    gui/sessionsbrowser.cpp \
    gui/notesbrowser.cpp \
    drc_shared/models/mediationsession.cpp \
    gui/mediationsessionform.cpp \
    gui/sessionoverview.cpp \
    gui/mptoolbox.cpp \
    gui/sessioncell.cpp \
    gui/nosessionsview.cpp \
    drc_shared/mpfilemaker.cpp \
    drc_shared/models/Note.cpp \
    drc_shared/models/clientsessiondata.cpp \
    gui/feeform.cpp \
    gui/attorneysupportview.cpp \
    gui/mediationobserverview.cpp \
    gui/manageusers.cpp \
    gui/attorneyheaderview.cpp \
    gui/mainmenuform.cpp

HEADERS  += \
    bl/drcbl.h \
    db/drcdb.h \
    drc_shared/mediator/Mediator.h \
    drc_shared/mediator/MediatorArg.h \
    drc_shared/mediator/MediatorKeys.h \
    drc_shared/mediator/AsyncMediatorCall.h \
    drc_shared/models/Person.h \
    DRCClient.h \
    drc_shared/models/DRCModels.h \
    db/Filter.h \
    db/FilterTypes.h \
    drc_shared/models/User.h \
    drc_shared/models/UserType.h \
    bl/userloginprocessor.h \
    bl/Crypto/SHA256_Crypto.h \
    gui/loginform.h \
    bl/Crypto/SHA256_Crypto.h \
    bl/stateupdate.h \
    drc_shared/mediator/asyncmediatorworker.h \
    gui/queryform.h \
    gui/contactrecorddataview.h \
    drc_shared/models/DBBaseObject.h \
    drc_shared/models/CurrentUser.h \
    gui/persondetailsform.h \
    gui/mediationprocessview.h \
    gui/partyform.h \
    drc_shared/models/party.h \
    drc_shared/models/mediationprocess.h \
    drc_shared/drctypes.h \
    gui/mediationprocessstatusform.h \
    gui/searchwizard/searchwizard.h \
    gui/searchwizard/searchwizardintro.h \
    gui/searchwizard/searchwizardselecttype.h \
    gui/searchwizard/searchwizardparameters.h \
    gui/searchwizard/searchwizardresults.h \
    gui/Mock_Server/mock_server.h \
    drc_shared/CurrentUser.h \
    gui/toolbarmanager.h \
    gui/Mock_Server/dummy.h \
    drc_shared/models/mediationsession.h \
    gui/mediationsessionform.h \
    gui/mediationbrowser.h \
    gui/sessionoverview.h \
    gui/sessionsbrowser.h \
    gui/notesbrowser.h \
    gui/mptoolbox.h \
    gui/sessioncell.h \
    gui/nosessionsview.h \
    gui/Note.h \
    drc_shared/mpfilemaker.h \
    drc_shared/models/Note.h \
    drc_shared/models/clientsessiondata.h \
    gui/feeform.h \
    gui/attorneysupportview.h \
    gui/mediationobserverview.h \
    gui/manageusers.h \
    gui/attorneyheaderview.h \
    gui/mainmenuform.h

FORMS    += \
    DRCClient.ui \
    gui/fruitnameform.ui \
    gui/loginform.ui \
    gui/queryform.ui \
    gui/contactrecorddataview.ui \
    gui/persondetailsform.ui \
    gui/mediationprocessview.ui \
    gui/partyform.ui \
    gui/mediationbrowser.ui \
    gui/mediationprocessstatusform.ui \
    gui/mediationsessionform.ui \
    gui/sessionoverview.ui \
    gui/sessionsbrowser.ui \
    gui/notesbrowser.ui \
    gui/mptoolbox.ui \
    gui/sessioncell.ui \
    gui/nosessionsview.ui \
    gui/feeform.ui \
    gui/attorneysupportview.ui \
    gui/mediationobserverview.ui \
    gui/manageusers.ui \
    gui/attorneyheaderview.ui \
    gui/mainmenuform.ui


CONFIG += c++11

OTHER_FILES += \
    

RESOURCES += \
    drc_resources.qrc
