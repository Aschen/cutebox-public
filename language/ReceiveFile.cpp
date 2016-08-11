#include "ReceiveFile.hh"

#include <QVariantHash>
#include <QFile>
#include <QDir>
#include <QDataStream>

#include "statemachine/varianttypetransition.h"
#include "statemachine/unconditionaltransition.h"
#include "statemachine/transitionutils.h"

#include "language/AuthAgent.hh"
#include "network/Client.hh"
#include "sql/User.hh"
#include "Debug.hh"
#include "SessionUtils.hh"

/* ReceiveFileState =============================================================== */

ReceiveFileState::ReceiveFileState(const State * previousState)
    : State("ReceiveFile")
{
    addTransition(new UnconditionalTransition, previousState);
}

void ReceiveFileState::entered(TransitionEvent * event) const
{
    DEBUG("ReceiveFileState::entered()", true);
    QVariantHash         response;
    const QVariantHash & hash =
            TransitionVariantEvent::extractVariant(event).value<QVariantHash>();

    const User  &user = event->machine()->data()["user"].value<User>();
    QString     dirname = QString("received_files/") + user.email + "/";
    if ( ! QDir(dirname).exists())
        QDir().mkdir(dirname);

    QFile       file(dirname + hash["name"].toString());

    if (file.open(QIODevice::ReadWrite) && file.seek(hash["offset"].toUInt()))
    {
        file.resize(hash["size"].toLongLong());
        file.write(hash["data"].toByteArray());

        response["receive-file"] = true;
        SessionUtils::sendMessage(event->machine(), response);
    }
    else
    {
        response["receive-file"] = false;
        SessionUtils::sendMessage(event->machine(), response);
    }

    event->machine()->postEvent(new TransitionEvent);
}

void ReceiveFileState::exited(TransitionEvent *) const
{
    DEBUG("ReceiveFileState::exited()", true);

}

/* ReceiveFileTransition ============================================================= */

ReceiveFileTransition::ReceiveFileTransition()
    : QVariantHashTransition("receive-file")
{
}

bool ReceiveFileTransition::eventTest(TransitionEvent * event) const
{
    if ( ! QVariantHashTransition::eventTest(event))
        return false;

    const QVariantHash & hash =
            TransitionVariantEvent::extractVariant(event).value<QVariantHash>();

    if ( ! hash.contains("name") || ! hash.contains("offset") || ! hash.contains("size") || ! hash.contains("data"))
    {
        QVariantHash         response;

        response["login"] = false;
        SessionUtils::sendMessage(event->machine(), response);
        return false;
    }

    return true;
}
