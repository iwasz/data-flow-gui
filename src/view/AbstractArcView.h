/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/
#ifndef ABSTRACTARCVIEW_H
#define ABSTRACTARCVIEW_H

#include "IArcView.h"
#include <core/IFlowObserver.h>

class __tiliae_reflect__ AbstractArcView : public IArcView {
public:
        virtual ~AbstractArcView () {}
        std::shared_ptr<flow::Arc> getArc () { return arc; }
        void setArc (std::shared_ptr<flow::Arc> a)
        {
                arc = a;
                arc->setObserver (dynamic_cast<flow::IFlowObserver *> (this));
        }

private:
        std::shared_ptr<flow::Arc> arc;
};

#endif // ABSTRACTARCVIEW_H
