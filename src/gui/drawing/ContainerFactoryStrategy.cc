/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "ContainerFactoryStrategy.h"

Core::Variant ContainerFactoryStrategy::run (/*Point const &a, Core::Object *oa, Point const &b, Core::Object *ob*/)
{
        return container->getBean (beanName);
}



