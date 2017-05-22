/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ConnectorActor.h"
#include "Port.h"

void ConnectorActor::connect (Port *port, Side s)
{
        getRoutable ()->connect (port->getRoutablePin (), s);

        if (s == Side::A) {
                a = port;
        }
        else if (s == Side::B) {
                b = port;
        }
}

/*****************************************************************************/

void ConnectorActor::disconnect (/*Side s*/)
{
        // TODO
        a = b = nullptr;
}
