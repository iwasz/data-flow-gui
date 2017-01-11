/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_ANCHOR_H
#define DATA_FLOW_ANCHOR_H

#include <vector>
#include <memory>
#include "IConnector.h"

/**
 * @brief The Anchor class
 */
class Anchor {
public:

        struct Connection {
                IConnector::Side side;
                IConnector *connector;
        };

        typedef std::vector<Connection> ConnectionVector;
        friend class AbstractConnector;

//        void notifyConnectAnchor (float x, float y);
        void notifyMoveAnchor (float x, float y);
//        void notifyDisconnectAnchor (float x, float y);

private:

        void connect (IConnector *c, IConnector::Side s);
        void disconnect (IConnector *c, IConnector::Side s);

        ConnectionVector connections;
};

typedef std::vector <std::unique_ptr<Anchor>> AnchorVector;

#endif // ANCHOR_H
