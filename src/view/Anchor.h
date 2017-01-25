/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_ANCHOR_H
#define DATA_FLOW_ANCHOR_H

#include "IConnector.h"
#include "primitives/Geometry.h"
#include <memory>
#include <vector>

struct IAnchorPositionProvider {
        virtual ~IAnchorPositionProvider () {}
        virtual Point getPosition () const = 0;
};

/**
 * The logic behind anchors.
 */
class Anchor {
public:
        ~Anchor ();

        struct Connection {
                IConnector::Side side;
                IConnector *connector;
        };

        typedef std::vector<Connection> ConnectionVector;
        friend class AbstractConnector;

        void notifyMoveAnchor (Point const &p);

        Point getPosition () const { return apProvider->getPosition (); }

        void setApProvider (std::shared_ptr<IAnchorPositionProvider> value) { apProvider = value; }


private:

        void connect (IConnector *c, IConnector::Side s);
//        void disconnect (IConnector *c, IConnector::Side s);
        void disconnect (IConnector *c);
//        void disconnect ();


        ConnectionVector connections;
        std::shared_ptr<IAnchorPositionProvider> apProvider;
};

typedef std::vector<std::unique_ptr<Anchor>> AnchorVector;

#endif // ANCHOR_H
