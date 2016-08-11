#ifndef SOCKETWORKER_HH
# define SOCKETWORKER_HH

# include <QVariant>
# include <QMap>
# include <QSharedPointer>
# include <QMutexLocker>

# include "abstractworker.h"
# include "Client.hh"
# include "BaseSocket.hh"

class SocketWorker : public AbstractWorker<QObject>
{
    Q_OBJECT

private:
    QMutex                                  m_mutex;
    QMap<qint32, QSharedPointer<Client>>    m_clients;

public:
    SocketWorker();
    ~SocketWorker();

    void        addSocket(BaseSocket * socket);

signals:
    void        send(qint32 socketFd, const QVariant & data) const;

public slots:
    void        start() Q_DECL_OVERRIDE;
    void        stop() Q_DECL_OVERRIDE;

    void        messageReceived(qint32 socketFd, const QVariant & data) const;
    void        clientDisconnected(qint32 socketFd);
};

#endif // SOCKETWORKER_HH
