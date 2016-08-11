/******************************************************************************

            COPYRIGHT (c) 2008 - 2010 by RG Systèmes Corporation.
        This software has been provided pursuant to a License Agreement
        containing restrictions on its use.  This software contains
        valuable trade secrets and proprietary information of
        RG Systèmes Corporation and is protected by law. It may
        not be copied or distributed in any form or medium, disclosed
        to third parties, reverse engineered or used in any manner not
        provided for in said License Agreement except with the prior
        written authorization from RG Systèmes Corporation.

******************************************************************************/

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QtCore>

class State;
class InitialState;
class ErrorTransition;
class TransitionEvent;

class StateMachine
{
public:
    enum MachineState {
        Running = 0, // The machine is currently running (not on the intial or a final state)
        Delayed = 1, // The posted event has been delayed because it has been posted while the machine was evaluating
        FinalState = 2, // The machine has reach a final state
        Stalled = 3 // No transition has been selected, we cannot pass to another state
    };

    StateMachine(const InitialState * initialState);
    virtual ~StateMachine();

    void setDefaultErrorTransition(ErrorTransition * defaultErrorTransition);
    const ErrorTransition * defaultErrorTransition() const;

    void setData(const QVariantHash & data);
    QVariantHash data() const;

    void setData(const QString & keyName, const QVariant & variant);
    QVariant data(const QString & keyName, const QVariant & defaultData = QVariant()) const;
    void removeData(const QString & keyName);

    MachineState postEvent(TransitionEvent * event);

private:
    Q_DISABLE_COPY(StateMachine)

    const State * m_currentState;

    const ErrorTransition * m_defaultErrorTransition;
    QSharedPointer < TransitionEvent > m_previousEvent;

    QVariantHash m_data;
    bool m_evaluating;

    QQueue < QSharedPointer < TransitionEvent > > m_events;
};

#endif // STATEMACHINE_H
