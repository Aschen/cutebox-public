#include "SessionUtils.hh"

# include "network/AClient.hpp"
# include "statemachine/statemachine.h"

void SessionUtils::sendMessage(const StateMachine * statemachine, const QVariant & message)
{
    SessionUtils::getClient(statemachine)->sendMessage(message);
}

AClient *SessionUtils::getClient(const StateMachine * statemachine)
{
    return statemachine->data("client").value<AClient*>();
}

SessionUtils::SessionUtils()
{
}

