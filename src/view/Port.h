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
#include <ReflectionParserAnnotation.h>
#include <vector>

struct INodeView;

/**
 * The view for anchors. This is only a view. Represents a port (place on a node you can
 * connect a connector to).
 */
class __tiliae_reflect__ Port : public Core::Object {
public:
        virtual ~Port () {}
        virtual bool isInput () const = 0;

        Direction getFacing () const { return anchor.getFacing (); }
        void setFacing (Direction value) { anchor.setFacing (value); }

        float angle = 0.0;
        float size = 0.0;
        Color color;
        Anchor anchor;
        INodeView *nodeView = nullptr;
        int number = 0;
};

class __tiliae_reflect__ InputPort : public Port {
public:
        virtual ~InputPort () {}
        virtual bool isInput () const { return true; }
};

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
