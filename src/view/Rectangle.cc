/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Rectangle.h"
#include "clutter/iw_rectangle.h"
#include <core/Exception.h>

/*****************************************************************************/

Rectangle::Rectangle ()
{
        self = iw_rectangle_new ();
        clutter_actor_set_reactive (self, TRUE);

        clutter_actor_add_action (self, clutter_drag_action_new ());

        iw_actor_set_user_data (IW_ACTOR (self), this);
        setCppImplementation ();
}
