/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CIRCULARNODE_H
#define CIRCULARNODE_H

#include "AbstractActor.h"
#include "IConnectable.h"
#include <vector>

/**
 * This is only a view. Represents a port (place on a node you can connect a connector to).
 */
class __tiliae_reflect__ Port {
public:
        float angle;
        float size;
        Color color;
        Anchor anchor;
};

/**
 * Collection of ports.
 */
typedef __tiliae_reflect__ std::vector<Port> PortVector;

/**
 * This is only a view.
 */
class __tiliae_reflect__ CircularNode : public AbstractActor, public IConnectable {
public:
        CircularNode ();
        virtual ~CircularNode () {}
        void init ();

        PortVector &getPorts () { return ports; }

        /*---------------------------------------------------------------------------*/

        bool isFill () const;
        void setFill (bool value);

        float getStrokeWidth () const;
        void setStrokeWidth (float value);

        float getStrokeDash () const;
        void setStrokeDash (float value);

        Color getStrokeColor () const;
        void setStrokeColor (const Color &value);

        Color getFillColor () const;
        void setFillColor (const Color &value);

        virtual Anchor *getAnchor (size_t i) __tiliae_no_reflect__;
        virtual Anchor const *getAnchor (size_t i) const __tiliae_no_reflect__;

        /*---------------------------------------------------------------------------*/

        virtual void onAllocate (Box const &b);

private:
        PortVector ports;
};

#endif // CIRCULARNODE_H
