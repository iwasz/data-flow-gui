/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractNodeView.h"

void AbstractNodeView::setNode (std::shared_ptr<flow::INode> n)
{
        node = n;
        flow::IFlowObserver *fo = dynamic_cast<flow::IFlowObserver *> (this);

        if (fo) {
                n->setObserver (fo);
        }
}
