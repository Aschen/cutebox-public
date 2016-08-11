/******************************************************************************

            COPYRIGHT (c) 2008 - 2010 by RG Systèmes Corporation.
        This software has been provided pursuant to a License Agreement
        containing restrictions on its use.  This software contains
        valuable trade secrets and proprietary information of
        RG Systèmes Corporation and is protected by law. It may
        not be copied or distributed in any form or medium, disclosed
        to third parties, reverse engineered or used in any manner not
        provided for in said License Agreement except with the prior
        written authorization from RG Systèmes Corporation.

******************************************************************************/

#ifndef ABSTRACTWORKER_H
# define ABSTRACTWORKER_H

# include <QDebug>

template < class ParentObject >
class AbstractWorker : public ParentObject
{
public slots:
    virtual void start() = 0;
    virtual void stop()
    {
        qWarning("You're using the default implementation of the stop() function, this is broken");
    }
};

#endif // ABSTRACTWORKER_H
