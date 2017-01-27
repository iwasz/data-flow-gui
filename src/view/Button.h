/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATAFLOW_GUI_STUFF_BUTTON_H
#define DATAFLOW_GUI_STUFF_BUTTON_H

#include "AbstractActor.h"
#include "AbstractNodeView.h"
#include "primitives/Geometry.h"

class __tiliae_reflect__ Button : public AbstractActor, public AbstractNodeView {
public:
        Button ();
        virtual ~Button () {}
        void init ();

        /*---------------------------------------------------------------------------*/

        // TODO all these methods to AbstractActor.
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

        /*---------------------------------------------------------------------------*/

        virtual void onAllocate (Box const &b);
        virtual void onClick ();
        virtual Point getPortPosition (int i) const;
};

#endif // BUTTON_H
