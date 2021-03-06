#include "mediationsession.h"
#include <sstream>
#include <QDateTime>
#include <QDebug>
#include "DRCModels.h"

MediationSession::MediationSession()
{
    _state = SessionStates::SESSION_STATE_PENDING;
    _outcome = SESSION_OUTCOME_NONE;
    _mediator1 = _mediator2 = _observer1 = _observer2 = "";
    _mediationTime = QDateTime::currentDateTime();
    _isShuttle = false;

}
MediationSession::MediationSession(uint numOfClients)
{
    _state = SessionStates::SESSION_STATE_PENDING;
    _outcome = SESSION_OUTCOME_NONE;
    _mediator1 = _mediator2 = _observer1 = _observer2 = "";
    _mediationTime = QDateTime::currentDateTime();
    _isShuttle = false;
    for(int i = 0; i < (int)numOfClients; i++)
        _clientSessionDataVector.insert(_clientSessionDataVector.end() - 2, new ClientSessionData());
}

QString MediationSession::ColumnNames()
{
    QString column_names = QString ("%1, %2, %3, %4, %5 ,%6, %7, ")
            .arg("Session_id")
            .arg("Process_id")
            .arg("SessionStatus")
            .arg("SessionOutcome")
            .arg("CreatedDateTime")
            .arg("UpdatedDateTime")
            .arg("ScheduledTime");

    column_names += QString ("%1, %2, %3, %4, %5")
            .arg("Mediator1")
            .arg("Mediator2")
            .arg("Observer1")
            .arg("Observer2")
            .arg("Shuttle");

    QString toReturn = QString("(%1)")
            .arg(column_names);

    return toReturn;
}

QString MediationSession::Parse()
{
    //static QString single_quote("\'");
    QString column_values = QString("%1, %2, ")
            .arg(QString::number(this->GetState()))
            .arg(QString::number(this->getOutcome()));

    column_values += QString("'%1', '%2', '%3', ")
            .arg(this->GetCreatedDate().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(this->GetUpdatedDate().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(this->getMediationTime().toString("yyyy-MM-dd hh:mm:ss"));

    column_values += QString("'%1', '%2', '%3', '%4', ")
            .arg(this->getMediator1())
            .arg(this->getMediator2())
            .arg(this->getObserver1())
            .arg(this->getObserver2());

    column_values += QString("%1")
            .arg(QString::number(this->GetIsShuttle()));

    return column_values;
}

QString MediationSession::UpdateParse()
{
    QString toUpdate;

    // Status
    toUpdate += QString("SessionStatus = '%1', ").arg(QString::number(this->GetState()));
    toUpdate += QString("SessionOutcome = '%1', ").arg(QString::number(this->getOutcome()));

    toUpdate += QString("UpdatedDateTime = '%1', ").arg(this->GetUpdatedDate().toString("yyyy-MM-dd"));
    toUpdate += QString("ScheduledTime = '%1', ")
            .arg(this->getMediationTime().toString("yyyy-MM-dd hh:mm:ss"));

    //Mediators
    toUpdate += QString("Mediator1 = '%1', ").arg(this->getMediator1().replace("'", "''"));
    toUpdate += QString("Mediator2 = '%1', ").arg(this->getMediator2().replace("'", "''"));

    //Observers
    toUpdate += QString("Observer1 = '%1', ").arg(this->getObserver1().replace("'", "''"));
    toUpdate += QString("Observer2 = '%1', ").arg(this->getObserver2().replace("'", "''"));
    toUpdate += QString("Shuttle = '%1'").arg(this->GetIsShuttle());
qDebug()<<toUpdate;
    return toUpdate;
}

QString MediationSession::table()
{
    return QString("Session_Table");
}

QString MediationSession::GetIdRowName()
{
    return "session_id";
}

QString MediationSession::DuplicateQuery()
{
    return "";
}

QString MediationSession::SearchQuery()
{
    return "";
}


QString MediationSession::getStatus() const
{
    return StringForSessionStates(_state);
}

QString MediationSession::getFeeStatus() const
{
    bool partial, paidInFull, noFees;
    partial = false;
    paidInFull = noFees = true;
    for(int i = 0; i < (int)_clientSessionDataVector.size(); i++)
    {
        if(!_clientSessionDataVector.at(i)->isNoFee() && !_clientSessionDataVector.at(i)->isPaid())
            paidInFull = false;
        if(!_clientSessionDataVector.at(i)->isNoFee())
            noFees = false;
        if(!_clientSessionDataVector.at(i)->isNoFee() && _clientSessionDataVector.at(i)->isPaid())
            partial = true;
    }

    if(noFees)           //check if all fees are empty
        return "No fees added";  // stateupdate.cpp is comparing with this return value.
    else if(paidInFull)                                                                             //check if paid in full
        return "Paid In Full";
    else if(partial)                                           //check if there are any partial payments
        return "Partial Payment";
    else                                                                                            //else it's not paid
        return "Not Paid";
}

bool MediationSession::isFullyPaid() const
{
     bool paidInFull = true;
    for(int i = 0; i < (int)_clientSessionDataVector.size(); i++)
    {
        if(!_clientSessionDataVector.at(i)->isNoFee() && !_clientSessionDataVector.at(i)->isPaid())
            paidInFull = false;
    }
    return paidInFull;
}

void MediationSession::removeClientSessionData(uint value)
{
    if(_clientSessionDataVector.size() > 0)
        _clientSessionDataVector.erase(_clientSessionDataVector.begin() + value);
}

MediationSession *MediationSession::SampleData()
{

    MediationSession *result = new MediationSession();

     // unique string to append to fields
    static int _SAMPLE_INDEX = 0;
    std::stringstream ss;
    ss << ++_SAMPLE_INDEX;
    std::string strId = ss.str();

    int randomNumber = qrand() * 100000;
    result->SetState((SessionStates)(qrand() % 5));
    result->setMediationTime(QDateTime::fromTime_t(randomNumber));
    result->setMediator1(QString::fromStdString("Mediator" + strId));
    result->setMediator2(QString::fromStdString("Mediator" + strId));
    result->setObserver1(QString::fromStdString("Observer " + strId));
    result->setObserver2(QString::fromStdString("Observer " + strId));

    return result;
}

void MediationSession::BuildToPDF(QTextCursor &cursor)
{
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertText("\nMediation Date: ");
    cursor.insertText(_mediationTime.toString("MMM dd, yyyy.  h:mm AP")+ "\n");
    cursor.insertText("Session Outcome: ");
    cursor.insertText(StringForSessionOutcomes(_outcome) + "\n");
    cursor.insertText("Schedule Status: ");
    cursor.insertText(StringForSessionStates(_state) + "\n");
    cursor.insertText("Requires shuttle: ");
    cursor.insertText(_isShuttle == true ? "Yes" : "No");
    cursor.insertText("Mediators: ");
    if((_mediator1 == "" || _mediator1.isEmpty()) && (_mediator2.isEmpty() || _mediator2 == ""))
        cursor.insertText("None");
    else
        cursor.insertText(_mediator1 + ",  "+ _mediator2 + "\n");
    cursor.insertText("Observers: ");
    if((_observer1 == "" || _observer1.isEmpty()) && (_observer2.isEmpty() || _observer2 == ""))
        cursor.insertText("None");
    else
        cursor.insertText(_observer1 + ",  " + _observer2 + "\n");
    for(int i = 0; i < (int)_clientSessionDataVector.size(); i++)
    {
        cursor.insertText("Client " + QString::number(i + 1) + "\n");
        _clientSessionDataVector.at(i)->print(cursor);

    }

}
