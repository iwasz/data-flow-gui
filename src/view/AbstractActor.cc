/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractActor.h"
#include "ScaleLayer.h"
#include "clutter/iw_actor.h"

/*****************************************************************************/

AbstractActor::~AbstractActor ()
{
        if (!clutterDestroyed) {
                ClutterActor *oldParent;
                if ((oldParent = clutter_actor_get_parent (self)) != nullptr) {
                        clutter_actor_remove_child (oldParent, self);
                }
                else {
                        g_critical ("AbstractActor::~AbstractActor : clutter_actor_get_parent (self) == nullptr");
                }
        }
}

/*****************************************************************************/

void AbstractActor::setParent (IClutterActor *parent)
{

        ClutterActor *oldParent;
        if ((oldParent = clutter_actor_get_parent (self)) != nullptr) {
                g_object_ref (self);
                clutter_actor_remove_child (oldParent, self);
        }

        clutter_actor_add_child (parent->getActor (), self);

        if (oldParent) {
                g_object_unref (self);
        }
}

/*****************************************************************************/

bool AbstractActor::isVisible () const { return clutter_actor_is_visible (self); }

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

void AbstractActor::setCppImplementation () { g_object_set_data (G_OBJECT (self), CPP_IMPLEMENTATION_KEY, this); }

/*****************************************************************************/

Box AbstractActor::getBoundingBox () const
{

        //        ClutterActorBox actorBox;
        //        if (!clutter_actor_get_paint_box (self, &actorBox)) {
        //                throw Core::Exception ("AbstractActor::getBoundingBox : !clutter_actor_get_paint_box");
        //        }
        //        return Box (Point (actorBox.x1, actorBox.y1), Point (actorBox.x2, actorBox.y2));

        // Assuming, that IClutterActors won't be scalled or rotated.
        float x, y, w, h;
        clutter_actor_get_position (self, &x, &y);
        clutter_actor_get_size (self, &w, &h);
        return Box (Point (x, y), Dimension (w, h));
}

/*****************************************************************************/

bool AbstractActor::isReactive () const { return clutter_actor_get_reactive (self); }

/*****************************************************************************/

void AbstractActor::setReactive (bool value) { clutter_actor_set_reactive (self, value); }

/*****************************************************************************/

Point AbstractActor::convertToScaleLayer (Point const &p) const
{
        if (clutter_actor_get_parent (self) == ScaleLayer::singleton ()->getActor ()) {
                return p;
        }

        ClutterVertex in, out = { 0, 0 };
        in.x = p.x;
        in.y = p.y;
        clutter_actor_apply_relative_transform_to_point (CLUTTER_ACTOR (self), ScaleLayer::singleton ()->getActor (), &in, &out);
        Point b, pos = getPosition ();
        b.x = out.x - pos.x;
        b.y = out.y - pos.y;

        return b;
}

/*****************************************************************************/

bool AbstractActor::isFill () const { return iw_actor_is_fill (IW_ACTOR (self)); }

/*****************************************************************************/

void AbstractActor::setFill (bool value) { iw_actor_set_fill (IW_ACTOR (self), value); }

/*****************************************************************************/

float AbstractActor::getStrokeWidth () const { return iw_actor_get_stroke_width (IW_ACTOR (self)); }

/*****************************************************************************/

void AbstractActor::setStrokeWidth (float value) { iw_actor_set_stroke_width (IW_ACTOR (self), value); }

/*****************************************************************************/

float AbstractActor::getStrokeDash () const { return iw_actor_get_stroke_dash (IW_ACTOR (self)); }

/*****************************************************************************/

void AbstractActor::setStrokeDash (float value) { iw_actor_set_stroke_dash (IW_ACTOR (self), value); }

/*****************************************************************************/

Color AbstractActor::getStrokeColor () const { return Color (iw_actor_get_stroke_color (IW_ACTOR (self))); }

/*****************************************************************************/

Color AbstractActor::getFillColor () const { return Color (iw_actor_get_fill_color (IW_ACTOR (self))); }

/*****************************************************************************/

void AbstractActor::setStrokeColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_actor_set_stroke_color (IW_ACTOR (self), &color);
}

/*****************************************************************************/

void AbstractActor::setFillColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_actor_set_fill_color (IW_ACTOR (self), &color);
}

/*****************************************************************************/

extern "C" void abstractActorOnFinalize (void *ptr)
{
        AbstractActor *cn = static_cast<AbstractActor *> (ptr);
        cn->onFinalize ();
}
