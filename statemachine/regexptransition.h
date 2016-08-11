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

#ifndef REGEXPTRANSITION_H
#define REGEXPTRANSITION_H

#include <QRegExp>

#include "transition.h"

class RegExpTransition : public Transition
{
public:
    RegExpTransition(const QRegExp & regexp, bool cascading = true);

protected:
    virtual bool eventTest(TransitionEvent * event) const;

private:
    QRegExp m_regexp;
};

#endif // REGEXPTRANSITION_H
