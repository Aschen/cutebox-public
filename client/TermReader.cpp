#include "TermReader.hh"

#include <QTextStream>
#include <QCoreApplication>

#include <iostream>

# include "client/CuteboxClient.hh"

TermReader::TermReader(CuteboxClient * client)
    : m_client(client),
      m_notifier(0, QSocketNotifier::Read)
{
    connect(&m_notifier, SIGNAL(activated(int)), this, SLOT(readInput()));
    std::cout << "Command to send ? (type 'help' for help)" << std::endl << "> " << std::flush;
    m_commandsHelp["connect"] = " - connect <host> <port> : Connect to the server";
    m_commandsHelp["login"] = " - login <email> <password> : Authenticate to the server";
    m_commandsHelp["addfile"] = " - addfile <filepath> : Add file to be watched";
    m_commandsHelp["check"] = " - check : Force file change detection";
    m_commandsHelp["help"] = " - help : Display this help";
    m_commandsHelp["exit"] = " - exit : Quit application";
}

void TermReader::readInput()
{
    QTextStream in(stdin);
    QString     command;

    in >> command;

    if (command == "exit")
    {
        QCoreApplication::exit();
        return;
    }

    if (command == "connect")
    {
        QString     host;
        quint16     port = 0;

        in >> host >> port;
        if (host != "" && port != 0)
        {
            m_client->start(host, port);
        }
        else
        {
            qDebug() << m_commandsHelp["connect"];
        }
        return;
    }

    if (command == "login")
    {
        QString     email, password;

        in >> email >> password;
        if (email != "" && password != "")
        {
            m_client->login(email, password);
        }
        else
        {
            qDebug() << m_commandsHelp["login"];
        }
        return;
    }

    if (command == "addfile")
    {
        QString     file;

        in >> file;
        if (file != "")
        {
            m_client->addFile(file);
        }
        else
        {
            qDebug() << m_commandsHelp["addfile"];
        }
        return;
    }

    if (command == "check")
    {
        m_client->checkFiles();
        return;
    }

    for (const QString & help : m_commandsHelp)
        qDebug() << help;

    std::cout << "Command to send ?" << std::endl << "> " << std::flush;
}
