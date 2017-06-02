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
#include <core/IFlowObserver.h>

class __tiliae_reflect__ SimpleDisplay : public NodeActor, public AbstractNodeView, public flow::IFlowObserver {
public:
        SimpleDisplay ();
        virtual ~SimpleDisplay () {}
        virtual void visit (IDataFileSave *d) { /*d->onCircle (this);*/}
        virtual void onValueChange (Core::Variant const &v);
};

#endif // CIRCLE_H
