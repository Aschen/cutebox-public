#ifndef RECEIVEFILE_HH
# define RECEIVEFILE_HH

# include "statemachine/state.h"
# include "statemachine/QVariantHashTransition.hh"
# include "statemachine/transitionvariantevent.h"

/* ReceiveFileState=============================================================== */

class ReceiveFileState : public State
{
public:
    ReceiveFileState(const State * previousState);

    // State interface
protected:
    void            entered(TransitionEvent * event) const Q_DECL_OVERRIDE;
    void            exited(TransitionEvent *) const Q_DECL_OVERRIDE;
};

/* ReceiveFileTransition ============================================================= */

class ReceiveFileTransition : public QVariantHashTransition
{
public:
    ReceiveFileTransition();

    // Transition interface
protected:
    bool            eventTest(TransitionEvent * event) const Q_DECL_OVERRIDE;
};

#endif // RECEIVEFILE_HH
