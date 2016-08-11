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

#ifndef TRANSITIONVARIANTEVENT_H
#define TRANSITIONVARIANTEVENT_H

#include <QVariant>

#include "transitionevent.h"

class TransitionVariantEvent : public TransitionEvent
{
public:
    TransitionVariantEvent(const QVariant & variant = QVariant());

    void setVariant(const QVariant & variant);
    QVariant variant() const;

    template < class T >
    T value() const;

    static QEvent::Type eventType();
    static QVariant extractVariant(const TransitionEvent * event);
    template < class T >
    static T extractVariant(const TransitionEvent * event);
    static QVariantList extractPreviousVariants(const TransitionEvent * event);

private:
    QVariant m_variant;
};

template <>
QVariantHash TransitionVariantEvent::extractVariant(const TransitionEvent * event);

#endif // TRANSITIONVARIANTEVENT_H
