#include "mediationprocessstatusform.h"
#include "ui_mediationprocessstatusform.h"
#include "toolbarmanager.h"
#include <QLayout>
#include <QMessageBox>
#include <QtSql>
#include "DRCModels.h"
#include "Mediator.h"
#include "drcdb.h"

const QString SAVED_MSG = "Saved!";
const QString NOT_SAVED_MSG = "Unsaved Changes!";

MediationProcessStatusForm::MediationProcessStatusForm(QWidget *parent, MediationProcess* mediationProcess) :
    QWidget(parent),
    ui(new Ui::MediationProcessStatusForm),
  _mediationProcess(mediationProcess)
{
    ui->setupUi(this);
    _loading = true;
    SetSavedLabel(false);

    ui->saveStatusLabel->setVisible(false);
    ui->courtCheckBox->setChecked(false);
    ConfigureComboBoxes();

    Update();

    _SavePendingCallbackId = Mediator::Register(MKEY_GUI_MP_SAVE_PENDING, [this](MediatorArg){SetSavedLabel(false);});
    _PersistMPDoneCallbackId = Mediator::Register(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, [this](MediatorArg arg){MPSaveFinished(arg);});
    _LoadMPCallbackId = Mediator::Register(MKEY_GUI_MP_POPULATE, [this](MediatorArg arg){MPSaveFinished(arg);});
    _loading = false;
}
MediationProcessStatusForm::~MediationProcessStatusForm()
{
    Mediator::Unregister(MKEY_GUI_MP_SAVE_PENDING, _SavePendingCallbackId);
    Mediator::Unregister(MKEY_DB_PERSIST_MEDIATION_PROCESS_FORM_DONE, _PersistMPDoneCallbackId);
    Mediator::Unregister(MKEY_GUI_MP_POPULATE, _LoadMPCallbackId);
    delete ui;
}

void MediationProcessStatusForm::setMediationProcess(MediationProcess* value)
{
//    if(_mediationProcess == value) // same pointer
//        SetSavedLabel(true);

    _mediationProcess = value;
    Update();
}

void MediationProcessStatusForm::Update()
{

    if(!(ui && _mediationProcess)) return;
    _loading = true;
    // Preserve save label status
//    bool isSaved = ui->saveStatusLabel->text() == SAVED_MSG;

    ui->inquiryTypeComboBox->setCurrentIndex(_mediationProcess->GetInquiryType());
    ui->infoOnlyCheckBox->setChecked(_mediationProcess->GetInfoOnly());
    ui->dateEdit->setDate(_mediationProcess->GetCreatedDate().date());
    ui->currentStatusLabel->setText("Status: " + StringForDisputeProcessStates( _mediationProcess->GetState()));
    ui->spanishCheckBox->setChecked(_mediationProcess->GetRequiresSpanish());
    ui->conflictComboBox->setCurrentIndex(_mediationProcess->GetDisputeType());
    ui->countyComboBox->setCurrentIndex(_mediationProcess->GetCountyId());
    ui->referralComboBox->setCurrentIndex(_mediationProcess->GetReferralType());
    ui->printCourtDateCheckBox->setChecked(_mediationProcess->getPrintCourtDate());
    ui->courtCheckBox->setChecked(_mediationProcess->GetIsCourtCase());
    ui->courtTypeComboBox->setCurrentIndex(_mediationProcess->GetCourtType());
    ui->courDateEdit->setDate(_mediationProcess->GetCourtDate());
    ui->courtOrderLineEdit->setText(_mediationProcess->GetCourtOrder());
//    ui->courtOrderComboBox->setCurrentIndex(_mediationProcess->GetCourtOrderType());
//    ui->expirationDateTimeEdit->setDateTime(_mediationProcess->GetCourtOrderExpiration());
    sessionTypeDisplay();
    ui->mediationClauseCheckBox->setEnabled(false);
    //JAS Change to remove   ui->lastActivityDisplayLabel->setText(_mediationProcess->GetUpdatedDate().toString("MM/dd/yyyy"));
    if(_mediationProcess->GetDisputeType() == DISPUTE_T_PARENTING_PLAN)
    {
        ui->mediationClauseCheckBox->setEnabled(true);
        ui->mediationClauseCheckBox->setChecked(_mediationProcess->getMediationClause());
    }


    ui->statusMessageLabel->setStyleSheet("QLabel#statusMessageLabel { color : blue; font: italic; }");
    ui->statusMessageLabel->setText(_mediationProcess->GetStateMessage());
    ui->courtCheckBox->setChecked(_mediationProcess->GetIsCourtCase());
    ui->courtRow_3->setEnabled(_mediationProcess->GetIsCourtCase());
    //on_courtCheckBox_clicked();
     _loading = false;
//    SetSavedLabel(isSaved); // Preserve labels
}
//session type display function to set the radio buttons
void MediationProcessStatusForm::sessionTypeDisplay()
{
    _loading = true;
    switch (_mediationProcess->GetSessionType()){
    case MEDIATION_SESSION:
        ui->regularRadioButton->setChecked(true);
        break;
    case FACILITATION_SESSION:
        ui->facilitationRadioButton->setChecked(true);
        break;
    case PHONE_SESSION:
        ui->phoneRadioButton->setChecked(true);
        break;
    case COACHING_SESSION:
        ui->coachingRadioButton->setChecked(true);
        break;
    default:
        break;
    }
     _loading = false;
}

//update session type to update the model based off gui
void MediationProcessStatusForm::updateSessionType()
{
    if(_loading) return;
    if(ui->regularRadioButton->isChecked())
    {
        _mediationProcess->SetSessionType(MEDIATION_SESSION);
    }
    else if(ui->facilitationRadioButton->isChecked())
    {
        _mediationProcess->SetSessionType(FACILITATION_SESSION);
    }
    else if(ui->phoneRadioButton->isChecked())
    {
        _mediationProcess->SetSessionType(PHONE_SESSION);
    }
    else if(ui->coachingRadioButton->isChecked())
    {
        _mediationProcess->SetSessionType(COACHING_SESSION);
    }
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);

}

// Sets the values based on enums.
void MediationProcessStatusForm::ConfigureComboBoxes()
{
    for(int i = 0; i < 15; i++)
        ui->conflictComboBox->addItem(StringForDisputeTypes((DisputeTypes)i));

//    ui->conflictComboBox->setItemText(DISPUTE_T_NONE, StringForDisputeTypes(DISPUTE_T_NONE));
//    ui->conflictComboBox->setItemText(DISPUTE_T_PARENTING_PLAN, StringForDisputeTypes(DISPUTE_T_PARENTING_PLAN));
//    ui->conflictComboBox->setItemText(DISPUTE_T_DIVORCE, StringForDisputeTypes(DISPUTE_T_DIVORCE));
//    ui->conflictComboBox->setItemText(DISPUTE_T_SMALL_CLAIMS, StringForDisputeTypes(DISPUTE_T_SMALL_CLAIMS));
//    ui->conflictComboBox->setItemText(DISPUTE_T_TENANT, StringForDisputeTypes(DISPUTE_T_TENANT));
//    ui->conflictComboBox->setItemText(DISPUTE_T_LANDLORD, StringForDisputeTypes(DISPUTE_T_LANDLORD));
//    ui->conflictComboBox->setItemText(DISPUTE_T_CONSUMER_MERCHANT, StringForDisputeTypes(DISPUTE_T_CONSUMER_MERCHANT));
//    ui->conflictComboBox->setItemText(DISPUTE_T_WORKPLACE, StringForDisputeTypes(DISPUTE_T_WORKPLACE));
//    ui->conflictComboBox->setItemText(DISPUTE_T_NEIGHBORHOOD, StringForDisputeTypes(DISPUTE_T_NEIGHBORHOOD));
//    ui->conflictComboBox->setItemText(DISPUTE_T_FAMILY, StringForDisputeTypes(DISPUTE_T_FAMILY));
//    ui->conflictComboBox->setItemText(DISPUTE_T_PROPERTY_BUSINESS, StringForDisputeTypes(DISPUTE_T_PROPERTY_BUSINESS));
//    ui->conflictComboBox->setItemText(DISPUTE_T_PARENT_TEEN, StringForDisputeTypes(DISPUTE_T_PARENT_TEEN));
//    ui->conflictComboBox->setItemText(DISPUTE_T_VICTIM_OFFENDER, StringForDisputeTypes(DISPUTE_T_VICTIM_OFFENDER));
//    ui->conflictComboBox->setItemText(DISPUTE_T_OTHER, StringForDisputeTypes(DISPUTE_T_OTHER));
//    ui->conflictComboBox->setItemText(DISPUTE_T_FORECLOSURE,StringForDisputeTypes(DISPUTE_T_FORECLOSURE));

    ui->countyComboBox->setItemText(COUNTY_NONE, StringForCountyIds(COUNTY_NONE));
    ui->countyComboBox->setItemText(COUNTY_BENTON, StringForCountyIds(COUNTY_BENTON));
    ui->countyComboBox->setItemText(COUNTY_FRANLKIN, StringForCountyIds(COUNTY_FRANLKIN));
    ui->countyComboBox->setItemText(COUNTY_GRANT, StringForCountyIds(COUNTY_GRANT));
    ui->countyComboBox->setItemText(COUNTY_ADAMS, StringForCountyIds(COUNTY_ADAMS));
    ui->countyComboBox->setItemText(COUNTY_WALLAWALLA, StringForCountyIds((COUNTY_WALLAWALLA)));
    ui->countyComboBox->setItemText(COUNTY_OTHER, StringForCountyIds(COUNTY_OTHER));

    ui->referralComboBox->setItemText(REFERRAL_T_NONE, StringForReferralTypes(REFERRAL_T_NONE));
    ui->referralComboBox->setItemText(REFERRAL_T_FAMILY_FRIEND, StringForReferralTypes(REFERRAL_T_FAMILY_FRIEND));
    ui->referralComboBox->setItemText(REFERRAL_T_ATTORNEY, StringForReferralTypes(REFERRAL_T_ATTORNEY));
    ui->referralComboBox->setItemText(REFERRAL_T_LEGAL_SERVICES, StringForReferralTypes(REFERRAL_T_LEGAL_SERVICES));
    ui->referralComboBox->setItemText(REFERRAL_T_RETURN_CLIENTS, StringForReferralTypes(REFERRAL_T_RETURN_CLIENTS));
    ui->referralComboBox->setItemText(REFERRAL_T_PRIVATE_AGENCY, StringForReferralTypes(REFERRAL_T_PRIVATE_AGENCY));
    ui->referralComboBox->setItemText(REFERRAL_T_COURTS, StringForReferralTypes(REFERRAL_T_COURTS));
    ui->referralComboBox->setItemText(REFERRAL_T_COURT_SOLICITED, StringForReferralTypes(REFERRAL_T_COURT_SOLICITED));
    ui->referralComboBox->setItemText(REFERRAL_T_LAW_ENFORCEMENT, StringForReferralTypes(REFERRAL_T_LAW_ENFORCEMENT));
    ui->referralComboBox->setItemText(REFERRAL_T_DCFS_JJC_GOVT_AGENCY, StringForReferralTypes(REFERRAL_T_DCFS_JJC_GOVT_AGENCY));
    ui->referralComboBox->setItemText(REFERRAL_T_ATTORNEY_GENERALS_OFFICE, StringForReferralTypes(REFERRAL_T_ATTORNEY_GENERALS_OFFICE));
    ui->referralComboBox->setItemText(REFERRAL_T_PRESENTATION_TRAINING, StringForReferralTypes(REFERRAL_T_PRESENTATION_TRAINING));
    ui->referralComboBox->setItemText(REFERRAL_T_ADVERTISING, StringForReferralTypes(REFERRAL_T_ADVERTISING));
    ui->referralComboBox->setItemText(REFERRAL_T_PHONEBOOK, StringForReferralTypes(REFERRAL_T_PHONEBOOK));
    ui->referralComboBox->setItemText(REFERRAL_T_INTERNET, StringForReferralTypes(REFERRAL_T_INTERNET));
    ui->referralComboBox->setItemText(REFERRAL_T_OTHER_NONE, StringForReferralTypes(REFERRAL_T_OTHER_NONE));

    ui->inquiryTypeComboBox->setItemText(INQUIRY_T_NONE, StringForInquiryTypes(INQUIRY_T_NONE));
    ui->inquiryTypeComboBox->setItemText(INQUIRY_T_EMAIL, StringForInquiryTypes(INQUIRY_T_EMAIL));
    ui->inquiryTypeComboBox->setItemText(INQUIRY_T_PHONE, StringForInquiryTypes(INQUIRY_T_PHONE));
    ui->inquiryTypeComboBox->setItemText(INQUIRY_T_REFERRAL, StringForInquiryTypes(INQUIRY_T_REFERRAL));
    ui->inquiryTypeComboBox->setItemText(INQUIRY_T_WALKIN, StringForInquiryTypes(INQUIRY_T_WALKIN));

    ui->courtTypeComboBox->setItemText(COURT_T_NONE, StringForCourtTypes(COURT_T_NONE));
    ui->courtTypeComboBox->setItemText(COURT_T_JUVENILE, StringForCourtTypes(COURT_T_JUVENILE));
    ui->courtTypeComboBox->setItemText(COURT_T_OTHER, StringForCourtTypes(COURT_T_OTHER));
    ui->courtTypeComboBox->setItemText(COURT_T_SMALL_CLAIMS, StringForCourtTypes(COURT_T_SMALL_CLAIMS));
    ui->courtTypeComboBox->setItemText(COURT_T_SUPERIOR, StringForCourtTypes(COURT_T_SUPERIOR));

   // ui->courtOrderComboBox->setItemText(COURT_ORDER_T_NONE, StringForCourtOrderTypes(COURT_ORDER_T_NONE));
}

void MediationProcessStatusForm::on_conflictComboBox_currentIndexChanged(int index)
{
    if(_loading) return;
    if((int)_mediationProcess->GetDisputeType() == index) return;

    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
    _mediationProcess->SetDisputeType((DisputeTypes)index);
    Update();
}

void MediationProcessStatusForm::on_statusComboBox_currentIndexChanged(int index)
{
//    _mediationProcess->SetState((DisputeProcessStates)index);
//    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_countyComboBox_currentIndexChanged(int index)
{
    if(_loading) return;
        if((int)_mediationProcess->GetCountyId() == index) return;

        _mediationProcess->SetCountyId((CountyIds)index);

}

void MediationProcessStatusForm::on_referralComboBox_currentIndexChanged(int index)
{
    if(_loading) return;

    if((int)_mediationProcess->GetReferralType() == index) return;

    _mediationProcess->SetReferralType((ReferralTypes)index);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::SetSavedLabel(bool isSaved)
{
    if(!ui) return;

    if(!isSaved)
    {
        SetStatusLabel(NOT_SAVED_MSG, true);
    }
    else
    {
        SetStatusLabel(SAVED_MSG);
    }
}

void MediationProcessStatusForm::SetStatusLabel(QString message, bool isError)
{
    if(!ui || !_mediationProcess) return;

    ui->saveStatusLabel->setVisible(true);
    if(isError)
    {
        ui->notSavedLabel->setStyleSheet("QLabel#notSavedLabel { color : red; }");
        ui->saveStatusLabel->hide();
        ui->notSavedLabel->show();
        ui->notSavedLabel->setText(message);
    }
    else
    {
        ui->saveStatusLabel->setStyleSheet("QLabel#saveStatusLabel { color : green; }");
        ui->notSavedLabel->hide();
        ui->saveStatusLabel->show();
        ui->saveStatusLabel->setText(message);
    }
}

void MediationProcessStatusForm::MPSaveFinished(MediatorArg arg)
{
    SetSavedLabel(arg.IsSuccessful());

    //    if(arg.ErrorMessage().length())
    //        ui->statusMessageLabel->setText(arg.ErrorMessage());
    Update();
}

void MediationProcessStatusForm::on_courtCheckBox_clicked()
{

    bool isCourtCase = ui->courtCheckBox->isChecked();
    // Block the save label from getting overriden during gui loading
    if(isCourtCase != _mediationProcess->GetIsCourtCase())
    {
        _mediationProcess->SetIsCourtCase(isCourtCase);
        SetSavedLabel(false);
        ui->courtRow_3->setEnabled(isCourtCase);
    }
}

void MediationProcessStatusForm::on_courtTypeComboBox_currentIndexChanged(int index)
{
    if(_loading) return;
    if((int)_mediationProcess->GetCourtType() == index) return;

    _mediationProcess->SetCourtType((CourtCaseTypes)index);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_courDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    if(_loading) return;
    if(_mediationProcess->GetCourtDate() == dateTime.date()) return;

    _mediationProcess->SetCourtDate(ui->courDateEdit->date());
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_courtOrderComboBox_currentIndexChanged(int index)
{
//    _mediationProcess->SetCourtOrderType((CourtOrderTypes)index);
//    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_expirationDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
//    _mediationProcess->SetCourtOrderExpiration(dateTime);
//    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_inquiryTypeComboBox_currentIndexChanged(int index)
{
    if(_loading) return;
    if((int)_mediationProcess->GetInquiryType() == index) return;

    _mediationProcess->SetInquiryTypes((InquiryTypes)index);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_infoOnlyCheckBox_toggled(bool checked)
{
    if(_loading) return;
    if(_mediationProcess->GetInfoOnly() == checked) return;

    _mediationProcess->SetInfoOnly(checked);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_spanishCheckBox_clicked(bool checked)
{
    if(_loading) return;
    if(_mediationProcess->GetRequiresSpanish() == checked) return;

    _mediationProcess->SetRequiresSpanish(checked);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_regularRadioButton_clicked() // ???
{
    updateSessionType();
}

void MediationProcessStatusForm::on_facilitationRadioButton_clicked()
{
    updateSessionType();
}

void MediationProcessStatusForm::on_phoneRadioButton_clicked()
{
    updateSessionType();
}

void MediationProcessStatusForm::on_mediationClauseCheckBox_toggled(bool checked)
{
    if(_loading) return;
    if(_mediationProcess->getMediationClause() == checked) return;

    _mediationProcess->setMediationClause(checked);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_coachingRadioButton_clicked()
{
    updateSessionType();
}

void MediationProcessStatusForm::on_courtOrderLineEdit_textEdited(const QString &arg1)
{
    if(_loading) return;
    if(_mediationProcess->GetCourtOrder() == arg1) return;

    _mediationProcess->SetCourtOrder(arg1);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}



void MediationProcessStatusForm::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
//    if(_loading) return;
//    _mediationProcess->SetCreatedDate(dateTime);
//    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_dateEdit_dateChanged(const QDate &date)
{
    if(_loading) return;
    QDateTime a = _mediationProcess->GetCreatedDate();
    a.setDate(date);
    _mediationProcess->SetCreatedDate(a);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_courDateEdit_dateChanged(const QDate &date)
{
    if(_loading) return;
    _mediationProcess->SetCourtDate(date);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_printCourtDateCheckBox_toggled(bool checked)
{
    if(_loading) return;
    _mediationProcess->setPrintCourtDate(checked);
    Mediator::Call(MKEY_GUI_MP_SAVE_PENDING);
}

void MediationProcessStatusForm::on_deleteMediationButton_clicked()
{
    QMessageBox msgBox;
    msgBox.addButton(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setText("Are you sure you want to Delete this Intake?");

    int selection = msgBox.exec();

    if(selection == QMessageBox::Yes)
    {
        MediatorArg arg = _mediationProcess;

        Mediator::Call(MKEY_GUI_REQUEST_DELETE_INTAKE, arg); //sends delete request to DB through BL
        Mediator::Call(MKEY_GUI_ENABLE_MENUS); //Takes user to Main Menu
        Mediator::Call(MKEY_DOCK_REQUEST_PENDING_MEDIATIONS); //Refresh the Browser Toolbox to clear deleted record

    }
}
