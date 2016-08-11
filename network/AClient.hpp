#ifndef ACLIENT
# define ACLIENT

# include <QVariant>

# include "statemachine/statemachine.h"

class AClient : public QObject
{
    Q_OBJECT

protected:
    StateMachine*   m_stateMachine;

public:
    AClient(StateMachine * stateMachine)
        : QObject(),
          m_stateMachine(stateMachine)
    {
        QVariant    variant;

        variant.setValue(this);
        m_stateMachine->setData("client", variant);
    }

    virtual ~AClient()
    {
        delete m_stateMachine;
    }

    virtual void    receiveMessage(const QVariant & message) = 0;
    virtual void    sendMessage(const QVariant & message) = 0;

signals:
    void            send(qint32 socketFd, const QVariant & message);

private:
    Q_DISABLE_COPY(AClient)
};

Q_DECLARE_METATYPE(AClient*)

#endif // ACLIENT

