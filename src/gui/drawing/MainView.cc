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
}
