/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/clutter-gtk.h>
#include "MainView.h"
#include "clutter/iw_circle.h"
#include "clutter/iw_circular_node.h"
#include "clutter/iw_line.h"

/*****************************************************************************/

void MainView::loadUi (GtkForms::App *app)
{
        BuilderView::loadUi (app);

        GtkWindow *mainWindow = GTK_WINDOW (getUi ("mainView"));
        assert (mainWindow);
        gtk_window_maximize (mainWindow);

        GtkBox *cb = GTK_BOX (getUi ("content"));
        assert (cb);

        GtkWidget *clutter = gtk_clutter_embed_new ();
        gtk_box_pack_start (GTK_BOX (cb), clutter, TRUE, TRUE, 0);

        ClutterActor *stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutter));
        ClutterColor stage_color = { 236, 236, 236, 255 };
        clutter_actor_set_background_color (CLUTTER_ACTOR (stage), &stage_color);

        /*---------------------------------------------------------------------------*/

        {
                ClutterActor *circularNode = iw_circular_node_new ();
                clutter_actor_set_position (circularNode, 100, 300);
                iw_circular_node_set_radius (IW_CIRCULAR_NODE (circularNode), 75);
                ClutterColor actor_color = { 0, 150, 198, 201 };
                iw_circular_node_set_color (IW_CIRCULAR_NODE (circularNode), &actor_color);
                clutter_actor_set_reactive (circularNode, TRUE);

                iw_circular_node_set_ports_no (IW_CIRCULAR_NODE (circularNode), 3);
                iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (circularNode), 0, G_PI - 0.5);
                iw_circular_node_set_port_size (IW_CIRCULAR_NODE (circularNode), 0, 0.4);
                ClutterColor port_color = { 141, 141, 141, 255 };
                iw_circular_node_set_port_color (IW_CIRCULAR_NODE (circularNode), 0, &port_color);

                iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (circularNode), 1, G_PI + 0.5);
                iw_circular_node_set_port_size (IW_CIRCULAR_NODE (circularNode), 1, 0.4);
                iw_circular_node_set_port_color (IW_CIRCULAR_NODE (circularNode), 1, &port_color);

                iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (circularNode), 2, 2 * G_PI);
                iw_circular_node_set_port_size (IW_CIRCULAR_NODE (circularNode), 2, 0.4);
                ClutterColor port_color2 = { 209, 209, 209, 255 };
                iw_circular_node_set_port_color (IW_CIRCULAR_NODE (circularNode), 2, &port_color2);

                clutter_actor_add_child (stage, circularNode);

                ClutterAction *dragAction = clutter_drag_action_new ();
                clutter_actor_add_action (circularNode, dragAction);
        }

        /*---------------------------------------------------------------------------*/
        // Warning! This causes problems:
        // clutter_actor_show (stage);
}
