/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DashedCircleStrategy.h"

static float startX;
static float startY;

void DashedCircleStrategy::onButtonPress (float x, float y)
{
        circle->setX (x);
        circle->setY (y);
        circle->setW (0);
        circle->setH (0);
        startX = x;
        startY = y;
        circle->setVisible (true);
}

/*****************************************************************************/

void DashedCircleStrategy::onMotion (float x, float y)
{
        circle->setW (x - startX);
        circle->setH (y - startY);
}

/*****************************************************************************/

void DashedCircleStrategy::onButtonRelease (float x, float y) { circle->setVisible (false); }
