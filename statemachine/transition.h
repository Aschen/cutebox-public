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

#ifndef TRANSITION_H
#define TRANSITION_H

#include "transitionevent.h"

class Transition
{
    friend class StateMachine;

public:
    Transition(bool cascading = false);
    Transition(Transition * proxy);
    virtual ~Transition();

    void setCascading(bool cascading);
    bool cascading() const;

    void setTargetState(const State * targetState);
    const State * targetState() const;

protected:
    virtual bool eventTest(TransitionEvent * event) const;
    virtual void onTransition(TransitionEvent * event) const;

private:
    bool m_cascading;

    const State * m_targetState;

    Transition * m_proxy;
};

#endif // TRANSITION_H
