/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "drawing_stuff.h"
#include <cogl/cogl.h>
#include <math.h>

/*****************************************************************************/

void cogl_line (gfloat x1, gfloat y1, gfloat x2, gfloat y2, gboolean fill, float angle, float lw)
{
        if (lw <= 1) {
                cogl_path_move_to (x1, y1);
                cogl_path_line_to (x2, y2);
                cogl_path_stroke ();
                return;
        }

        double c = cos (angle);
        double s = sin (angle);

        float px = s * lw / 2.0;
        float py = c * lw / 2.0;

        cogl_path_move_to (x1 - px, y1 + py);
        cogl_path_line_to (x2 - px, y2 + py);
        cogl_path_line_to (x2 + px, y2 - py);
        cogl_path_line_to (x1 + px, y1 - py);
        cogl_path_line_to (x1 - px, y1 + py);

        if (fill) {
                cogl_path_fill ();
        }
        else {
                cogl_path_stroke ();
        }
}
