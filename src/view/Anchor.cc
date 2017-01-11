/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Anchor.h"

// TODO when attepmpting to connect the same connector to the same anchor, throw.
void Anchor::connect (IConnector *c, IConnector::Side s) { connections.push_back ({ s, c }); /* TODO notify x, y*/ }
void Anchor::disconnect (IConnector *c, IConnector::Side s) { /* TODO */}

void Anchor::notifyMoveAnchor (float x, float y)
{
        for (Connection &c : connections) {
                c.connector->onMoveAnchor (x, y, c.side);
        }
}

// void Anchor::notifyConnectAnchor (float x, float y) {}

// void Anchor::notifyDisconnectAnchor (float x, float y) {}
