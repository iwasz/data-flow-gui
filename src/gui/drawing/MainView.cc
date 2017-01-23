/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MainView.h"
#include "MainController.h"
#include "view/abstractActor.h"
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
        g_signal_connect (stage->getClutterWidget (), "button_press_event", G_CALLBACK (button_callback_clutter), nullptr);

        /*---------------------------------------------------------------------------*/

        //        {
        //                ClutterActor *circularNode = iw_circular_node_new ();
        //                clutter_actor_set_position (circularNode, 100, 300);
        //                iw_circular_node_set_radius (IW_CIRCULAR_NODE (circularNode), 75);
        //                ClutterColor actor_color = { 0, 150, 198, 201 };
        //                iw_circular_node_set_color (IW_CIRCULAR_NODE (circularNode), &actor_color);
        //                clutter_actor_set_reactive (circularNode, TRUE);

        //                iw_circular_node_set_ports_no (IW_CIRCULAR_NODE (circularNode), 3);
        //                iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (circularNode), 0, G_PI - 0.5);
        //                iw_circular_node_set_port_size (IW_CIRCULAR_NODE (circularNode), 0, 20);
        //                ClutterColor port_color = { 141, 141, 141, 255 };
        //                iw_circular_node_set_port_color (IW_CIRCULAR_NODE (circularNode), 0, &port_color);

        //                iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (circularNode), 1, G_PI + 0.5);
        //                iw_circular_node_set_port_size (IW_CIRCULAR_NODE (circularNode), 1, 20);
        //                iw_circular_node_set_port_color (IW_CIRCULAR_NODE (circularNode), 1, &port_color);

        //                iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (circularNode), 2, 2 * G_PI);
        //                iw_circular_node_set_port_size (IW_CIRCULAR_NODE (circularNode), 2, 20);
        //                ClutterColor port_color2 = { 209, 209, 209, 255 };
        //                iw_circular_node_set_port_color (IW_CIRCULAR_NODE (circularNode), 2, &port_color2);

        //                clutter_actor_add_child (stage->getActor (), circularNode);

        //                ClutterAction *dragAction = clutter_drag_action_new ();
        //                clutter_actor_add_action (circularNode, dragAction);
        //        }

        //        {
        //                ClutterActor *label = clutter_text_new ();
        //                clutter_actor_add_child (stage->getActor (), label);
        //                clutter_actor_set_position (label, 100, 300);
        //                clutter_text_set_text (CLUTTER_TEXT (label), "Hello, World!");
        //                clutter_text_set_font_name (CLUTTER_TEXT (label), "18px");
        //                clutter_text_set_editable (CLUTTER_TEXT (label), TRUE);
        //                clutter_text_set_selectable (CLUTTER_TEXT (label), TRUE);
        //                clutter_actor_set_reactive (label, TRUE);
        //        }

        //        {
        //                ClutterActor *rect = iw_rectangle_new ();
        //                clutter_actor_add_child (stage->getActor (), rect);
        //                clutter_actor_set_position (rect, 100, 300);
        //                clutter_actor_set_size (rect, 600, 600);
        //                clutter_actor_set_reactive (rect, TRUE);
        //                ClutterAction *dragAction = clutter_drag_action_new ();
        //                clutter_actor_add_action (rect, dragAction);

        //                ClutterActor *circle = iw_circle_new ();
        //                clutter_actor_add_child (rect, circle);
        //                clutter_actor_set_position (circle, 100, 100);
        //                clutter_actor_set_size (circle, 400, 400);
        //        }
}

/*****************************************************************************/

typedef std::pair<Point, Core::Object *> EventData;

EventData processEvent (ClutterStage *stage, ClutterEvent *event)
{
        gfloat x = 0;
        gfloat y = 0;
        clutter_event_get_coords (event, &x, &y);

        //        ClutterActor *actor = clutter_stage_get_actor_at_pos (CLUTTER_STAGE (stage), CLUTTER_PICK_ALL, x, y);
        ClutterActor *actor = clutter_event_get_source (event);
        Core::Object *cActor = nullptr;

        do {
                cActor = static_cast<Core::Object *> (g_object_get_data (G_OBJECT (actor), CPP_IMPLEMENTATION_KEY));

                if (cActor) {
                        break;
                }

        } while ((actor = clutter_actor_get_parent (actor)) != CLUTTER_ACTOR (stage));

        return EventData (Point (x, y), cActor);
}

/*****************************************************************************/

void on_stage_button_press (ClutterStage *stage, ClutterEvent *ev, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        EventData t = processEvent (stage, ev);

        static Event event;
        event.p = t.first;
        event.object = t.second;
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
        EventData t = processEvent (stage, ev);

        static Event event;
        event.p = t.first;
        event.object = t.second;
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
        EventData t = processEvent (stage, ev);

        static Event event;
        event.p = t.first;
        event.object = t.second;

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
        EventData t = processEvent (stage, ev);

        if (clutter_event_get_source (ev) != CLUTTER_ACTOR (stage)) {
                static Event event;
                event.p = t.first;
                event.object = t.second;
                event.button = clutter_event_get_button (ev);
                mc->pushMessage ("stage.enter", &event);
        }
}

/*****************************************************************************/

void on_stage_leave (ClutterStage *stage, ClutterEvent *ev, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        EventData t = processEvent (stage, ev);

        if (clutter_event_get_source (ev) != CLUTTER_ACTOR (stage)) {
#if 0
                gfloat x = 0;
                gfloat y = 0;
                clutter_event_get_coords (event, &x, &y);
                ClutterActor *actor = clutter_stage_get_actor_at_pos (CLUTTER_STAGE (stage), CLUTTER_PICK_ALL, x, y);
                std::cerr << "leave : Core::Obj " << typeid (*t.second).name () << ", pointer_at " << actor << ", source " << clutter_event_get_source (event)
                          << std::endl;
#endif
                static Event event;
                event.p = t.first;
                event.object = t.second;
                event.button = clutter_event_get_button (ev);
                mc->pushMessage ("stage.leave", &event);
        }
}

/*****************************************************************************/

gboolean on_stage_scroll (ClutterActor *actor, ClutterEvent *event, gpointer userData)
{
        ClutterScrollDirection direction;
        direction = clutter_event_get_scroll_direction (event);
        Stage *stage = static_cast<Stage *> (userData);

        switch (direction) {
        case CLUTTER_SCROLL_UP:
                stage->zoomIn ();
                break;

        case CLUTTER_SCROLL_DOWN:
                stage->zoomOut ();
                break;

        case CLUTTER_SCROLL_SMOOTH: {
                double dx, dy;
                clutter_event_get_scroll_delta (event, &dx, &dy);

                if (dy > 0) {
                        stage->zoomOut ();
                }
                else if (dy < 0) {
                        stage->zoomIn ();
                }
        } break;

        default:
                break;
        }

        return CLUTTER_EVENT_STOP;
}

/*****************************************************************************/

gboolean button_callback_clutter (GtkWidget *widget, GdkEvent *event, gpointer callback_data)
{
        gtk_widget_grab_focus (widget);
        gboolean handled = FALSE;
        return handled;
}
