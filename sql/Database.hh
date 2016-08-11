#ifndef DATABASE_HH
#define DATABASE_HH

# include <QSqlDatabase>

class Database
{
private:
    QSqlDatabase    m_db;

public:
    ~Database();
    bool            initDatabase(const QString & databaseName = "cutebox.sqlite");
    bool            createTables();

// Singleton stuff =======================================
private:
    Database();
    Database(Database const & cpy);
    Database&   operator=(Database const & cpy);

public:
    static Database & instance()
    {
        static Database     instance;

        return instance;
    }

// =======================================================
};



#endif // DATABASE_HH
