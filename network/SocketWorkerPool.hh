#ifndef SOCKETWORKERPOOL_HH
# define SOCKETWORKERPOOL_HH

# include <QVector>

# include "SocketWorker.hh"

class SocketWorkerPool
{
private:
    quint32                         m_size;
    quint32                         m_index;
    QVector<SocketWorker*>          m_workers;

public:
    SocketWorkerPool(quint32 size);
    ~SocketWorkerPool();

    SocketWorker*                   get();

    const QVector<SocketWorker*>&   workers() const;
};

#endif // SOCKETWORKERPOOL_HH
