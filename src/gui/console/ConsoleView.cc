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

        g_signal_connect (console->getGtkTextBuffer (), "insert-text", G_CALLBACK (&ConsoleView::onInsertText), this);
}

/*****************************************************************************/

void ConsoleView::onInsertText (GtkTextBuffer *textBuffer, GtkTextIter *location, gchar *text, gint len, gpointer userData)
{
        ConsoleView *that = static_cast<ConsoleView *> (userData);
        GtkTextView *textView = GTK_TEXT_VIEW (that->getUiOrThrow (">console"));

        if (that->autoScroll) {
                GtkTextBuffer *buffer = gtk_text_view_get_buffer (textView);

                GtkTextMark *mark = gtk_text_buffer_get_mark (buffer, "mark");

                if (!mark) {
                        mark = gtk_text_buffer_create_mark (buffer, "mark", location, false);
                        gtk_text_mark_set_visible (mark, true);
                }
                else {
                        gtk_text_buffer_move_mark (buffer, mark, location);
                }

                gtk_text_view_scroll_to_mark (textView, mark, 0, false, 0, 0);
        }
}
