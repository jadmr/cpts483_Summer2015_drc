#ifndef MPTOOLBOX_H
#define MPTOOLBOX_H

#include <QToolBox>

#include "drctypes.h"
#include "mediationbrowser.h"
#include "sessionsbrowser.h"
#include "mediationprocess.h"
#include "notesbrowser.h"


namespace Ui {
class MPToolBox;
}

class MPToolBox : public QToolBox
{
    Q_OBJECT

public:
    explicit MPToolBox(QWidget *parent = 0);
//    static MPToolBox& Instance(QWidget *parent = 0);
    ~MPToolBox();

private:
    Ui::MPToolBox *ui;

    MediationBrowser* _mpBrowser;
    SessionsBrowser* _sessionsBrowser;
    NotesBrowser* _notesBrowser;
    // Track which indices the tables use (for enable/disable)
    int _mpBrowserIndex;
    int _sessionsBrowserIndex;
    int _notesBrowserIndex;

    void Configure();

    void EnableMediationsTable(MediationTableSortTypes sortType = MEDIATION_SORT_T_RECENT);
    void EnableSessionsTable(MediationSessionVector* sessions);
    void EnableNotesTable(MediationNotesVector* notes);

    void DisableMediationsTable();
    void DisableSessionsTable();
    void DisableNotesTable();

signals:
    void MPSelected(MediationProcess* process);

public slots:
    void DoMPSelected(MediationProcess* process) { emit MPSelected(process); }
};

#endif // MPTOOLBOX_H