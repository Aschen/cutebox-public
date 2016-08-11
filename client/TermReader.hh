#ifndef TERMREADER_HH
# define TERMREADER_HH

# include <QSocketNotifier>
# include <QString>
# include <QHash>

class CuteboxClient;

class TermReader : public QObject
{
    Q_OBJECT

private:
    CuteboxClient*          m_client;
    QSocketNotifier         m_notifier;
    QHash<QString, QString> m_commandsHelp;

public:
    TermReader(CuteboxClient * client);

signals:
    void        inputReceived(const QString & command);

private slots:
    void        readInput();
};

#endif // TERMREADER_HH
