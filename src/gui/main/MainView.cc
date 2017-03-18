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

void MainView::loadUi (GtkForms::App *app)
{
        BuilderView::loadUi (app);

        GtkWindow *mainWindow = GTK_WINDOW (getUiOrThrow ("mainView"));
        gtk_window_maximize (mainWindow);

        GtkContainer *cb = GTK_CONTAINER (getUiOrThrow ("content"));
        gtk_widget_set_focus_on_click (GTK_WIDGET (cb), TRUE);

        if (!stage) {
                throw Core::Exception ("No stage. Create stage first, and assign it to the 'stage' pointer.");
        }

#if 0
        // Sandbox, do not delete.
        {
                ClutterActor *parent = clutter_actor_new ();
                clutter_actor_set_position (parent, 500, 500);
                // clutter_actor_set_size (parent, 100, 100);

                clutter_actor_add_child (stage->getActor (), parent);

                static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
                clutter_actor_set_background_color (CLUTTER_ACTOR (parent), &c);

                ClutterLayoutManager *layout = clutter_bin_layout_new (CLUTTER_BIN_ALIGNMENT_CENTER, CLUTTER_BIN_ALIGNMENT_CENTER);
                clutter_actor_set_layout_manager (parent, layout);

                ClutterActor *label = clutter_text_new ();
                clutter_actor_set_name (label, "text");
                clutter_text_set_text (CLUTTER_TEXT (label), "A");
                clutter_text_set_font_name (CLUTTER_TEXT (label), "20px");
                clutter_text_set_editable (CLUTTER_TEXT (label), TRUE);
                clutter_text_set_selectable (CLUTTER_TEXT (label), TRUE);
                clutter_text_set_single_line_mode (CLUTTER_TEXT (label), TRUE);
                clutter_actor_set_reactive (label, TRUE);
                clutter_actor_set_x_expand (label, TRUE);
                clutter_actor_set_x_align (label, CLUTTER_ACTOR_ALIGN_CENTER);
                clutter_actor_set_y_expand (label, TRUE);
                clutter_actor_set_y_align (label, CLUTTER_ACTOR_ALIGN_CENTER);
                clutter_actor_add_child (parent, label);

                //                GValue gVal = G_VALUE_INIT;
                //                g_value_init (&gVal, G_TYPE_FLOAT);
                //                g_value_set_float (&gVal, 100);
                //                g_object_set_property (G_OBJECT (self), "min-width", &gVal);
                //                g_value_unset (&gVal);

                //                g_value_init (&gVal, G_TYPE_FLOAT);
                //                g_value_set_float (&gVal, 100);
                //                g_object_set_property (G_OBJECT (self), "min-height", &gVal);
                //                g_value_unset (&gVal);

                //                //                g_value_init (&gVal, G_TYPE_FLOAT);
                //                //                g_value_set_float (&gVal, 10);
                //                //                g_object_set_property (G_OBJECT (self), "width", &gVal);
                //                //                g_value_unset (&gVal);

                //                g_value_init (&gVal, G_TYPE_FLOAT);
                //                g_value_set_float (&gVal, 100);
                //                g_object_set_property (G_OBJECT (self), "height", &gVal);
                //                g_value_unset (&gVal);

                //                {
                //                        GValue gVal = G_VALUE_INIT;

                //                        g_value_init (&gVal, G_TYPE_BOOLEAN);
                //                        g_value_set_float (&gVal, TRUE);
                //                        g_object_set_property (G_OBJECT (self), "x-expand", &gVal);
                //                        g_value_unset (&gVal);

                //                        g_value_init (&gVal, G_TYPE_BOOLEAN);
                //                        g_value_set_float (&gVal, TRUE);
                //                        g_object_set_property (G_OBJECT (self), "y-expand", &gVal);
                //                        g_value_unset (&gVal);
                //                }
        }
#endif

        gtk_container_add (cb, stage->getClutterWidget ());
        gtk_widget_set_can_focus (stage->getClutterWidget (), TRUE);
        gtk_widget_set_can_default (stage->getClutterWidget (), TRUE);
        gtk_widget_set_focus_on_click (stage->getClutterWidget (), TRUE);
        gtk_widget_grab_focus (stage->getClutterWidget ());
}
