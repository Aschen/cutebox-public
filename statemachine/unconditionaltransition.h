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

#ifndef UNCONDITIONALTRANSITION_H
#define UNCONDITIONALTRANSITION_H

#include "transition.h"

class UnconditionalTransition : public Transition
{
    friend class ErrorTransition;

public:
    UnconditionalTransition(bool cascading = false);

    void setCondition(bool condition);
    bool condition() const;

private:
    // A class inherting from Unconditionnal MUST be unconditionnal for ever
    virtual bool eventTest(TransitionEvent * event) const;

    bool m_condition;
};

#endif // UNCONDITIONALTRANSITION_H
