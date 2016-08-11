#include <QCoreApplication>

#include "network/Server.hh"
#include "Debug.hh"
#include "client/CuteboxClient.hh"
#include "sql/Database.hh"
#include "sql/User.hh"

#include <string>
#include <iostream>

void startServer()
{
    Server*     server;

    Database::instance().initDatabase();

    server = new Server(4242);
    server->start();
}

void startClient()
{
    CuteboxClient*   client = new CuteboxClient;
}

void populateDatabase()
{
    Database::instance().initDatabase("cuteboxlite.sqlite");
    Database::instance().createTables();

    if ( ! User().findBy({ QArg("email", "root@root.org")}).persisted())
    {
        User().create ({ QArg("email", "root@root.org"), QArg("password", "azerty") });
        qDebug() << "User root@root.org:azerty created";
    }

    if ( ! User().findBy({ QArg("email", "aschen@aschen.ovh")}).persisted())
    {
        User    aschen;
        aschen.email = "aschen@aschen.ovh";
        aschen.password = "rootme";
        aschen.save();
        qDebug() << "User aschen@aschen.ovh:rootme created";
    }

    qDebug() << "Database populated";
    qDebug() << "Hit CTRL + C to quit";
}

int main(int ac, char *av[])
{
    QCoreApplication app(ac, av);

    std::string input;

    if (ac > 1)
    {
        input = av[1];
    }
    else
    {
        DEBUG("Server (srv) or Client (cli) ?", true);
        std::cin >> input;
    }

    if (input == "srv")
        startServer();
    else if (input == "cli")
        startClient();
    else if (input == "seed")
        populateDatabase();

    return app.exec();
}
