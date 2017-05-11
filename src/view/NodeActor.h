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
        virtual primitives::Point getPortPosition (Port const *port) const __tiliae_no_reflect__ = 0;

private:
        PortVector ports;
};

#endif // NODEACTOR_H
