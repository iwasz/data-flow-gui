/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MainView.h"
#include "MainController.h"
#include "clutter/iw_circle.h"
#include "clutter/iw_circular_node.h"
#include "clutter/iw_line.h"
#include <clutter-gtk/clutter-gtk.h>
#include <clutter/clutter.h>
#include <gtk/gtk.h>

/*****************************************************************************/

static void on_stage_button_press (ClutterStage *stage, ClutterEvent *event, gpointer data);
static void on_stage_button_release (ClutterStage *stage, ClutterEvent *event, gpointer data);
static void on_stage_motion (ClutterStage *stage, ClutterEvent *event, gpointer data);

/*****************************************************************************/

void MainView::loadUi (GtkForms::App *app)
{
        BuilderView::loadUi (app);

        GtkWindow *mainWindow = GTK_WINDOW (getUiOrThrow ("mainView"));
        gtk_window_maximize (mainWindow);

        GtkBox *cb = GTK_BOX (getUiOrThrow ("content"));

        GtkWidget *palette = gtk_tool_palette_new ();
        gtk_box_pack_start (GTK_BOX (cb), palette, FALSE, TRUE, 0);

        GtkWidget *group = gtk_tool_item_group_new ("Test Category");
        gtk_container_add (GTK_CONTAINER (palette), group);

        GtkToolItem *item = gtk_tool_button_new (NULL, "Add");
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (item), "gtk-add");
        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);
        connectSignal (item, "clicked", "$controller.onNewNodeToolClicked ('addNode')");

        item = gtk_tool_button_new (NULL, "Copy");
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (item), "gtk-go-forward");
        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);
        connectSignal (item, "clicked", "$controller.onNewNodeToolClicked ('copyNode')");

        item = gtk_tool_button_new (NULL, "Arc");
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (item), "gtk-edit");
        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);
        connectSignal (item, "clicked", "$controller.onNewNodeToolClicked ('arc')");

        item = gtk_tool_button_new (NULL, "Circle");
        gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (item), "gtk-media-record");
        gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP (group), item, -1);
        connectSignal (item, "clicked", "$controller.onNewNodeToolClicked ('circle')");

        /*---------------------------------------------------------------------------*/

        //        GtkWidget *clutter = gtk_clutter_embed_new ();

        if (!stage) {
                throw Core::Exception ("No stage. Create stage first, and assign it to the 'stage' pointer.");
        }

        gtk_box_pack_start (GTK_BOX (cb), stage->getClutterWidget (), TRUE, TRUE, 0);

        //        ClutterActor *stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutter));
        //        ClutterColor stage_color = { 236, 236, 236, 255 };
        //        clutter_actor_set_background_color (CLUTTER_ACTOR (stage), &stage_color);

        MainController *mc = dynamic_cast<MainController *> (getController ());
        g_signal_connect (stage->getActor (), "button-press-event", G_CALLBACK (on_stage_button_press), mc);
        g_signal_connect (stage->getActor (), "button-release-event", G_CALLBACK (on_stage_button_release), mc);
        g_signal_connect (stage->getActor (), "motion-event", G_CALLBACK (on_stage_motion), mc);

        /*---------------------------------------------------------------------------*/

        {
        }
}

/*****************************************************************************/

static void on_stage_button_press (ClutterStage *stage, ClutterEvent *event, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        // find out which part of the screen was clicked
        gfloat x = 0;
        gfloat y = 0;
        clutter_event_get_coords (event, &x, &y);

        // find which actor was clicked
        ClutterActor *clicked = clutter_stage_get_actor_at_pos (CLUTTER_STAGE (stage), CLUTTER_PICK_ALL, x, y);

        // Pobrać model
        // Czy to jest arc.
        // Czy to jest port (jeśli port, to porty będzie wiedział do jakiego node należy). Numer portu.
        //

        if (clicked == CLUTTER_ACTOR (stage)) {
                mc->onButtonPress (x, y);
        }

        // hide the actor that was clicked
        //        clutter_actor_hide (clicked);
}

/*****************************************************************************/

static void on_stage_button_release (ClutterStage *stage, ClutterEvent *event, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        // find out which part of the screen was clicked
        gfloat x = 0;
        gfloat y = 0;
        clutter_event_get_coords (event, &x, &y);

        // find which actor was clicked
        mc->onButtonRelease (x, y);
}

/*****************************************************************************/

static void on_stage_motion (ClutterStage *stage, ClutterEvent *event, gpointer data)
{
        MainController *mc = static_cast<MainController *> (data);
        // find out which part of the screen was clicked
        gfloat x = 0;
        gfloat y = 0;
        clutter_event_get_coords (event, &x, &y);

        // ClutterActor *motion = clutter_stage_get_actor_at_pos (CLUTTER_STAGE (stage), CLUTTER_PICK_ALL, x, y);

        // find which actor was clicked
        mc->onMotion (x, y);
}
