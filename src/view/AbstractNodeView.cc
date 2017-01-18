/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractNodeView.h"

/*****************************************************************************/

Anchor *AbstractNodeView::getAnchor (size_t i)
{
        if (i >= ports.size ()) {
                throw Core::Exception ("AbstractNodeView::getAnchor no sucho node");
        }

        return &ports[i]->anchor;
}

/*****************************************************************************/

Anchor const *AbstractNodeView::getAnchor (size_t i) const
{
        if (i >= ports.size ()) {
                throw Core::Exception ("AbstractNodeView::getAnchor no sucho node");
        }

        return &ports[i]->anchor;
}

/*****************************************************************************/

void AbstractNodeView::glueInit ()
{
        int inputNumber = 0;
        int outputNumber = 0;
        for (std::shared_ptr<Port> p : getPorts ()) {
                p->nodeView = this;

                if (p->isInput ()) {
                        p->number = inputNumber++;
                }
                else {
                        p->number = outputNumber++;
                }
        }
}
