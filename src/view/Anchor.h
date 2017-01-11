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

struct IConnector;

/**
 * @brief The Anchor class
 */
class Anchor {
public:
        enum Side { A, B };
        struct Connection {
                Side side;
                IConnector *connector;
        };

        typedef std::vector<Connection> ConnectionVector;
        friend class AbstractConnector;

private:
        void connect (IConnector *c, Side s) { connections.push_back ({ s, c }); }
        void disconnect (IConnector *c, Side s) { /* TODO */}

        ConnectionVector connections;
};

#endif // ANCHOR_H
