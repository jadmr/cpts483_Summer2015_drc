#ifndef PARTYDETAILSFORM_H
#define PARTYDETAILSFORM_H

#include <QWidget>
#include "drc_shared/models/Person.h"


namespace Ui {
class PartyDetailsForm;
}


class PartyDetailsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PartyDetailsForm(QWidget *parent = 0);
    ~PartyDetailsForm();

    void SetPerson(Person p) { _person = p; UpdateLabels(); }
    Person GetPerson() { return _person; }
private slots:
    void on_emailLineEdit_textChanged(const QString &arg1);

private:
    Ui::PartyDetailsForm *ui;

    Person _person;

    // This will set the labels based on Person object.
    void UpdateLabels();
};

#endif // PARTYDETAILSFORM_H
