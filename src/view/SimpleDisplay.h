/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_SIMPLEDISPLAY_H
#define DATA_FLOW_SIMPLEDISPLAY_H

#include "AbstractNodeView.h"
#include "NodeActor.h"
#include "primitives/Geometry.h"

class __tiliae_reflect__ SimpleDisplay : public NodeActor, public AbstractNodeView {
public:
        SimpleDisplay ();
        virtual ~SimpleDisplay () {}
        virtual void visit (IDataFileSave *d) { /*d->onCircle (this);*/}
};

#endif // CIRCLE_H
