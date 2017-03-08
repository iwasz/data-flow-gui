/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ContainerFactoryStrategy.h"
#include "view/INodeView.h"
#include <core/variant/Cast.h>
#include <iostream>

Core::Variant ContainerFactoryStrategy::run (Event const &e) { return container->getBean (beanName); }

/*****************************************************************************/

Core::Variant NodeContainerFactoryStrategy::run (Event const &e)
{
        Core::Variant v = ContainerFactoryStrategy::run (e);

        if (!occast<INodeView *> (v)) {
                throw Core::Exception ("NodeContainerFactoryStrategy::run can't cast to INodeView *.");
        }

        INodeView *nodeView = ocast<INodeView *> (v);

        if (!nodeView->getNode ()) {
                throw Core::Exception ("NodeContainerFactoryStrategy::run nodeView has no flow::Node.");
        }

        assert (program);
        program->addNode (nodeView->getNode ().get ());
        return v;
}
