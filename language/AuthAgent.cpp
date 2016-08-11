#include "AuthAgent.hh"

#include "Debug.hh"
#include "SessionUtils.hh"
#include "sql/User.hh"
#include "language/ReceiveFile.hh"

/* AuthAgentState ================================================================== */

AuthAgentState::AuthAgentState()
    : InitialState("authAgent")
{
    addTransition(new AuthAgentTransition, new AuthenticatedAgentState(this));
}

void AuthAgentState::exited(TransitionEvent * ) const
{
    DEBUG("AuthAgentState::exited()", true);
}

/* AuthenticatedAgentState ========================================================= */

AuthenticatedAgentState::AuthenticatedAgentState(const State * previousState)
    : State("authenticatedAgent")
{    
    addTransition(new ReceiveFileTransition, new ReceiveFileState(this));
}

void AuthenticatedAgentState::entered(TransitionEvent * event) const
{
    DEBUG("AuthenticatedAgentState::entered()", true);
}

/* AuthAgentTransition ============================================================= */

AuthAgentTransition::AuthAgentTransition()
    : QVariantHashTransition("login")
{
}

bool AuthAgentTransition::eventTest(TransitionEvent * event) const
{
    if ( ! QVariantHashTransition::eventTest(event))
        return false;

    QVariantHash         response;
    const QVariantHash & hash =
            TransitionVariantEvent::extractVariant(event).value<QVariantHash>();

    response["login"] = false;
    if ( ! hash.contains("email") || ! hash.contains("password"))
    {
        SessionUtils::sendMessage(event->machine(), response);
        return false;
    }

    const User user = User().findBy({ QArg("email", hash["email"].toString()) });

    if ( ! user.persisted() || user.password != hash["password"].toString())
    {
        // In error transition ?
        SessionUtils::sendMessage(event->machine(), response);
        return false;
    }

    QVariant    variant;

    variant.setValue(user);
    event->machine()->setData("user", variant);

    response["login"] = true;
    SessionUtils::sendMessage(event->machine(), response);

    return true;
}
