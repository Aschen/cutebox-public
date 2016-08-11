#ifndef SESSIONUTILS_HH
# define SESSIONUTILS_HH

# include <QVariant>

class AClient;
class StateMachine;

class SessionUtils
{
public:
    static void     sendMessage(const StateMachine * statemachine, const QVariant & message);
    static AClient* getClient(const StateMachine * statemachine);
public:
    SessionUtils();
};

#endif // SESSIONUTILS_HH
