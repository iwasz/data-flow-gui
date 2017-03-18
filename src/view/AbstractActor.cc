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
#include <boost/algorithm/string.hpp>

/*****************************************************************************/

gboolean on_actor_button_press (ClutterActor *stage, ClutterEvent *event, gpointer data);
gboolean on_actor_button_release (ClutterActor *stage, ClutterEvent *event, gpointer data);
gboolean on_actor_motion (ClutterActor *stage, ClutterEvent *event, gpointer data);
gboolean on_actor_enter (ClutterActor *stage, ClutterEvent *event, gpointer data);
gboolean on_actor_leave (ClutterActor *stage, ClutterEvent *event, gpointer data);
gboolean on_actor_scroll (ClutterActor *actor, ClutterEvent *event, gpointer userData);
gboolean on_actor_key_press (ClutterActor *actor, ClutterEvent *event, gpointer user_data);

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

void AbstractActor::init ()
{
        if (isConnectSignals ()) {
                g_signal_connect (self, "button-press-event", G_CALLBACK (on_actor_button_press), this);
                g_signal_connect (self, "button-release-event", G_CALLBACK (on_actor_button_release), this);
                g_signal_connect (self, "motion-event", G_CALLBACK (on_actor_motion), this);
                g_signal_connect (self, "enter-event", G_CALLBACK (on_actor_enter), this);
                g_signal_connect (self, "leave-event", G_CALLBACK (on_actor_leave), this);
                g_signal_connect (self, "scroll-event", G_CALLBACK (on_actor_scroll), this);
                g_signal_connect (self, "key-press-event", G_CALLBACK (on_actor_key_press), this);
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

Core::StringVector AbstractActor::getPropertyViews () const
{
        Core::StringVector ret;
        ret.push_back ("abstractActorPropertiesView");

        Core::StringVector views;
        if (!propertyView.empty ()) {
                boost::split (views, propertyView, boost::is_any_of (", "), boost::token_compress_on);
        }

        for (std::string const &propertyView : views) {
                ret.push_back (propertyView);
        }

        return ret;
}

/*****************************************************************************/

extern "C" void abstractActorOnFinalize (void *ptr)
{
        AbstractActor *cn = static_cast<AbstractActor *> (ptr);
        cn->onFinalize ();
}

/*****************************************************************************/

void processEvent (ClutterActor *stage, ClutterEvent *ev, Event *event)
{
        gfloat x = 0;
        gfloat y = 0;
        clutter_event_get_coords (ev, &x, &y);

        // Find cpp implementation of an actor under cursor.

        // ClutterActor *actor = clutter_stage_get_actor_at_pos (CLUTTER_STAGE (stage), CLUTTER_PICK_ALL, x, y);
        ClutterActor *actor = clutter_event_get_source (ev);
        Core::Object *cActor = nullptr;

        do {
                cActor = static_cast<Core::Object *> (g_object_get_data (G_OBJECT (actor), CPP_IMPLEMENTATION_KEY));

                if (cActor) {
                        break;
                }

        } while ((actor = clutter_actor_get_parent (actor)) != CLUTTER_ACTOR (stage));

        event->positionStageCoords = Point (x, y);
        event->object = cActor;

        /*---------------------------------------------------------------------------*/
        // Find container which the actor is on.

        Core::Object *obj = nullptr;
        IClutterActor *firstContainer = nullptr;
        actor = clutter_event_get_source (ev);

        do {
                obj = static_cast<Core::Object *> (g_object_get_data (G_OBJECT (actor), CPP_IMPLEMENTATION_KEY));

                if (!obj) {
                        continue;
                }

                firstContainer = dynamic_cast<IClutterActor *> (obj);

                if (firstContainer && firstContainer->isContainter ()) {
                        break;
                }

        } while ((actor = clutter_actor_get_parent (actor)) != nullptr && actor != CLUTTER_ACTOR (stage));

        if (firstContainer) {
                ClutterActor *firstContainerActor = firstContainer->getActor ();
                clutter_actor_transform_stage_point (firstContainerActor, event->positionStageCoords.x, event->positionStageCoords.y,
                                                     &event->positionParentCoords.x, &event->positionParentCoords.y);
        }
        else {
                event->positionParentCoords = event->positionStageCoords;
        }
}

/*****************************************************************************/

gboolean on_actor_button_press (ClutterActor *actor, ClutterEvent *ev, gpointer data)
{
        static Event event;
        processEvent (actor, ev, &event);
        event.button = clutter_event_get_button (ev);
        AbstractActor *that = static_cast<AbstractActor *> (data);
        that->stagePrev = event.positionStageCoords;
        that->parentPrev = event.positionParentCoords;
        return that->onButtonPress (event);
}

/*****************************************************************************/

gboolean on_actor_button_release (ClutterActor *stage, ClutterEvent *ev, gpointer data)
{
        static Event event;
        processEvent (stage, ev, &event);
        event.button = clutter_event_get_button (ev);
        AbstractActor *that = static_cast<AbstractActor *> (data);
        return that->onButtonRelease (event);
}

/*****************************************************************************/

gboolean on_actor_motion (ClutterActor *stage, ClutterEvent *ev, gpointer data)
{
        static Event event;
        processEvent (stage, ev, &event);
        AbstractActor *that = static_cast<AbstractActor *> (data);

        if (clutter_event_get_state (ev) & CLUTTER_BUTTON1_MASK) {
                event.stageDelta.x = event.positionStageCoords.x - that->stagePrev.x;
                event.stageDelta.y = event.positionStageCoords.y - that->stagePrev.y;
                event.parentDelta.x = event.positionParentCoords.x - that->parentPrev.x;
                event.parentDelta.y = event.positionParentCoords.y - that->parentPrev.y;
                that->stagePrev = event.positionStageCoords;
                that->parentPrev = event.positionParentCoords;
        }
        else {
                event.stageDelta = Point ();
                event.parentDelta = Point ();
        }

        //        std::cerr << event.stageDelta << ", " << event.parentDelta << std::endl;

        if (clutter_event_get_state (ev) & CLUTTER_BUTTON1_MASK) {
                event.button = 1;
        }
        else if (clutter_event_get_state (ev) & CLUTTER_BUTTON2_MASK) {
                event.button = 2;
        }
        else if (clutter_event_get_state (ev) & CLUTTER_BUTTON3_MASK) {
                event.button = 3;
        }

        return that->onMotion (event);
}

/*****************************************************************************/

gboolean on_actor_enter (ClutterActor *stage, ClutterEvent *ev, gpointer data)
{
        static Event event;
        processEvent (stage, ev, &event);
        AbstractActor *that = static_cast<AbstractActor *> (data);
        return that->onEnter (event);
}

/*****************************************************************************/

gboolean on_actor_leave (ClutterActor *stage, ClutterEvent *ev, gpointer data)
{
        static Event event;
        processEvent (stage, ev, &event);
        AbstractActor *that = static_cast<AbstractActor *> (data);
        return that->onLeave (event);
}

/*****************************************************************************/

gboolean on_actor_scroll (ClutterActor *actor, ClutterEvent *ev, gpointer data)
{
        static Event event;
        processEvent (actor, ev, &event);
        AbstractActor *that = static_cast<AbstractActor *> (data);
        event.scrollDirection = clutter_event_get_scroll_direction (ev);
        clutter_event_get_scroll_delta (ev, &event.scrollX, &event.scrollY);
        return that->onScroll (event);
}

/*****************************************************************************/

gboolean on_actor_key_press (ClutterActor *actor, ClutterEvent *ev, gpointer data)
{
        static Event event;
        event.key = clutter_event_get_key_symbol (ev);
        event.state = clutter_event_get_state (ev);
        event.shiftPressed = (event.state & CLUTTER_SHIFT_MASK ? TRUE : FALSE);
        event.ctrlPressed = (event.state & CLUTTER_CONTROL_MASK ? TRUE : FALSE);
        AbstractActor *that = static_cast<AbstractActor *> (data);
        return that->onKeyPress (event);
}
