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
#include <clutter-gtk/clutter-gtk.h>
#include <clutter/clutter.h>
#include <gtk/gtk.h>

/*****************************************************************************/

static void on_stage_button_press (ClutterStage *stage, ClutterEvent *event, gpointer data);
static void on_stage_button_release (ClutterStage *stage, ClutterEvent *event, gpointer data);
static void on_stage_motion (ClutterStage *stage, ClutterEvent *event, gpointer data);
static void on_stage_enter (ClutterStage *stage, ClutterEvent *event, gpointer data);
static void on_stage_leave (ClutterStage *stage, ClutterEvent *event, gpointer data);
static gboolean button_callback_clutter (GtkWidget *widget, GdkEvent *event, gpointer callback_data);

/*****************************************************************************/

void MainView::loadUi (GtkForms::App *app)
{
        BuilderView::loadUi (app);

        GtkWindow *mainWindow = GTK_WINDOW (getUiOrThrow ("mainView"));
        gtk_window_maximize (mainWindow);

        GtkBox *cb = GTK_BOX (getUiOrThrow ("content"));
        gtk_widget_set_focus_on_click (GTK_WIDGET (cb), TRUE);

        GtkWidget *p = GTK_WIDGET (getUiOrThrow ("drawing_tool_palette"));
        gtk_widget_show_all (p);

        GtkWidget *g = GTK_WIDGET (getUiOrThrow ("left_tools"));
        gtk_widget_show (g);
        gtk_widget_show_all (g);

        GtkWidget *w = GTK_WIDGET (getUiOrThrow ("left_rect_select_tool"));
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (w), "gtk-add");
        //        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (g), GTK_TOOL_ITEM (w), -1);
        gtk_widget_show (w);

        /*---------------------------------------------------------------------------*/

//        GtkWidget *palette = gtk_tool_palette_new ();
//        gtk_box_pack_start (GTK_BOX (cb), palette, FALSE, TRUE, 0);

        GtkWidget *group = gtk_tool_item_group_new ("Test Category");
        gtk_container_add (GTK_CONTAINER (p), group);

        GtkToolItem *item = gtk_tool_button_new (NULL, "Add");
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (item), "gtk-add");
        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);
        connectSignal (item, "clicked", "$controller.onNewNodeToolClicked ('addNode')");

//        This works, so items are loaded.
//        item = GTK_TOOL_ITEM (getUiOrThrow ("toolButton"));
//        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);

        item = gtk_tool_button_new (NULL, "Copy");
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (item), "gtk-go-forward");
        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);
        connectSignal (item, "clicked", "$controller.onNewNodeToolClicked ('copyNode')");

        item = gtk_tool_button_new (NULL, "Line");
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (item), "gtk-edit");
        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);
        connectSignal (item, "clicked", "$controller.onNewNodeToolClicked ('line')");

        item = gtk_tool_button_new (NULL, "Circle");
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (item), "gtk-media-record");
        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);
        connectSignal (item, "clicked", "$controller.onNewNodeToolClicked ('circle')");

        item = gtk_tool_button_new (NULL, "LineConnector");
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (item), "gtk-edit");
        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);
        connectSignal (item, "clicked", "$controller.onNewNodeToolClicked ('lineConnector')");

        item = gtk_tool_button_new (NULL, "Connect");
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (item), "gtk-edit");
        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);

        /*---------------------------------------------------------------------------*/

        //        GtkWidget *clutter = gtk_clutter_embed_new ();

        if (!stage) {
                throw Core::Exception ("No stage. Create stage first, and assign it to the 'stage' pointer.");
        }

        // Does not have any effect. Why?
        // clutter_stage_set_motion_events_enabled (CLUTTER_STAGE (stage->getActor ()), FALSE);

        gtk_box_pack_start (GTK_BOX (cb), stage->getClutterWidget (), TRUE, TRUE, 0);
        gtk_widget_set_can_focus (stage->getClutterWidget (), TRUE);
        gtk_widget_set_can_default (stage->getClutterWidget (), TRUE);
        gtk_widget_set_focus_on_click (stage->getClutterWidget (), TRUE);
        gtk_widget_grab_focus (stage->getClutterWidget ());

        //        ClutterActor *stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutter));
        //        ClutterColor stage_color = { 236, 236, 236, 255 };
        //        clutter_actor_set_background_color (CLUTTER_ACTOR (stage), &stage_color);

        MainController *mc = dynamic_cast<MainController *> (getController ());
        g_signal_connect (stage->getActor (), "button-press-event", G_CALLBACK (on_stage_button_press), mc);
        g_signal_connect (stage->getActor (), "button-release-event", G_CALLBACK (on_stage_button_release), mc);
        g_signal_connect (stage->getActor (), "motion-event", G_CALLBACK (on_stage_motion), mc);
        g_signal_connect (stage->getActor (), "enter-event", G_CALLBACK (on_stage_enter), mc);
        g_signal_connect (stage->getActor (), "leave-event", G_CALLBACK (on_stage_leave), mc);
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

void on_stage_button_press (ClutterStage *stage, ClutterEvent *event, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        EventData t = processEvent (stage, event);
#if 0
        gfloat x = 0;
        gfloat y = 0;
        clutter_event_get_coords (event, &x, &y);
        ClutterActor *actor = clutter_stage_get_actor_at_pos (CLUTTER_STAGE (stage), CLUTTER_PICK_ALL, x, y);
        std::cerr << "press : Core::Obj " << typeid (*t.second).name () << ", pointer_at " << actor << ", source " << clutter_event_get_source (event)
                  << std::endl;
#endif
        mc->onButtonPress (t.first, t.second);
}

/*****************************************************************************/

void on_stage_button_release (ClutterStage *stage, ClutterEvent *event, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        EventData t = processEvent (stage, event);
        mc->onButtonRelease (t.first, t.second);
}

/*****************************************************************************/

void on_stage_motion (ClutterStage *stage, ClutterEvent *event, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        EventData t = processEvent (stage, event);
        mc->onMotion (t.first, t.second);
}

/*****************************************************************************/

void on_stage_enter (ClutterStage *stage, ClutterEvent *event, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        EventData t = processEvent (stage, event);

        if (clutter_event_get_source (event) != CLUTTER_ACTOR (stage)) {
#if 0
                gfloat x = 0;
                gfloat y = 0;
                clutter_event_get_coords (event, &x, &y);
                ClutterActor *actor = clutter_stage_get_actor_at_pos (CLUTTER_STAGE (stage), CLUTTER_PICK_ALL, x, y);
                std::cerr << "enter : Core::Obj " << typeid (*t.second).name () << ", pointer_at " << actor << ", source " << clutter_event_get_source (event)
                          << std::endl;
#endif
                mc->onEnter (t.first, t.second);
        }
}

/*****************************************************************************/

void on_stage_leave (ClutterStage *stage, ClutterEvent *event, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        EventData t = processEvent (stage, event);

        if (clutter_event_get_source (event) != CLUTTER_ACTOR (stage)) {
#if 0
                gfloat x = 0;
                gfloat y = 0;
                clutter_event_get_coords (event, &x, &y);
                ClutterActor *actor = clutter_stage_get_actor_at_pos (CLUTTER_STAGE (stage), CLUTTER_PICK_ALL, x, y);
                std::cerr << "leave : Core::Obj " << typeid (*t.second).name () << ", pointer_at " << actor << ", source " << clutter_event_get_source (event)
                          << std::endl;
#endif
                mc->onLeave (t.first, t.second);
        }
}

/*****************************************************************************/

static gboolean button_callback_clutter (GtkWidget *widget, GdkEvent *event, gpointer callback_data)
{
        gtk_widget_grab_focus (widget);
        gboolean handled = FALSE;
        return handled;
}
