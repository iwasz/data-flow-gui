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
#include "primitives/Geometry.h"

/**
 * This is only a view.
 */
class __tiliae_reflect__ CircularNode : public AbstractActor, public AbstractNodeView {
public:
        CircularNode ();
        virtual ~CircularNode () {}
        void init ();

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

        virtual Core::StringVector getPropertyViews () const
        {
                Core::StringVector v = AbstractActor::getPropertyViews ();
                v.push_back (propertyView);
                return v;
        }

        // TODO move
        std::string propertyView;

        /*---------------------------------------------------------------------------*/

        virtual void onAllocate (Box const &b);
        virtual Point getPortPosition (int i) const;
};

#endif // CIRCULARNODE_H
