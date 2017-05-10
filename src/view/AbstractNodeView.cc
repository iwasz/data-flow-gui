/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractNodeView.h"

/*****************************************************************************/

//Anchor *AbstractNodeView::getAnchor (size_t i)
//{
//        if (i >= getPorts ().size ()) {
//                throw Core::Exception ("AbstractNodeView::getAnchor no sucho node");
//        }

//        return &getPorts ()[i]->anchor;
//}

///*****************************************************************************/

//Anchor const *AbstractNodeView::getAnchor (size_t i) const
//{
//        if (i >= ports.size ()) {
//                throw Core::Exception ("AbstractNodeView::getAnchor no sucho node");
//        }

//        return &ports[i]->anchor;
//}

/*****************************************************************************/

void AbstractNodeView::glueInit ()
{
        int inputProgramNumber = 0;
        int outputProgramNumber = 0;
        int viewNumber = 0;
        for (std::shared_ptr<Port> p : getPorts ()) {
                p->setNodeView (this);

                if (p->isInput ()) {
                        p->setProgramNumber (inputProgramNumber++);
                        p->setViewNumber (viewNumber);
                }
                else {
                        p->setProgramNumber (outputProgramNumber++);
                        p->setViewNumber (viewNumber);
                }

                p->createPin ();
                ++viewNumber;
        }
}
