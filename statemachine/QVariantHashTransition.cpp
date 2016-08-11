#include "QVariantHashTransition.hh"

#include <QVariantHash>

#include "transitionvariantevent.h"

#include "language/SessionUtils.hh"
#include "Debug.hh"

QVariantHashTransition::QVariantHashTransition(const QString & action)
    : Transition(false),
      m_action(action)
{
}

bool QVariantHashTransition::eventTest(TransitionEvent * event) const
{
    const QVariant & variant = TransitionVariantEvent::extractVariant(event);
    const QVariantHash & hash = variant.value<QVariantHash>();

    if (hash.empty()|| ! hash.contains("action"))
    {
        SessionUtils::sendMessage(event->machine(), QVariant("{'status':400, 'error':'Invalid request format'}"));
        return false;
    }

    if (hash["action"] != m_action)
    {
        return false;
    }

    return true;
}
