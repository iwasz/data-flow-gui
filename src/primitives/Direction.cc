/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Direction.h"

Core::Variant directionFromString (std::string const &s)
{
        Direction d;

        if (s == "E") {
                d = EAST;
        }
        else if (s == "W") {
                d = WEST;
        }
        else if (s == "S") {
                d = SOUTH;
        }
        else if (s == "N") {
                d = NORTH;
        }
        else {
                throw Core::Exception (std::string ("directionFromString : unknown direction [") + s + "]!");
        }

        return Core::Variant (d);
}

/*****************************************************************************/

Direction getOppositeDirection (Direction d)
{
        switch (d) {
        case NORTH:
                return SOUTH;

        case SOUTH:
                return NORTH;

        case WEST:
                return EAST;

        case EAST:
                return WEST;

        case NONE:
        default:
                return NONE;
        }
}


