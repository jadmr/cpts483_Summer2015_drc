#include "sessionoverview.h"
#include "ui_sessionoverview.h"

SessionOverview::SessionOverview(QWidget *parent, MediationSessionVector *mediationSessionVector) :
    QWidget(parent),  
    ui(new Ui::SessionOverview),
    _mediationSessionVector(mediationSessionVector ? mediationSessionVector : new MediationSessionVector())
{
    ui->setupUi(this);

    updateView();
}

SessionOverview::~SessionOverview()
{
    delete ui;
}

void SessionOverview::updateView()
{
     _numberOfSessions = _mediationSessionVector->size();
    if(_numberOfSessions > 0)
    {
        ui->sessionCreationDateDisplayLabel->setText(_mediationSessionVector->at(0)->GetCreatedDate().toString());
        ui->sessionFeeStatusDisplayLabel->setText(_mediationSessionVector->at(0)->getFeeStatus());
        ui->sessionStatusDisplayLabel->setText(_mediationSessionVector->at(0)->getStatus());
        if(!_mediationSessionVector->at(0)->getMediationTime().isNull())
            ui->sessionScheduleDisplayLabel->setText(_mediationSessionVector->at(0)->getMediationTime().toString());
    }
        ui->numSessionsDisplayLabel->setText(QString::number(_numberOfSessions));
}

void SessionOverview::setNumberOfSessions(uint value)
{
    _numberOfSessions = value;
}

void SessionOverview::on_pushButton_clicked()
{
    MediationSession *temp = new MediationSession();
    _mediationSessionVector->push_back(temp);
    updateView();
}
