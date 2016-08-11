#include "FileWatcher.hh"

#include "Debug.hh"

FileWatcher::FileWatcher(qint32 watchDelay, quint64 chunkSize)
    : m_watchDelay(watchDelay),
      m_chunkSize(chunkSize)
{
}

bool FileWatcher::addFile(const QString & filepath)
{
    QFile       file(filepath);

    if ( ! file.exists())
    {
        DEBUG("FileWatcher::add() : File" << filepath << " doesn't exist", true);
        return false;
    }

    for (const FileInfos & file : m_files)
    {
        if (file.filepath() == filepath)
        {
            DEBUG("FileWatcher::add() : File" << filepath << " is already watched", true);
            return false;
        }
    }

    DEBUG("FileWatcher::addFile() : add file" << filepath, true);
    m_files.push_back(FileInfos(filepath, m_chunkSize));
    emit fileChanged(FileChange(filepath, 0));

    return true;
}

void FileWatcher::start()
{
    m_timer.setSingleShot(false);
    m_timer.start(m_watchDelay);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(checkFiles()));
}

const QVector<FileInfos> &FileWatcher::files() const
{
    return m_files;
}

quint32 FileWatcher::checkFiles()
{
    DEBUG("FileWatcher::checkFiles() : check for file changes", true);
    // Error when chunkSize is bigger than file size
    quint32     count = 0;
    QVector<FileInfos>  newFiles;


    for (const FileInfos & oldFile : m_files)
    {
        FileInfos                   newFile(oldFile.filepath(), oldFile.chunkSize());
        // Resize smallest hash ?
        const QVector<QByteArray>   &newHashs = newFile.hashs();
        const QVector<QByteArray>   &oldHashs = oldFile.hashs();

        for (qint32 i = 0; i < newHashs.size(); ++i)
        {
            if (i >= oldHashs.size() || oldHashs[i] != newHashs[i])
            {
                count++;
                emit fileChanged(FileChange(oldFile.filepath(), i * oldFile.chunkSize()));
                break;
            }
        }

        newFiles.push_back(newFile);
    }

    m_files = newFiles;

    return count;
}

