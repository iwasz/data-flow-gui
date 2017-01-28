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

        virtual void onAllocate (Box const &b);
        virtual void onClick ();
        virtual Point getPortPosition (int i) const;
};

#endif // BUTTON_H
