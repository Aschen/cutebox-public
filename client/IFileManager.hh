#ifndef IFILEMANAGER
# define IFILEMANAGER

# include <QVector>

# include "client/FileChange.hh"

class IFileManager
{
public:
    virtual bool                   addFile(const QString & filepath) = 0;
    virtual QVector<FileChange>    getChange() = 0;
};

#endif // IFILEMANAGER

