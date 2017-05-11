/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "RoutablePin.h"
#include "IRoutable.h"

Avoid::ShapeRef *RoutablePin::getShapeRef () __tiliae_no_reflect__
{
        if (!owner) {
                return nullptr;
        }

        return owner->getShapeRef ();
}
