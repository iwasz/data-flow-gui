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
        pin = new Avoid::ShapeConnectionPin (owner->getShapeRef (), getClassNumber (), p.x, p.y, isRelative (), getInsideOffset (), getDirection ());
        pin->setExclusive (exclusive);
}

/*****************************************************************************/

Core::Variant avoidDirectionFromString (std::string const &s)
{
        Avoid::ConnDirFlag d;

        if (s == "RIGHT") {
                d = Avoid::ConnDirRight;
        }
        else if (s == "LEFT") {
                d = Avoid::ConnDirLeft;
        }
        else if (s == "DOWN") {
                d = Avoid::ConnDirDown;
        }
        else if (s == "UP") {
                d = Avoid::ConnDirUp;
        }
        else if (s == "NONE") {
                d = Avoid::ConnDirNone;
        }
        else if (s == "ALL") {
                d = Avoid::ConnDirAll;
        }
        else {
                throw Core::Exception (std::string ("avoidDirectionFromString : unknown direction [") + s + "]!");
        }

        return Core::Variant (d);
}
