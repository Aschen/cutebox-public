#include "Client.hh"

#include <QtCore/QMetaType>

#include "Debug.hh"
#include "language/SessionUtils.hh"
#include "language/AuthAgent.hh"

QString states[] = { "Running", "Delayed", "FinalState", "Stalled" };

Client::Client(qint32 socketFd)
    : AClient(new StateMachine(new AuthAgentState)),
      m_socketFd(socketFd)
{
}

void Client::receiveMessage(const QVariant & message)
{
    StateMachine::MachineState state;

    state = m_stateMachine->postEvent(new TransitionVariantEvent(message));
    DEBUG("State:" << states[state], true);
}

void Client::sendMessage(const QVariant & message)
{
    emit send(m_socketFd, message);
}
