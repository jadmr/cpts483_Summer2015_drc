#ifndef TOOLBARMANAGER_H
#define TOOLBARMANAGER_H

#include <QObject>
#include <Mediator.h>
#include <QToolBar>


class MediatorArg;
class MediatorCallback;

/// List of Toolbar type enums
enum ToolbarTypes
{
    TOOLBAR_T_NONE,
    TOOLBAR_T_MEDIATION,
    TOOLBAR_T_MEDIATION_SEARCH,
    TOOLBAR_T_PERSON,
    TOOLBAR_T_PERSON_SEARCH,
    TOOLBAR_T_REPORTS
};

/// List of Toodbar button type enums
enum ToolbarButtonTypes
{
    TBTN_T_NONE         = 0x00,
    TBTN_T_SEARCH       = 0x01,
    TBTN_T_SAVE         = 0x02,
    TBTN_T_LOAD         = 0x04,
    TBTN_T_DELETE       = 0x08,
    TBTN_T_PRINT        = 0x10,
    TBTN_T_SAVE_TO_FILE = 0x20
};

// Wrap a callback and type for variadic arguments
/*!
 * \brief The ToolbarCallback struct
 */
struct ToolbarCallback
{
    ToolbarCallback(ToolbarButtonTypes a_btnType, MediatorCallback* a_callback) : btnType(a_btnType), callback(a_callback) {}
    ToolbarButtonTypes btnType;
    MediatorCallback* callback;
};

/*!
 * \brief The ToolbarManager class
 */
class ToolbarManager : public QObject
{
    Q_OBJECT

public:
    explicit ToolbarManager(QObject *parent = 0);
    static ToolbarManager& Instance();  // Singleton

    /*!
     * \brief AddAction
     * \param text
     * \param receiver
     * \param member
     * \param icon
     */
    void AddAction(const QString & text, const QObject * receiver, const char * member, QIcon icon);
    /*!
     * \brief AddAction
     * \param text
     * \param receiver
     * \param member
     */
    void AddAction(const QString & text, const QObject * receiver, const char * member);
    /*!
     * \brief Clear
     */
    void Clear();
    /*!
     * \brief GetToolbar
     * \return
     */
    QToolBar* GetToolbar() { return _toolbar; }
    /*!
     * \brief SetToolbar
     * \param toolbar
     */
    void SetToolbar(QToolBar* toolbar) { _toolbar = toolbar; }

private:
    virtual ~ToolbarManager();
    ToolbarTypes _currentType;
    QToolBar* _toolbar;
};

#endif // TOOLBARMANAGER_H
