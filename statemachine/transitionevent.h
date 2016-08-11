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

#ifndef TRANSITIONEVENT_H
#define TRANSITIONEVENT_H

#include <QEvent>

#include "statemachine.h"

class TransitionEvent : public QEvent
{
public:
    TransitionEvent(QEvent::Type type = QEvent::None);
    ~TransitionEvent();

    void setPreviousEvent(QSharedPointer < TransitionEvent > transitionEvent);
    TransitionEvent * previousEvent() const;

    void setMachine(StateMachine * machine);
    StateMachine * machine() const;

private:
    QSharedPointer < TransitionEvent > m_previousEvent;
    StateMachine * m_machine;
};

#endif // TRANSITIONEVENT_H
