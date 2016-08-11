#include "CuteboxClient.hh"

#include <QVariantHash>

#include "Debug.hh"

#define WATCH_DELAY 30000
#define CHUNK_SIZE 10

CuteboxClient::CuteboxClient()
    : m_fileWatcher(WATCH_DELAY, CHUNK_SIZE),
      m_termReader(this)
{
    connect(&m_fileWatcher, SIGNAL(fileChanged(const FileChange &)),
            this, SLOT(sendFileChange(const FileChange &)));
    connect(&m_sender, SIGNAL(transfertMessage(qint32,QVariant)),
            this, SLOT(receiveCommandStatus(qint32, QVariant)));

    m_commandStatus["login"] = false;
}

void CuteboxClient::login(const QString & email, const QString & password)
{
    DEBUG("CuteboxClient::login()", true);
    QVariantHash    hash;

    hash["action"] = "login";
    hash["email"] = email;
    hash["password"] = password;

    m_sender.send(hash);

    m_commandStatus["login"] = false;
}

void CuteboxClient::start(const QString & host, quint16 port)
{
    m_fileWatcher.start();
    m_sender.start(host, port);
}

bool CuteboxClient::addFile(const QString & filepath)
{
    if (m_commandStatus["login"])
    {
        return m_fileWatcher.addFile(filepath);
    }

    qDebug() << "User not authenticated";
    return false;
}

void CuteboxClient::checkFiles()
{
    if (m_commandStatus["login"])
    {
        m_fileWatcher.checkFiles();
    }
    else
    {
        qDebug() << "User not authenticated";
    }
}

void CuteboxClient::sendFileChange(const FileChange & filechange)
{
    if (m_commandStatus["login"] == true)
    {
        QVariantHash    hash;

        hash["action"] = "receive-file";
        hash["offset"] = filechange.offset();
        hash["name"] = filechange.filepath();
        hash["size"] = filechange.filesize();
        hash["data"] = filechange.data();

        m_sender.send(hash);
    }
    else
    {
        qDebug() << "User not authenticated";
    }
}

void CuteboxClient::receiveCommandStatus(qint32 socketFd, const QVariant &message)
{
    (void) socketFd;

    QVariantHash    response = message.value<QVariantHash>();

    for (const QString & key : response.keys())
    {
        if (m_commandStatus.contains(key))
        {
            DEBUG("CuteboxClient::receiveCommandStatus() :" << key << " status :" << response[key].toBool(), true);
            m_commandStatus[key] = response[key].toBool();
        }
    }
}

