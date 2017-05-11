/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VISIBLE_PORT_H
#define VISIBLE_PORT_H

#include "Anchor.h"
#include "primitives/Color.h"
#include "primitives/Direction.h"
#include "primitives/Geometry.h"
#include "routable/RoutablePin.h"
#include <ReflectionParserAnnotation.h>
#include <libavoid.h>
#include <vector>

class NodeActor;
class RoutablePin;

/**
 * The view for anchors. This is only a view. Represents a port (place on a node you can
 * connect a connector to).
 */
class __tiliae_reflect__ Port : public Core::Object {
public:
        virtual ~Port () {}
        virtual bool isInput () const = 0;

        NodeActor *getNodeActor () { return nodeActor; }
        void setNodeActor (NodeActor *value) { nodeActor = value; }

        int getProgramNumber () const { return programNumber; }
        void setProgramNumber (int i) { programNumber = i; }

        int getViewNumber () const { return viewNumber; }
        void setViewNumber (int i) { viewNumber = i; }

        RoutablePin *getRoutablePin () { return routablePin; }
        void setRoutablePin (RoutablePin *pin) { routablePin = pin; }

        void init ();

        primitives::Point getPosition () const;

        float angle = 0.0;
        float size = 0.0;
        primitives::Color color;

private:
        NodeActor *nodeActor = nullptr;
        /// Number for indexing in data-flow program nodes
        int programNumber = 0;
        /// Number for indexing in views (like CircularNode).
        int viewNumber = 0;

        RoutablePin *routablePin = nullptr;
};

/*****************************************************************************/

class __tiliae_reflect__ InputPort : public Port {
public:
        virtual ~InputPort () {}
        virtual bool isInput () const { return true; }
};

/*****************************************************************************/

class __tiliae_reflect__ OutputPort : public Port {
public:
        virtual ~OutputPort () {}
        virtual bool isInput () const { return false; }
};

/**
 * Collection of ports.
 */
typedef __tiliae_reflect__ std::vector<std::shared_ptr<Port>> PortVector;

#endif // PORT_H
