/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef NODEACTOR_H
#define NODEACTOR_H

#include "AbstractActor.h"
#include "Port.h"

/**
 * Actor with ports.
 */
class __tiliae_reflect__ NodeActor : public AbstractActor {
public:
        virtual void init ();

        virtual PortVector &getPorts () { return ports; }

private:
        PortVector ports;
};

#endif // NODEACTOR_H
