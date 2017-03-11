/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ConsoleBuffer.h"
#include <core/Exception.h>

ConsoleBuffer *console = nullptr;

struct ConsoleBuffer::Impl {
        Impl () : textBuffer (gtk_text_buffer_new (nullptr)) {}
        ~Impl () { g_object_unref (textBuffer); }
        GtkTextBuffer *textBuffer;
};

/*****************************************************************************/

ConsoleBuffer::ConsoleBuffer () : impl (new Impl)
{

        if (console != nullptr) {
                throw Core::Exception ("ConsoleBuffer::ConsoleBuffer : error initializing static pointer");
        }

        console = this;
}

/*****************************************************************************/

ConsoleBuffer::~ConsoleBuffer () { delete impl; }

/*****************************************************************************/

GtkTextBuffer *ConsoleBuffer::getGtkTextBuffer () { return impl->textBuffer; }

/*****************************************************************************/

void ConsoleBuffer::append (std::string const &txt)
{
        GtkTextIter iter;
        gtk_text_buffer_get_end_iter (impl->textBuffer, &iter);
        gtk_text_buffer_insert (impl->textBuffer, &iter, txt.c_str (), txt.size ());
}

/*****************************************************************************/

void ConsoleBuffer::clear () { gtk_text_buffer_set_text (impl->textBuffer, "", 0); }

