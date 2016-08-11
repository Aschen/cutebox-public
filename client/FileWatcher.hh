#ifndef FILEWATCHER_HH
# define FILEWATCHER_HH

# include <QTimer>
# include <QVector>
# include <QFile>

# include "FileInfos.hh"
# include "client/FileChange.hh"

class FileWatcher : public QObject
{
    Q_OBJECT

private:
    qint32                              m_watchDelay;
    quint64                             m_chunkSize;
    QVector<FileInfos>                  m_files;
    QTimer                              m_timer;

public:
    FileWatcher(qint32 watchDelay = 42, quint64 chunkSize = 200);

    bool                        addFile(const QString & filepath);
    void                        start();

    const QVector<FileInfos>    &files() const;

public slots:
    quint32                     checkFiles();

signals:
    void                        fileChanged(const FileChange & fileChange);

};

#endif // FILEWATCHER_HH
