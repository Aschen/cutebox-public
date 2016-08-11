#include "SocketWorkerPool.hh"

#include "workerfactory.h"

SocketWorkerPool::SocketWorkerPool(quint32 size)
    : m_size(size),
      m_index(0),
      m_workers(m_size)
{
    // Create and start workers
    for (quint32 i = 0; i < m_size; ++i)
    {
        SocketWorker*   worker =
                WorkerFactory<SocketWorker>::create(nullptr, QString("Socket Worker %1").arg(i + 1));

        m_workers[i] = worker;

        WorkerFactory<SocketWorker>::go(worker);
    }
}

SocketWorkerPool::~SocketWorkerPool()
{
    for (SocketWorker* worker : m_workers)
    {
        worker->deleteLater();
    }
}

SocketWorker *SocketWorkerPool::get()
{
    SocketWorker*   worker = m_workers[m_index];

    m_index++;

    if (m_index >= m_size)
        m_index = 0;

    return worker;
}

const QVector<SocketWorker *> &SocketWorkerPool::workers() const
{
    return m_workers;
}

