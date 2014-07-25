/*
 * this class is to test and update the state transition of a mediation process.
 * after everything is implemented all that should be required is create the class with the mediation
 * process as argument.
 */


#ifndef STATEUPDATE_H
#define STATEUPDATE_H

#include "mediationprocess.h"
#include "drctypes.h"

/*!
 * \brief The StateUpdate class
 */
class StateUpdate
{
public:
    StateUpdate();
    /*!
     * \brief StateCheck
     * \param arg
     * \param errorMessage
     * \param stateMessage
     * \return
     */
    bool StateCheck(MediationProcess *arg, QString &errorMessage, QString &stateMessage);
private:
    QString _errorMessage;
    QString _stateMessage;
    bool _infoOnly;
    /*!
     * \brief startState
     * \param arg
     * \return
     */
    bool startState(MediationProcess *arg);
    /*!
     * \brief info
     * \param arg
     * \return
     */
    bool info(MediationProcess *arg);
    /*!
     * \brief initiated
     * \param arg
     * \return
     */
    bool initiated(MediationProcess* arg);
    /*!
     * \brief unique
     * \param arg
     * \return
     */
    bool unique(MediationProcess *arg);
    /*!
     * \brief clientinfo
     * \param arg
     * \return
     */
    bool clientinfo(MediationProcess *arg);
    /*!
     * \brief fees
     * \param arg
     * \return
     */
    bool fees(MediationProcess *arg);
    /*!
     * \brief mediators
     * \param arg
     * \return
     */
    bool mediators(MediationProcess *arg);
    /*!
     * \brief scheduled
     * \param arg
     * \return
     */
    bool scheduled(MediationProcess *arg);
    /*!
     * \brief outcome
     * \param arg
     * \return
     */
    bool outcome(MediationProcess *arg);
    /*!
     * \brief closed
     * \param arg
     * \return
     */
    bool closed(MediationProcess *arg);
    /*!
     * \brief ValidateName
     * \param name
     * \return
     */
    bool ValidateName(QString name);
    /*!
     * \brief StateToString
     * \return
     */
    QString StateToString(DisputeProcessInternalStates);
    /*!
     * \brief GetExternalState
     * \param arg
     */
    void GetExternalState(MediationProcess* arg);
};

#endif // STATEUPDATE_H
