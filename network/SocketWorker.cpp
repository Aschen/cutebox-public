#include "SocketWorker.hh"

#include "Debug.hh"

SocketWorker::SocketWorker()
{
}

SocketWorker::~SocketWorker()
{
}

void SocketWorker::addSocket(BaseSocket * socket)
{
    QMutexLocker    lock(&m_mutex);

    qint32 socketFd = socket->socketDescriptor();

    m_clients[socketFd] = QSharedPointer<Client>(new Client(socketFd));

    // Connect communications functions for the new socket
    connect(m_clients[socketFd].data(), SIGNAL(send(qint32, const QVariant &)),
            socket,                     SLOT(send(qint32, const QVariant &)));

    connect(socket, SIGNAL(message(qint32, const QVariant &)),
            this,   SLOT(messageReceived(qint32, const QVariant &)));
    connect(socket, SIGNAL(clientDisconnected(qint32)),
            this,   SLOT(clientDisconnected(qint32)));

    socket->moveToThread(this->thread());
}

void SocketWorker::start()
{
    DEBUG("SocketWorker::start()", false);
}

void SocketWorker::stop()
{
    DEBUG("SocketWorker::stop()", true);
}

void SocketWorker::messageReceived(qint32 socketFd, const QVariant & data) const
{
    DEBUG("SocketWorker::messageReceived() : Socket" << socketFd << " message " << data, false);

    m_clients[socketFd]->receiveMessage(data);
}

void SocketWorker::clientDisconnected(qint32 socketFd)
{
    DEBUG("SocketWorker::clientDisconnected() : Socket" << socketFd, true);
    m_clients.remove(socketFd);
}

