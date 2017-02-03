/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "RectangularSelector.h"
#include "clutter/iw_rectangle.h"
#include <core/Exception.h>
#include <iostream>

/*****************************************************************************/

RectangularSelector::RectangularSelector () { clutter_actor_add_action (self, clutter_drag_action_new ());}

/*****************************************************************************/

bool RectangularSelector::onButtonPress (Event const &event)
{
        if (!getEventHandler ()) {
                return false;
        }

        if (event.object != this) {
                return true;
        }

        if (event.button == 2) {
                getEventHandler ()->pushMessage ("stage.press.scroll", &event);
        }
        else {
                getEventHandler ()->pushMessage ("stage.press", &event);
        }

        return true;
}

/*****************************************************************************/

bool RectangularSelector::onButtonRelease (Event const &event)
{
        if (!getEventHandler ()) {
                return false;
        }

        if (event.object != this) {
                return true;
        }

        if (event.button == 2) {
                getEventHandler ()->pushMessage ("stage.release.scroll", &event);
        }
        else {
                getEventHandler ()->pushMessage ("stage.release", &event);
        }

        return true;
}

/*****************************************************************************/

bool RectangularSelector::onMotion (Event const &event)
{
        if (!getEventHandler ()) {
                return false;
        }

        if (event.object != this) {
//                Point p2;
//                clutter_actor_get_position (getActor(), &p2.x, &p2.y);
//                p2.x += event.stageDelta.x;
//                p2.y += event.stageDelta.y;
//                std::cerr << "++ " << event.stageDelta << std::endl;
//                clutter_actor_set_position (getActor (), p2.x, p2.y);
                return true;
        }

        getEventHandler ()->pushMessage ("stage.motion", &event);
        return true;
}
