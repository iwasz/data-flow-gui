/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractActor.h"

/*****************************************************************************/

void AbstractActor::setParent (IClutterActor *parent) { clutter_actor_add_child (parent->getActor (), self); }

/*****************************************************************************/

bool AbstractActor::getVisible () const { return clutter_actor_is_visible (self); }

/*****************************************************************************/

void AbstractActor::setVisible (bool value)
{
        if (value) {
                clutter_actor_show (self);
        }
        else {
                clutter_actor_hide (self);
        }
}

/*****************************************************************************/

void AbstractActor::setPosition (Point const &p) { clutter_actor_set_position (self, p.x, p.y); }

/*****************************************************************************/

Point AbstractActor::getPosition () const
{
        Point p;
        clutter_actor_get_position (self, &p.x, &p.y);
        return p;
}

/*****************************************************************************/

void AbstractActor::setSize (Dimension const &d) { clutter_actor_set_size (self, d.width, d.height); }

/*****************************************************************************/

Dimension AbstractActor::getDimension () const
{
        Dimension d;
        clutter_actor_get_size (self, &d.width, &d.height);
        return d;
}

/*****************************************************************************/

void AbstractActor::setCppImplementation ()
{
        g_object_set_data (G_OBJECT (self), CPP_IMPLEMENTATION_KEY, this);
}
