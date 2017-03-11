/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ConsoleView.h"
#include <gtk/gtk.h>

/*****************************************************************************/

void ConsoleView::loadUi (GtkForms::App *app)
{
        BuilderView::loadUi (app);

        GtkTextView *textView = GTK_TEXT_VIEW (getUiOrThrow (">console"));
        gtk_text_view_set_buffer (textView, console->getGtkTextBuffer ());
}
