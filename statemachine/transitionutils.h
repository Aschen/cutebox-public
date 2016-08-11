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

#ifndef TRANSITIONUTILS_H
#define TRANSITIONUTILS_H

#include "statemachine/state.h"
#include "statemachine/transition.h"
#include "statemachine/transitionevent.h"
#include "statemachine/stringtransition.h"
#include "statemachine/regexptransition.h"

class TransitionUtils
{
public:
    static QVariant data(const TransitionEvent * event, const QString & keyName, const QVariant & defaultValue = QVariant());
    static void setData(const TransitionEvent * event, const QString & keyName, const QVariant & variant);
};

// -----------------------------------------------------------------------------

class PushFakeEventOnTransition : public Transition
{
public:
    PushFakeEventOnTransition(Transition * proxy);

protected:
    void onTransition(TransitionEvent * event) const;
};

// -----------------------------------------------------------------------------

class AutoTransition : public UnconditionalTransition
{
public:
    AutoTransition(bool cascading = false);

protected:
    void onTransition(TransitionEvent * event) const;
};

// -----------------------------------------------------------------------------

class ReplayPreviousEventOnTransition : public Transition
{
public:
    ReplayPreviousEventOnTransition(Transition * proxy);

protected:
    void onTransition(TransitionEvent * event) const;
};

// -----------------------------------------------------------------------------

class AgentVersionTransition : public RegExpTransition
{
public:
    AgentVersionTransition();
};

// -----------------------------------------------------------------------------

class AgentIdTransition : public RegExpTransition
{
public:
    AgentIdTransition();
};

// -----------------------------------------------------------------------------

class MailTransition : public RegExpTransition
{
public:
    MailTransition();
};

#endif // TRANSITIONUTILS_H
