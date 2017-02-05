/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DRAWING_STUFF_H
#define DRAWING_STUFF_H

#include <glib.h>

void cogl_line (gfloat x1, gfloat y1, gfloat x2, gfloat y2, gboolean fill, float angle, float lw);

#endif // DRAWING_STUFF_H
