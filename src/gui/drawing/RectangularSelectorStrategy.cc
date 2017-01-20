/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "RectangularSelectorStrategy.h"
#include "view/Rectangle.h"

void RectangularSelectorStrategy::onObjectCreated (IClutterActor *)
{
        rectangularSelector->setPosition (startPoint);
        rectangularSelector->setSize (endPoint - startPoint);
        rectangularSelector->setVisible (true);
}
