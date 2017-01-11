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
#include <vector>

/**
 * This is only a view.
 */
class __tiliae_reflect__ Port {
public:
        float angle;
        float size;
        Color color;
};

typedef __tiliae_reflect__ std::vector<Port> PortVector;

/*****************************************************************************/









/*****************************************************************************/

/**
 * This is only a view.
 */
class __tiliae_reflect__ CircularNode : public AbstractActor {
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

private:
        PortVector ports;
};

#endif // CIRCULARNODE_H
