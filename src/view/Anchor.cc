/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Anchor.h"
#include <algorithm>

Anchor::~Anchor ()
{
        for (Connection const &con : connections) {
                con.connector->disconnect ();
        }

        connections.clear ();
}

// TODO when attepmpting to connect the same connector to the same anchor, throw.
void Anchor::connect (IConnector *c, IConnector::Side s) { connections.push_back ({ s, c }); }

/*****************************************************************************/

// void Anchor::disconnect (IConnector *c, IConnector::Side s)
//{
//        ConnectionVector::iterator i
//                = std::remove_if (connections.begin (), connections.end (), [c, s](Connection const &con) { return con.connector == c && con.side == s; });

//        for (ConnectionVector::iterator j = i; j < connections.end (); ++j) {
//                j->connector->onDisconnectAnchor (Point (), j->side);
//        }

//        connections.erase (i, connections.end ());
//}

/*****************************************************************************/

void Anchor::disconnect (IConnector *c)
{
        ConnectionVector::iterator i = std::remove_if (connections.begin (), connections.end (), [c](Connection const &con) { return con.connector == c; });

        //        for (ConnectionVector::iterator j = i; j < connections.end (); ++j) {
        //                j->connector->onDisconnectAnchor (Point (), j->side);
        //        }

        connections.erase (i, connections.end ());
}

/*****************************************************************************/

// void Anchor::disconnect ()
//{

//        for (Connection const &con : connections) {
//                con.connector->onDisconnectAnchor (Point (), con.side);
//        }

//        connections.clear ();
//}

/*****************************************************************************/

void Anchor::notifyMoveAnchor (const Point &p)
{
        for (Connection &c : connections) {
                c.connector->onMoveAnchor (p, c.side);
        }
}
