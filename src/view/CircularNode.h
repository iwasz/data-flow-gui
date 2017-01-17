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
#include "AbstractNodeView.h"
#include "IConnectable.h"
#include "Port.h"
#include <vector>
/**
 * This is only a view.
 */
class __tiliae_reflect__ CircularNode : public AbstractActor, public IConnectable, public AbstractNodeView {
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
