#ifndef SERVER_HH
# define SERVER_HH

# include <QTcpServer>
# include <QVariant>

# include "SocketWorkerPool.hh"

/**
 * @brief The Server class listen for new client and can receive or send message to any client
 */
class Server : public QTcpServer
{
    Q_OBJECT

private:
    quint16                     m_port;
    QHostAddress                m_listenAddress;
    quint32                     m_clientCount;
    SocketWorkerPool            m_workerPool;

public:
    Server(quint16 port, QObject * parent = nullptr);
    ~Server();

    void                        start();

    quint32                     clientCount() const;

    // QTcpServer override
    void                        incomingConnection(qintptr socketFd) Q_DECL_OVERRIDE;


public slots:
    void                        clientDisconnected(qint32 socketFd);
};

#endif // SERVER_HH
