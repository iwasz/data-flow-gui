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

/*****************************************************************************/

void RoutablePin::init (primitives::Point const &p, IRoutable *owner)
{
        assert (owner);
        this->owner = owner;
        pin = new Avoid::ShapeConnectionPin (owner->getShapeRef (), getClassNumber (), p.x, p.y, true, 0, Avoid::ConnDirNone);
        pin->setExclusive (exclusive);
}

/*****************************************************************************/

// void RoutablePin::setPosition (primitives::Point const &p) { pin->updatePosition (Avoid::Point (p.x, p.y)); }
