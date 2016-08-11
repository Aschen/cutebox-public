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

#ifndef STATE_H
#define STATE_H

#include <QList>

#include "transition.h"
#include "errortransition.h"

class InitialState;

class State
{
    friend class StateMachine;

public:
    State(const QString & name = QString());
    virtual ~State();

    QString name() const;

    void addTransition(Transition * transition, const State * targetState);
    void addTransition(const Transition * transition);
    void setTransitions(const QList < const Transition * > & transitions);
    QList < const Transition * > transitions() const;

    void setErrorTransition(const ErrorTransition * errorTransition);
    const ErrorTransition * errorTransition() const;

    static QList < const State * > flatten(const State * state);

protected:
    virtual void entered(TransitionEvent * event) const;
    virtual void exited(TransitionEvent * event) const;

private:
    QString m_name;
    QList < const Transition * > m_transitions;
    const ErrorTransition * m_errorTransition;
};

class InitialState : public State
{
public:
    InitialState(const QString & name = QString());

    static int destroy(const InitialState * state);
};

#endif // STATE_H
