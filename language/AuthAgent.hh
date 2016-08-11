#ifndef AUTHAGENT_HH
# define AUTHAGENT_HH

# include "statemachine/state.h"
# include "statemachine/initialstate.h"
# include "statemachine/QVariantHashTransition.hh"
# include "statemachine/transitionvariantevent.h"

/* AuthAgentState ================================================================== */

class AuthAgentState : public InitialState
{
public:
    AuthAgentState();

    // State interface
protected:
    void        exited(TransitionEvent * event) const Q_DECL_OVERRIDE;
};

/* AuthenticatedAgentState ========================================================= */

class AuthenticatedAgentState : public State
{
public:
    AuthenticatedAgentState(const State * previousState);

    // State interface
protected:
    void        entered(TransitionEvent * event) const Q_DECL_OVERRIDE;
};

/* AuthAgentTransition ============================================================= */

class AuthAgentTransition : public QVariantHashTransition
{
public:
    AuthAgentTransition();

    // Transition interface
protected:
    bool        eventTest(TransitionEvent * event) const;
};

#endif // AUTHAGENT_HH
