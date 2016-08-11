#ifndef CUTEBOXCLIENT_HH
# define CUTEBOXCLIENT_HH

# include <QHash>

# include "client/FileWatcher.hh"
# include "client/Sender.hh"
# include "client/TermReader.hh"

class CuteboxClient : public QObject
{
    Q_OBJECT

private:
    Sender                  m_sender;
    FileWatcher             m_fileWatcher;
    TermReader              m_termReader;
    QHash<QString, bool>    m_commandStatus;

public:
    CuteboxClient();

    void                login(const QString & email, const QString & password);
    void                start(const QString &host, quint16 port);
    bool                addFile(const QString &filepath);

    //debug
    void                checkFiles();

public slots:
    void                sendFileChange(const FileChange & filechange);
    void                receiveCommandStatus(qint32 socketFd, const QVariant &message);
};

#endif // CUTEBOXCLIENT_HH
