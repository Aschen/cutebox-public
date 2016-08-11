#ifndef QVARIANTHASHTRANSITION_HH
# define QVARIANTHASHTRANSITION_HH

# include <QString>
# include "transition.h"

class QVariantHashTransition : public Transition
{
private:
    QString         m_action;

public:
    QVariantHashTransition(const QString & action);

    // Transition interface
protected:
    virtual bool    eventTest(TransitionEvent *event) const Q_DECL_OVERRIDE;
};

#endif // QVARIANTHASHTRANSITION_HH
