#include "Server.hh"
#include "Debug.hh"

#include "BaseSocket.hh"

Server::Server(quint16 port, QObject * parent)
    : QTcpServer(parent),
      m_port(port),
      m_listenAddress(QHostAddress::Any),
      m_clientCount(0),
      m_workerPool(QThread::idealThreadCount() - 1)
{
    DEBUG("Server::Server()", false);
    QThread::idealThreadCount ();
}

Server::~Server()
{
    DEBUG("Server::~Server()", false);
}

void Server::start()
{
    if (isListening())
    {
        DEBUG("Server::start() : Server is already started", true);
        return;
    }

    if ( ! listen(m_listenAddress, m_port))
    {
        DEBUG("Server::start() : Server error listen", true);
        return;
    }

    DEBUG("Server::start() : Listening on port" << m_port, true);
}

void Server::incomingConnection(qintptr socketFd)
{
    DEBUG("Server::incomingConnection() : New connection" << socketFd, true);

    m_clientCount++;

    SocketWorker*   worker = m_workerPool.get();

    // Set worker as socket parent to prevent memory leak    
    BaseSocket*     socket = new BaseSocket(socketFd, worker);

    socket->setDescriptor();

    connect(socket, SIGNAL(clientDisconnected(qint32)),
            this,   SLOT(clientDisconnected(qint32)));

    worker->addSocket(socket);
}

void Server::clientDisconnected(qint32 socketFd)
{
    Q_UNUSED(socketFd);
    m_clientCount--;
}

quint32 Server::clientCount() const
{
    return m_clientCount;
}
