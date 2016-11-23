/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <GtkForms.h>
#include <gtk/gtk.h>
#include <Tiliae.h>

//// TODO czemu to musi tu być? Czemu tiliaeparser zamienia bool na to _Bool?
#define _Bool bool
#include "Reflection_output_tiliae.cc.h"
#include "Reflection_output_gtkforms.cc.h"
#include "Reflection_output.cc.h"

int main (int argc, char **argv)
{
        srand (time (0));
        gtk_init (&argc, &argv);
        GtkForms::App app {"config.xml", "mainController"};
        gtk_main ();
}


