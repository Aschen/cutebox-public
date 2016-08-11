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

#ifndef ERRORTRANSITION_H
#define ERRORTRANSITION_H

#include "transitionevent.h"
#include "unconditionaltransition.h"

class ErrorTransition : public UnconditionalTransition
{
public:
    ErrorTransition();
    ~ErrorTransition();

protected:
    virtual void onTransition(TransitionEvent * event) const;

private:
    // We overload this friendly function to assert something important
    virtual bool eventTest(TransitionEvent * event) const;

    State * m_state;
};

#endif // ERRORTRANSITION_H
