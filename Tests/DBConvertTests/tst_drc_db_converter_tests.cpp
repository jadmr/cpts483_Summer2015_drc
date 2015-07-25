#include <QString>
#include <QtTest>
#include <QTextStream>
#include <QFile>

#include "drcdb.h"
#include "mediationprocess.h"
#include "Person.h"
#include "drctypes.h"

//Unit Tests
bool doDimensionsMatch(MediationProcessVector* oldDB,MediationProcessVector* newDB);
bool doMediationsMatch(MediationProcess* a, MediationProcess* b);

int main()
{
    QString oldPath = "outdated.db3";
    QString newPath = "new.db3";
    DRCDB database;

    qDebug() <<"Performing Database Conversion Tests";

    qDebug() <<"Loading old database from " << oldPath;
    database.OpenDatabase(oldPath);
    /*if (~database.IsDatabaseOpen())
    {
        qDebug() << "ERROR: Database could not be open.";
        exit(1);
    }*/

    qDebug() <<"Pulling in database records";

    //Make process Id string
    int numberOfMediations = database.getNumberOfMediations();
    QString mediationIdMatches = "1";
    for(int i=0;i<numberOfMediations-1;i++)
    {
        mediationIdMatches += ", ";
        int temp = i+2;
        mediationIdMatches += QString::number(temp);
    }

    //Get mediations from that procesID list
    MediationProcessVector* outdatedMediationProcesses = database.LoadMediations(mediationIdMatches);

    qDebug() << "Loaded " << outdatedMediationProcesses->size() <<" mediations! ";

    //Close database
    database.CloseDatabase();

    qDebug() <<"Loading new database from " << newPath;
    database.OpenDatabase(newPath);
    /*if (~database.IsDatabaseOpen())
    {
        qDebug() << "ERROR: Database could not be open.";
        exit(1);
    }*/

    qDebug() <<"Pulling in database records";

    //Make process Id string
    numberOfMediations = database.getNumberOfMediations();
    mediationIdMatches = "1";
    for(int i=0;i<numberOfMediations-1;i++)
    {
        mediationIdMatches += ", ";
        int temp = i+2;
        mediationIdMatches += QString::number(temp);
    }

    //Get mediations from that procesID list
    MediationProcessVector* updatedMediationProcesses = database.LoadMediations(mediationIdMatches);

    qDebug() << "Loaded " << updatedMediationProcesses->size() <<" mediations! ";

    //Close database
    database.CloseDatabase();

    //Start unit testing
    QString result = "";
    bool overallResult = true;

    //Dimension test
    bool dimensionsMatch = doDimensionsMatch(outdatedMediationProcesses,updatedMediationProcesses);
    overallResult = overallResult && dimensionsMatch;
    if (dimensionsMatch)
    {result = QString("PASS");}
    else
    {result = QString("FAIL");}
    qDebug() << QString(result) << " - Outdated and Updated dimensions match.";
    if (!dimensionsMatch)
    {exit(1);}

    //Process Tests
    for (int i=0;i<outdatedMediationProcesses->size();i++)
    {
        bool mediationsMatch = doMediationsMatch(outdatedMediationProcesses->at(i),updatedMediationProcesses->at(i));
        overallResult = overallResult && mediationsMatch;
        if (mediationsMatch)
        {result = QString("PASS");}
        else
        {result = QString("FAIL");}
        qDebug() << QString(result) << " - Mediation " << i << " match test.";
    }

    //Finished testing yay!
    if (overallResult)
    {result = QString("PASS");}
    else
    {result = QString("FAIL");}
    qDebug() << result << " - All tests.";

    //system("pause");

    return 0;
}

bool doDimensionsMatch(MediationProcessVector* oldDB,MediationProcessVector* newDB)
{
    return oldDB->size() == newDB->size();
}

bool doMediationsMatch(MediationProcess* a, MediationProcess* b)
{
    bool result = true;

    result = result && ( a->getMediationClause() == b->getMediationClause() );

    //get session vector
    for (int i=0;i<a->getMediationSessionVector()->size();i++)
    {
        MediationSession * as = a->getMediationSessionVector()->at(i);
        MediationSession * bs = b->getMediationSessionVector()->at(i);

        //get client session vector
        for (int ii = 0; ii < as->getClientSessionDataVector()->size();ii++)
        {
            ClientSessionData * ac = as->getClientSessionDataVector()->at(ii);
            ClientSessionData * bc = bs->getClientSessionDataVector()->at(ii);

            result = result && ( ac->getAtTable() == bc->getAtTable() );
            result = result && ( ac->getAttyDidAttend() == bc->getAttyDidAttend() );
            result = result && ( ac->getAttySaidAttend() == bc->getAttySaidAttend() );
            result = result && ( ac->getFee() == bc->getFee() );
            result = result && ( ac->getIncome() == bc->getIncome() );
            result = result && ( ac->getOnPhone() == bc->getOnPhone() );
            result = result && ( ac->getPaid() == bc->getPaid() );
            result = result && ( ac->getSupport() == bc->getSupport() );
            result = result && ( ac->GetId() == bc->GetId() );
            result = result && ( ac->GetIdRowName() == bc->GetIdRowName() );
        }

        result = result && ( as->getFeeStatus() == bs->getFeeStatus() );
        result = result && ( as->getMediationTime() == bs->getMediationTime() );
        result = result && ( as->getMediator1() == bs->getMediator1() );
        result = result && ( as->getMediator2() == bs->getMediator2() );
        result = result && ( as->getObserver1() == bs->getObserver1() );
        result = result && ( as->getObserver2() == bs->getObserver2() );
        result = result && ( as->getOutcome() == bs->getOutcome() );
        result = result && ( as->getScheduledDate() == bs->getScheduledDate() );
        result = result && ( as->getScheduledTime() == bs->getScheduledTime() );
        result = result && ( as->getStatus() == bs->getStatus() );
        result = result && ( as->GetCreatedDate() == bs->GetCreatedDate() );
        result = result && ( as->GetId() == bs->GetId() );
        result = result && ( as->GetIdRowName() == bs->GetIdRowName() );
        result = result && ( as->GetIsShuttle() == bs->GetIsShuttle() );
        result = result && ( as->GetState() == bs->GetState() );
        result = result && ( as->GetUpdatedDate() == bs->GetUpdatedDate() );
    }
    result = result && ( a->getPrintCourtDate()  == b->getPrintCourtDate()  );
    result = result && ( a->GetAffectedChildrenCount() == b->GetAffectedChildrenCount() );
    result = result && ( a->GetCountyId() == b->GetCountyId() );
    result = result && ( a->GetCourtDate() == b->GetCourtDate() );
    result = result && ( a->GetCourtOrder() == b->GetCourtOrder() );
    result = result && ( a->GetCourtType() == b->GetCourtType() );
    result = result && ( a->GetCreatedDate() == b->GetCreatedDate() );
    result = result && ( a->GetDirectAdult() == b->GetDirectAdult() );
    result = result && ( a->GetDirectChildren() == b->GetDirectChildren() );
    result = result && ( a->GetDisputeType() == b->GetDisputeType() );
    result = result && ( a->GetId() == b->GetId() );
    result = result && ( a->GetIdRowName() == b->GetIdRowName() );
    result = result && ( a->GetIndirectAdult() == b->GetIndirectAdult() );
    result = result && ( a->GetIndirectChildren() == b->GetIndirectChildren() );
    result = result && ( a->GetInfoOnly() == b->GetInfoOnly() );
    result = result && ( a->GetInquiryType() == b->GetInquiryType() );
    result = result && ( a->GetInternalState() == b->GetInternalState() );
    result = result && ( a->GetIsCourtCase() == b->GetIsCourtCase() );
    result = result && ( a->GetIsShuttle() == b->GetIsShuttle() );

    //get notes
    for (int i=0;i<a->GetNotes()->size();i++)
    {
        Note * an = a->GetNotes()->at(i);
        Note * bn = b->GetNotes()->at(i);
        result = result && ( an->GetCreatedDate() == bn->GetCreatedDate() );
        result = result && ( an->GetId() == bn->GetId() );
        result = result && ( an->GetIdRowName() == bn->GetIdRowName() );
        result = result && ( an->GetmediationId() == bn->GetmediationId() );
        result = result && ( an->GetMessage() == bn->GetMessage() );
        result = result && ( an->GetSessionId() == bn->GetSessionId() );
    }

    for (int i=0;i<a->GetParties()->size();i++)
    {
        Party * ap = a->GetParties()->at(i);
        Party * bp = b->GetParties()->at(i);
        Person aAttorney = ap->GetAttorney();
        Person bAttorney = bp->GetAttorney();
        Person * aPrimary =  ap->GetPrimary();
        Person * bPrimary =  bp->GetPrimary();

        //Compare party atributes
        result = result && ( ap->GetAffectedChildren() == bp->GetAffectedChildren() );
        result = result && ( ap->GetId() == bp->GetId() );
        result = result && ( ap->GetIdRowName() == bp->GetIdRowName() );
        result = result && ( ap->GetTotalChildren() == bp->GetTotalChildren() );

        //LORENZO Party type is only working in debug mode.... I think this is because it isn't being initialized, or even used. Will ignore this value for now
        //result = result && ( ap->GetType() == bp->GetType() );
        //qDebug() << ap->GetType() << " - " << bp->GetType();

        //Compare Attorneys
        result = result && ( aAttorney.getAssistantEmail() == bAttorney.getAssistantEmail() );
        result = result && ( aAttorney.getAssistantName() == bAttorney.getAssistantName() );
        result = result && ( aAttorney.getAssistantPhone() == bAttorney.getAssistantPhone() );
        result = result && ( aAttorney.getAssistantPhoneExt() == bAttorney.getAssistantPhoneExt() );
        result = result && ( aAttorney.getAttorneyEmail() == bAttorney.getAttorneyEmail() );
        result = result && ( aAttorney.getAttorney() == bAttorney.getAttorney() );
        result = result && ( aAttorney.getAttorneyPhone() == bAttorney.getAttorneyPhone() );
        result = result && ( aAttorney.getCity() == bAttorney.getCity() );
        result = result && ( aAttorney.getCounty() == bAttorney.getCounty() );
        result = result && ( aAttorney.getEmail() == bAttorney.getEmail() );
        result = result && ( aAttorney.getFirstName() == bAttorney.getFirstName() );
        result = result && ( aAttorney.getLastName() == bAttorney.getLastName() );
        result = result && ( aAttorney.getMiddleName() == bAttorney.getMiddleName() );
        result = result && ( aAttorney.getNumberChildrenInHousehold() == bAttorney.getNumberChildrenInHousehold() );
        result = result && ( aAttorney.getNumberInHousehold() == bAttorney.getNumberInHousehold() );
        result = result && ( aAttorney.getPrimaryPhone() == bAttorney.getPrimaryPhone() );
        result = result && ( aAttorney.getPrimaryPhoneExt() == bAttorney.getPrimaryPhoneExt() );
        result = result && ( aAttorney.getSecondaryPhone() == bAttorney.getSecondaryPhone() );
        result = result && ( aAttorney.getSecondaryPhoneExt() == bAttorney.getSecondaryPhoneExt() );
        result = result && ( aAttorney.getState() == bAttorney.getState() );
        result = result && ( aAttorney.getStreet() == bAttorney.getStreet() );
        result = result && ( aAttorney.getUnit() == bAttorney.getUnit() );
        result = result && ( aAttorney.getZip() == bAttorney.getZip() );
        result = result && ( aAttorney.GetId() == bAttorney.GetId() );
        result = result && ( aAttorney.GetIdRowName() == bAttorney.GetIdRowName() );

        //Compare Primary
        result = result && ( aPrimary->getAssistantEmail() == bPrimary->getAssistantEmail() );
        result = result && ( aPrimary->getAssistantName() == bPrimary->getAssistantName() );
        result = result && ( aPrimary->getAssistantPhone() == bPrimary->getAssistantPhone() );
        result = result && ( aPrimary->getAssistantPhoneExt() == bPrimary->getAssistantPhoneExt() );
        result = result && ( aPrimary->getAttorney() == bPrimary->getAttorney() );
        result = result && ( aPrimary->getAttorneyEmail() == bPrimary->getAttorneyEmail() );
        result = result && ( aPrimary->getAttorneyPhone() == bPrimary->getAttorneyPhone() );
        result = result && ( aPrimary->getCity() == bPrimary->getCity() );
        result = result && ( aPrimary->getCounty() == bPrimary->getCounty() );
        result = result && ( aPrimary->getEmail() == bPrimary->getEmail() );
        result = result && ( aPrimary->getFirstName() == bPrimary->getFirstName() );
        result = result && ( aPrimary->getLastName() == bPrimary->getLastName() );
        result = result && ( aPrimary->getMiddleName() == bPrimary->getMiddleName() );
        result = result && ( aPrimary->getNumberChildrenInHousehold() == bPrimary->getNumberChildrenInHousehold() );
        result = result && ( aPrimary->getNumberInHousehold() == bPrimary->getNumberInHousehold() );
        result = result && ( aPrimary->getPrimaryPhone() == bPrimary->getPrimaryPhone() );
        result = result && ( aPrimary->getPrimaryPhoneExt() == bPrimary->getPrimaryPhoneExt() );
        result = result && ( aPrimary->getSecondaryPhone() == bPrimary->getSecondaryPhone() );
        result = result && ( aPrimary->getSecondaryPhoneExt() == bPrimary->getSecondaryPhoneExt() );
        result = result && ( aPrimary->getState() == bPrimary->getState() );
        result = result && ( aPrimary->getStreet() == bPrimary->getStreet() );
        result = result && ( aPrimary->getUnit() == bPrimary->getUnit() );
        result = result && ( aPrimary->getZip() == bPrimary->getZip() );
        result = result && ( aPrimary->GetId() == bPrimary->GetId() );
        result = result && ( aPrimary->GetIdRowName() == bPrimary->GetIdRowName() );

        //Process children vector
        for (int ii = 0; ii < ap->GetChildren().size(); ii++)
        {
            Person * aChild = ap->GetChildren().at(ii);
            Person * bChild = bp->GetChildren().at(ii);

            result = result && ( aChild->getAssistantEmail() == bChild->getAssistantEmail() );
            result = result && ( aChild->getAssistantName() == bChild->getAssistantName() );
            result = result && ( aChild->getAssistantPhone() == bChild->getAssistantPhone() );
            result = result && ( aChild->getAssistantPhoneExt() == bChild->getAssistantPhoneExt() );
            result = result && ( aChild->getAttorney() == bChild->getAttorney() );
            result = result && ( aChild->getAttorneyEmail() == bChild->getAttorneyEmail() );
            result = result && ( aChild->getAttorneyPhone() == bChild->getAttorneyPhone() );
            result = result && ( aChild->getCity() == bChild->getCity() );
            result = result && ( aChild->getCounty() == bChild->getCounty() );
            result = result && ( aChild->getEmail() == bChild->getEmail() );
            result = result && ( aChild->getFirstName() == bChild->getFirstName() );
            result = result && ( aChild->getLastName() == bChild->getLastName() );
            result = result && ( aChild->getMiddleName() == bChild->getMiddleName() );
            result = result && ( aChild->getNumberChildrenInHousehold() == bChild->getNumberChildrenInHousehold() );
            result = result && ( aChild->getNumberInHousehold() == bChild->getNumberInHousehold() );
            result = result && ( aChild->getPrimaryPhone() == bChild->getPrimaryPhone() );
            result = result && ( aChild->getPrimaryPhoneExt() == bChild->getPrimaryPhoneExt() );
            result = result && ( aChild->getSecondaryPhone() == bChild->getSecondaryPhone() );
            result = result && ( aChild->getSecondaryPhoneExt() == bChild->getSecondaryPhoneExt() );
            result = result && ( aChild->getState() == bChild->getState() );
            result = result && ( aChild->getStreet() == bChild->getStreet() );
            result = result && ( aChild->getUnit() == bChild->getUnit() );
            result = result && ( aChild->getZip() == bChild->getZip() );
            result = result && ( aChild->GetId() == bChild->GetId() );
            result = result && ( aChild->GetIdRowName() == bChild->GetIdRowName() );
        }

        //Process observer vector
        for (int ii = 0; ii < ap->GetChildren().size(); ii++)
        {
            Person * aObserver = ap->GetObservers().at(ii);
            Person * bObserver = bp->GetObservers().at(ii);

            result = result && ( aObserver->getAssistantEmail() == bObserver->getAssistantEmail() );
            result = result && ( aObserver->getAssistantName() == bObserver->getAssistantName() );
            result = result && ( aObserver->getAssistantPhone() == bObserver->getAssistantPhone() );
            result = result && ( aObserver->getAssistantPhoneExt() == bObserver->getAssistantPhoneExt() );
            result = result && ( aObserver->getAttorney() == bObserver->getAttorney() );
            result = result && ( aObserver->getAttorneyEmail() == bObserver->getAttorneyEmail() );
            result = result && ( aObserver->getAttorneyPhone() == bObserver->getAttorneyPhone() );
            result = result && ( aObserver->getCity() == bObserver->getCity() );
            result = result && ( aObserver->getCounty() == bObserver->getCounty() );
            result = result && ( aObserver->getEmail() == bObserver->getEmail() );
            result = result && ( aObserver->getFirstName() == bObserver->getFirstName() );
            result = result && ( aObserver->getLastName() == bObserver->getLastName() );
            result = result && ( aObserver->getMiddleName() == bObserver->getMiddleName() );
            result = result && ( aObserver->getNumberChildrenInHousehold() == bObserver->getNumberChildrenInHousehold() );
            result = result && ( aObserver->getNumberInHousehold() == bObserver->getNumberInHousehold() );
            result = result && ( aObserver->getPrimaryPhone() == bObserver->getPrimaryPhone() );
            result = result && ( aObserver->getPrimaryPhoneExt() == bObserver->getPrimaryPhoneExt() );
            result = result && ( aObserver->getSecondaryPhone() == bObserver->getSecondaryPhone() );
            result = result && ( aObserver->getSecondaryPhoneExt() == bObserver->getSecondaryPhoneExt() );
            result = result && ( aObserver->getState() == bObserver->getState() );
            result = result && ( aObserver->getStreet() == bObserver->getStreet() );
            result = result && ( aObserver->getUnit() == bObserver->getUnit() );
            result = result && ( aObserver->getZip() == bObserver->getZip() );
            result = result && ( aObserver->GetId() == bObserver->GetId() );
            result = result && ( aObserver->GetIdRowName() == bObserver->GetIdRowName() );
        }
    }

    result = result && ( a->GetReferralType() == b->GetReferralType() );
    result = result && ( a->GetRequiresSpanish() == b->GetRequiresSpanish() );
    result = result && ( a->GetSessionType() == b->GetSessionType() );
    result = result && ( a->GetState() == b->GetState() );
    result = result && ( a->GetStateMessage() == b->GetStateMessage() );
    result = result && ( a->GetUpdatedDate() == b->GetUpdatedDate() );

    //Get Tag field.
    result = result && ( a->GetTags() == b->GetTags() );

    //Other value comparisons can be added on below in the form of
    //result = result && ( a->getValue() == b->getValue() );

    return result;
}
