/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONSOLE_MAINVIEW_H
#define CONSOLE_MAINVIEW_H

#include "ConsoleBuffer.h"
#include "view/BuilderView.h"
#include "view/Stage.h"

/**
 * @brief The ConsoleView class
 */
class __tiliae_reflect__ ConsoleView : public GtkForms::BuilderView {
public:
        virtual ~ConsoleView () {}
        virtual void loadUi (GtkForms::App *app);
        virtual void destroyUi ();

public:
        ConsoleBuffer *console = nullptr;
        bool autoScroll = true;

private:

        static void onInsertText (GtkTextBuffer *textBuffer, GtkTextIter *location, gchar *text, gint len, gpointer userData);
        gulong connectionId = 0;
};

#endif // MAINVIEW_H
