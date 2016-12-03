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
        std::string color;
};

typedef __tiliae_reflect__ std::vector<Port> PortVector;

/**
 * This is only a view.
 */
class __tiliae_reflect__ CircularNode : public AbstractActor {
public:
        CircularNode ();
        virtual ~CircularNode () {}
        void init ();

        PortVector getPorts () const { return ports; }
        void setPorts (const PortVector &value) { ports = value; }

        /*---------------------------------------------------------------------------*/

        bool isFill () const;
        void setFill (bool value);

        float getStrokeWidth () const;
        void setStrokeWidth (float value);

        float getStrokeDash () const;
        void setStrokeDash (float value);

        std::string getStrokeColor () const;
        void setStrokeColor (const std::string &value);

        std::string getFillColor () const;
        void setFillColor (const std::string &value);

private:
        PortVector ports;
};

#endif // CIRCULARNODE_H
