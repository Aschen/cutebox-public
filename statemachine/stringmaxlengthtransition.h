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

#ifndef STRINGMAXLENGTHTRANSITION_H
#define STRINGMAXLENGTHTRANSITION_H

#include <QString>

#include "transition.h"

class StringMaxLengthTransition : public Transition
{
public:
    StringMaxLengthTransition(int maxLength);

protected:
    virtual bool eventTest(TransitionEvent * event) const;

private:
    int m_maxLength;
};

#endif // STRINGMAXLENGTHTRANSITION_H
