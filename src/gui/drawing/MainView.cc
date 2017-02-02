/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MainView.h"
#include "MainController.h"
#include "view/IClutterActor.h"
#include "view/ScaleLayer.h"
#include "view/clutter/iw_actor.h"
#include "view/clutter/iw_button.h"
#include "view/clutter/iw_circle.h"
#include "view/clutter/iw_circular_node.h"
#include "view/clutter/iw_line.h"
#include "view/clutter/iw_rectangle.h"
#include <clutter-gtk/clutter-gtk.h>
#include <clutter/clutter.h>
#include <gtk/gtk.h>

/*****************************************************************************/

void on_stage_button_press (ClutterStage *stage, ClutterEvent *event, gpointer data);
void on_stage_button_release (ClutterStage *stage, ClutterEvent *event, gpointer data);
void on_stage_motion (ClutterStage *stage, ClutterEvent *event, gpointer data);
void on_stage_enter (ClutterStage *stage, ClutterEvent *event, gpointer data);
void on_stage_leave (ClutterStage *stage, ClutterEvent *event, gpointer data);
gboolean on_stage_scroll (ClutterActor *actor, ClutterEvent *event, gpointer userData);
gboolean button_callback_clutter (GtkWidget *widget, GdkEvent *event, gpointer callback_data);
gboolean on_stage_key_press (ClutterActor *actor, ClutterEvent *event, gpointer user_data);

/*****************************************************************************/

void MainView::loadUi (GtkForms::App *app)
{
        BuilderView::loadUi (app);

        GtkWindow *mainWindow = GTK_WINDOW (getUiOrThrow ("mainView"));
        gtk_window_maximize (mainWindow);

        GtkBox *cb = GTK_BOX (getUiOrThrow ("content"));
        gtk_widget_set_focus_on_click (GTK_WIDGET (cb), TRUE);

        if (!stage) {
                throw Core::Exception ("No stage. Create stage first, and assign it to the 'stage' pointer.");
        }

        gtk_box_pack_start (GTK_BOX (cb), stage->getClutterWidget (), TRUE, TRUE, 0);
        gtk_widget_set_can_focus (stage->getClutterWidget (), TRUE);
        gtk_widget_set_can_default (stage->getClutterWidget (), TRUE);
        gtk_widget_set_focus_on_click (stage->getClutterWidget (), TRUE);
        gtk_widget_grab_focus (stage->getClutterWidget ());

        MainController *mc = dynamic_cast<MainController *> (getController ());
        g_signal_connect (stage->getActor (), "button-press-event", G_CALLBACK (on_stage_button_press), mc);
        g_signal_connect (stage->getActor (), "button-release-event", G_CALLBACK (on_stage_button_release), mc);
        g_signal_connect (stage->getActor (), "motion-event", G_CALLBACK (on_stage_motion), mc);
        g_signal_connect (stage->getActor (), "enter-event", G_CALLBACK (on_stage_enter), mc);
        g_signal_connect (stage->getActor (), "leave-event", G_CALLBACK (on_stage_leave), mc);
        g_signal_connect (stage->getActor (), "scroll-event", G_CALLBACK (on_stage_scroll), stage);
        g_signal_connect (stage->getActor (), "key-press-event", G_CALLBACK (on_stage_key_press), mc);
        g_signal_connect (stage->getClutterWidget (), "button_press_event", G_CALLBACK (button_callback_clutter), nullptr);
}

/*****************************************************************************/

void processEvent (ClutterStage *stage, ClutterEvent *ev, Event *event)
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

        // std::cerr << event.positionScaleCoords << std::endl;

        //        ClutterVertex in, out = { 0, 0 };
        //        in.x = event.positionStageCoords.x;
        //        in.y = event.positionStageCoords.y;

        // clutter_actor_apply_relative_transform_to_point (actor, clutter_actor_get_parent (CLUTTER_ACTOR (self)), &in, &out);
        //        clutter_actor_apply_relative_transform_to_point (actor, NULL, &in, &out);
        //        // clutter_actor_apply_transform_to_point (CLUTTER_ACTOR (self), &in, &out);
}

/*****************************************************************************/

void on_stage_button_press (ClutterStage *stage, ClutterEvent *ev, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);

        static Event event;
        processEvent (stage, ev, &event);
        event.button = clutter_event_get_button (ev);

        if (event.button == 2) {
                mc->pushMessage ("stage.press.scroll", &event);
        }
        else {
                mc->pushMessage ("stage.press", &event);
        }
}

/*****************************************************************************/

void on_stage_button_release (ClutterStage *stage, ClutterEvent *ev, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);

        static Event event;
        processEvent (stage, ev, &event);
        event.button = clutter_event_get_button (ev);

        if (event.button == 2) {
                mc->pushMessage ("stage.release.scroll", &event);
        }
        else {
                mc->pushMessage ("stage.release", &event);
        }
}

/*****************************************************************************/

void on_stage_motion (ClutterStage *stage, ClutterEvent *ev, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);

        static Event event;
        processEvent (stage, ev, &event);

        if (clutter_event_get_state (ev) & CLUTTER_BUTTON1_MASK) {
                event.button = 1;
        }
        else if (clutter_event_get_state (ev) & CLUTTER_BUTTON2_MASK) {
                event.button = 2;
        }
        else if (clutter_event_get_state (ev) & CLUTTER_BUTTON3_MASK) {
                event.button = 3;
        }

        mc->pushMessage ("stage.motion", &event);
}

/*****************************************************************************/

void on_stage_enter (ClutterStage *stage, ClutterEvent *ev, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        static Event event;
        processEvent (stage, ev, &event);

        ClutterActor *actor = clutter_event_get_source (ev);
        if (actor != CLUTTER_ACTOR (stage) && actor != mc->getStage ()->getScaleLayer ()->getActor ()) {
                mc->pushMessage ("stage.enter", &event);
        }
}

/*****************************************************************************/

void on_stage_leave (ClutterStage *stage, ClutterEvent *ev, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        static Event event;
        processEvent (stage, ev, &event);

        ClutterActor *actor = clutter_event_get_source (ev);
        if (actor != CLUTTER_ACTOR (stage) && actor != mc->getStage ()->getScaleLayer ()->getActor ()) {
#if 0
                gfloat x = 0;
                gfloat y = 0;
                clutter_event_get_coords (event, &x, &y);
                ClutterActor *actor = clutter_stage_get_actor_at_pos (CLUTTER_STAGE (stage), CLUTTER_PICK_ALL, x, y);
                std::cerr << "leave : Core::Obj " << typeid (*t.second).name () << ", pointer_at " << actor << ", source " << clutter_event_get_source (event)
                          << std::endl;
#endif
                mc->pushMessage ("stage.leave", &event);
        }
}

/*****************************************************************************/

gboolean on_stage_scroll (ClutterActor *actor, ClutterEvent *ev, gpointer userData)
{
        ClutterScrollDirection direction;
        direction = clutter_event_get_scroll_direction (ev);
        Stage *stage = static_cast<Stage *> (userData);
        ScaleLayer *scale = stage->getScaleLayer ();

        if (!scale) {
                return CLUTTER_EVENT_PROPAGATE;
        }

        gfloat x = 0, y = 0, x1, y1;
        clutter_event_get_coords (ev, &x, &y);
        clutter_actor_transform_stage_point (scale->getActor (), x, y, &x1, &y1);

        switch (direction) {
        case CLUTTER_SCROLL_UP:
                scale->zoomIn (Point (x1, y1));
                break;

        case CLUTTER_SCROLL_DOWN:
                scale->zoomOut (Point (x1, y1));
                break;

        case CLUTTER_SCROLL_SMOOTH: {
                double dx, dy;
                clutter_event_get_scroll_delta (ev, &dx, &dy);

                if (dy > 0) {
                        scale->zoomOut (Point (x1, y1));
                }
                else if (dy < 0) {
                        scale->zoomIn (Point (x1, y1));
                }
        } break;

        default:
                break;
        }

        return CLUTTER_EVENT_STOP;
}

/*****************************************************************************/

gboolean on_stage_key_press (ClutterActor *actor, ClutterEvent *ev, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        static Event event;
        event.key = clutter_event_get_key_symbol (ev);
        event.state = clutter_event_get_state (ev);
        event.shiftPressed = (event.state & CLUTTER_SHIFT_MASK ? TRUE : FALSE);
        event.ctrlPressed = (event.state & CLUTTER_CONTROL_MASK ? TRUE : FALSE);

        if (event.key == CLUTTER_KEY_Delete) {
                mc->pushMessage ("stage.delete", &event);
        }
        else {
                mc->pushMessage ("stage.leave", &event);
        }

        /* The event was not handled, and the emission should continue */
        return CLUTTER_EVENT_PROPAGATE;
}

/*****************************************************************************/

gboolean button_callback_clutter (GtkWidget *widget, GdkEvent *event, gpointer callback_data)
{
        gtk_widget_grab_focus (widget);
        gboolean handled = FALSE;
        return handled;
}
