/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Stage.h"
#include "ScaleLayer.h"
#include <clutter/clutter.h>
#include <core/Exception.h>

/*****************************************************************************/

void on_stage_resize (ClutterActor *actor, ClutterActorBox *box, ClutterAllocationFlags flags, gpointer user_data);
gboolean button_callback_clutter (GtkWidget *widget, GdkEvent *event, gpointer callback_data);

/*****************************************************************************/

Stage::Stage () : scaleLayer (nullptr)
{
        clutterWidget = gtk_clutter_embed_new ();
        self = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutterWidget));
        gtk_widget_set_can_focus (clutterWidget, TRUE);
        gtk_widget_set_focus_on_click (clutterWidget, TRUE);
        clutter_stage_set_minimum_size (CLUTTER_STAGE (self), 100, 100);

        g_signal_connect (self, "allocation-changed", G_CALLBACK (on_stage_resize), this);
        g_signal_connect (getClutterWidget (), "button_press_event", G_CALLBACK (button_callback_clutter), nullptr);
        setCppImplementation ();
}

/*****************************************************************************/

primitives::Color Stage::getFillColor () const
{
        ClutterColor color;
        clutter_actor_get_background_color (self, &color);
        return primitives::Color (&color);
}

/*****************************************************************************/

void Stage::setFillColor (const primitives::Color &value)
{
        ClutterColor color = primitives::Color::toClutterColor (value);
        clutter_actor_set_background_color (self, &color);
}

/*****************************************************************************/

void on_stage_resize (ClutterActor *actor, ClutterActorBox *box, ClutterAllocationFlags flags, gpointer user_data)
{
        Stage *stage = static_cast<Stage *> (user_data);
        ClutterActor *scale = nullptr;

        if (stage->getScaleLayer ()) {
                scale = stage->getScaleLayer ()->getActor ();
        }
        else {
                return;
        }

        primitives::Box bb (primitives::Point (box->x1, box->y1), primitives::Point (box->x2, box->y2));
        primitives::Dimension dim = bb.getDimension ();
        // clutter_actor_set_size (scale, dim.width, dim.height);
        clutter_actor_set_position (scale, -(SCALE_SURFACE_SIZE - dim.width) / 2.0, -(SCALE_SURFACE_SIZE - dim.height) / 2.0);
}

/*****************************************************************************/

gboolean button_callback_clutter (GtkWidget *widget, GdkEvent *event, gpointer callback_data)
{
        gtk_widget_grab_focus (widget);
        gboolean handled = FALSE;
        return handled;
}

/*****************************************************************************/

void Stage::setScaleLayer (ScaleLayer *layer)
{
        scaleLayer = layer;
        layer->setParent (this);
        layer->instance = layer; // trick
}

/*****************************************************************************/

bool Stage::onButtonPress (Event const &event)
{
        if (!getEventHandler ()) {
                return false;
        }

        if (event.button == 2) {
                getEventHandler ()->pushMessage ("stage.press.scroll", &event);
        }
        else {
                // if (event.object == this || event.object == getScaleLayer ()) {
                IClutterActor *actor;
                if ((actor = dynamic_cast<IClutterActor *> (event.object)) && actor->isSelectable ()) {
                        getEventHandler ()->pushMessage ("object.press", &event);
                }
                else {
                        getEventHandler ()->pushMessage ("stage.press", &event);
                }
        }

        return true;
}

/*****************************************************************************/

bool Stage::onButtonRelease (Event const &event)
{
        if (!getEventHandler ()) {
                return false;
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

bool Stage::onMotion (Event const &event)
{
        if (!getEventHandler ()) {
                return false;
        }

        getEventHandler ()->pushMessage ("stage.motion", &event);
        return true;
}

/*****************************************************************************/

bool Stage::onScroll (Event const &e)
{
        ScaleLayer *scale = getScaleLayer ();

        if (!scale) {
                return false;
        }

        switch (e.scrollDirection) {
        case CLUTTER_SCROLL_UP:
                scale->zoomIn (e.positionParentCoords);
                break;

        case CLUTTER_SCROLL_DOWN:
                scale->zoomOut (e.positionParentCoords);
                break;

        case CLUTTER_SCROLL_SMOOTH: {
                if (e.scrollY > 0) {
                        scale->zoomOut (e.positionParentCoords);
                }
                else if (e.scrollY < 0) {
                        scale->zoomIn (e.positionParentCoords);
                }
        } break;

        default:
                break;
        }

        return CLUTTER_EVENT_STOP;
}

/*****************************************************************************/

bool Stage::onKeyPress (Event const &event)
{
        if (event.key == CLUTTER_KEY_Delete) {
                getEventHandler ()->pushMessage ("stage.delete", &event);
                return true;
        }

        return false;
}
