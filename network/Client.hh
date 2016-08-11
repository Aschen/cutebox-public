#ifndef CLIENT_HH
# define CLIENT_HH

# include "AClient.hpp"

class Client : public AClient
{
private:
    qint32          m_socketFd;

public:
    Client(qint32 socketFd);

    void            receiveMessage(const QVariant & message);
    void            sendMessage(const QVariant & message);

private:
    Q_DISABLE_COPY(Client)
};

#endif // CLIENT_HH
