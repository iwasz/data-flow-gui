/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TEXT_CONSOLE_H
#define TEXT_CONSOLE_H

#include <ReflectionParserAnnotation.h>
#include <gtk/gtk.h>
#include <ostream>
#include <string>

/**
 * Output "console"
 */
class __tiliae_reflect__ ConsoleBuffer {
public:
        ConsoleBuffer ();
        virtual ~ConsoleBuffer ();

        GtkTextBuffer *getGtkTextBuffer ();
        void append (std::string const &txt);
        void clear ();

private:
        struct Impl;
        Impl *impl;
};

extern ConsoleBuffer *console;

#endif // CONSOLE_H
