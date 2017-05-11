/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONNECTORACTOR_H
#define CONNECTORACTOR_H

#include "AbstractActor.h"
#include "primitives/Direction.h"

class Port;

class __tiliae_reflect__ ConnectorActor : public AbstractActor {
public:
        virtual ~ConnectorActor () {}

        virtual void connect (Port *an, Side s);
        virtual void disconnect ();

        Port *getPort (Side s) __tiliae_no_reflect__ { return (Side::A) ? (a) : (b); }

private:
        Port *a = nullptr;
        Port *b = nullptr;
};

#endif // CONNECTORACTOR_H
