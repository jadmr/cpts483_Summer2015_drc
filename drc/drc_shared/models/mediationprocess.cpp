#include "mediationprocess.h"

#include <sstream>
#include "DRCModels.h"
#include "drctypes.h"
#include <random>
#include "DBBaseObject.h"

MediationProcess::MediationProcess() : DBBaseObject()
{
    _creationDate = QDateTime::currentDateTime();
    AddParty(new Party());
}
MediationProcess::MediationProcess(PartyVector parties, uint stateTrans, uint actStateTrans, DisputeTypes disputeType,
                                   QDateTime creationDate, DisputeProcessStates processState, CountyIds county,
                                   MediationNotesVector mediationNotes, ReferralTypes reftype, bool spanish, MediationSessionVector sessions) :
    _parties(parties), _stateTransition(stateTrans), _activeStateTransition(actStateTrans), _disputeType(disputeType),
    _creationDate(creationDate), _processState(processState), _countyOfMediation(county), _mediationNotes(mediationNotes),
    _referalSource(reftype), _requiresSpanish(spanish), _mediationSessionVector(sessions){}


MediationProcess::~MediationProcess()
{
}

// Abstract Overrides
QString MediationProcess::Parse()
{
#warning TODO - PARSE UNIMPLEMENTED!!!!

}

QString MediationProcess::table()
{
#warning TODO - table() UNIMPLEMENTED!!!!

}

QString MediationProcess::DuplicateQuery()
{
#warning TODO - DuplicateQuery() UNIMPLEMENTED!!!!

}

QString MediationProcess::SearchQuery()
{
#warning TODO - SearchQuery() UNIMPLEMENTED!!!!

}
void MediationProcess::addMediation()
{
    _mediationSessionVector.push_back(new MediationSession());
}

// Test Data - Fill the object with test values in every field.
MediationProcess *MediationProcess::SampleData()
{
    MediationProcess *result = new MediationProcess();

    // unique string to append to fields
    static int _SAMPLE_INDEX = 0;
    std::stringstream ss;
    ss << ++_SAMPLE_INDEX;
    std::string strId = ss.str();
    result->GetParties()->clear();
    for(int i=0; i < rand() % 4 + 1; ++i)
        result->AddParty(Party::SampleData());

    result->_countyOfMediation = (CountyIds)(rand() % 3 + 1);
    result->_disputeType = (DisputeTypes)(rand() % 7 + 1);
    result->_requiresSpanish = rand() % 2;
    result->_processState = (DisputeProcessStates)( rand() % 5 + 1 );
    result->_referalSource = (ReferralTypes)(rand() % 8 + 1);
    result->SetCreationDate(QDateTime::currentDateTime());
    MediationSessionVector *temp = new MediationSessionVector;
    for(int i = 0; i< rand() % 5 + 1; i++)
        temp->push_back(MediationSession::SampleData());
    result->setMediationSessionVector(temp);
    for(int i=0; i < 25; ++i)
        result->GetNotes()->push_back(new Note("Some more mediation notes " + QString::number(i)));



    return result;
}

int MediationProcess::GetAffectedChildrenCount()
{
    int total = 0;
    foreach(auto p, _parties)
        total += p->GetAffectedChildren();
    return total;
}


