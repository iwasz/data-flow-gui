/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "ContainerFactoryStrategy.h"

Core::Variant ContainerFactoryStrategy::run (float x1, float y1, float x2, float y2)
{
        return container->getBean (beanName);
}



