/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_line.h"
#include <math.h>

G_DEFINE_TYPE (IwLine, iw_line, IW_TYPE_ACTOR);
#define IW_LINE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_LINE, IwLinePrivate))

struct _IwLinePrivate {
        gfloat ax, ay;
        gfloat bx, by;
        ClutterActor *label;
};

static gboolean draw_line (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);
static void iw_line_resize_accordingly (IwLine *self);
void onTextChanged (void *lineConnector, const char *text);

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

/*****************************************************************************/

static void iw_line_paint_priv (ClutterActor *actor, const ClutterColor *color, gboolean fill)
{
        ClutterActorBox allocation = {
                0,
        };

        gfloat width, height;

        clutter_actor_get_allocation_box (actor, &allocation);
        clutter_actor_box_get_size (&allocation, &width, &height);

        cogl_path_new ();
        cogl_set_source_color4ub (color->red, color->green, color->blue, color->alpha);

        float lw = iw_actor_get_stroke_width (IW_ACTOR (actor));

        float ax = IW_LINE (actor)->priv->ax;
        float ay = IW_LINE (actor)->priv->ay;
        float bx = IW_LINE (actor)->priv->bx;
        float by = IW_LINE (actor)->priv->by;

        float angle = atan ((ay - by) / (ax - bx));

        if (ax < bx && ay < by) {
                cogl_line (0, 0, width, height, fill, angle, lw);
        }
        else if (ax > bx && ay > by) {
                cogl_line (width, height, 0, 0, fill, angle, lw);
        }
        else if (ax > bx && ay < by) {
                cogl_line (width, 0, 0, height, fill, angle, lw);
        }
        else if (ax < bx && ay > by) {
                cogl_line (0, height, width, 0, fill, angle, lw);
        }

        for (ClutterActor *iter = clutter_actor_get_first_child (actor); iter != NULL; iter = clutter_actor_get_next_sibling (iter)) {
                clutter_actor_paint (iter);
        }
}

/*****************************************************************************/

static void iw_line_pick (ClutterActor *actor, const ClutterColor *pick_color)
{
        if (!clutter_actor_should_pick_paint (actor)) {
                return;
        }

        iw_line_paint_priv (actor, pick_color, TRUE);
}

/*****************************************************************************/

static void iw_line_paint (ClutterActor *actor)
{
        ClutterColor *strokeColor = iw_actor_get_stroke_color (IW_ACTOR (actor));
        iw_line_paint_priv (actor, strokeColor, TRUE);
}

/*****************************************************************************/

static void iw_line_class_init (IwLineClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        actor_class->pick = iw_line_pick;
        actor_class->paint = iw_line_paint;
        g_type_class_add_private (klass, sizeof (IwLinePrivate));
}

/*****************************************************************************/

void on_text_changed (ClutterText *self, gpointer user_data)
{
        /*printf ("%s\n", clutter_text_get_text (self));*/
        IwLine *line = (IwLine *)user_data;
        iw_line_resize_accordingly (line);
        onTextChanged (iw_actor_get_user_data (IW_ACTOR (line)), clutter_text_get_text (self));
}

/*****************************************************************************/

static void iw_line_init (IwLine *self)
{
        IwLinePrivate *priv = self->priv = IW_LINE_GET_PRIVATE (self);
        priv->ax = 0;
        priv->ay = 0;
        priv->bx = 0;
        priv->by = 0;

        priv->label = clutter_text_new ();
        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->label);
        clutter_text_set_font_name (CLUTTER_TEXT (priv->label), "18px");
        clutter_text_set_editable (CLUTTER_TEXT (priv->label), FALSE);
        clutter_text_set_selectable (CLUTTER_TEXT (priv->label), TRUE);
        clutter_text_set_single_line_mode (CLUTTER_TEXT (priv->label), TRUE);
        clutter_actor_set_reactive (priv->label, TRUE);
        g_signal_connect (priv->label, "text-changed", G_CALLBACK (on_text_changed), self);

#if 0
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (CLUTTER_ACTOR (self), &c);
        clutter_actor_set_background_color (CLUTTER_ACTOR (self->priv->label), &c);
#endif

        //        ClutterContent *canvas = iw_actor_get_canvas (IW_ACTOR (self));
        //        g_signal_connect (canvas, "draw", G_CALLBACK (draw_line), self);
        //        clutter_content_invalidate (canvas);
}

/*****************************************************************************/

static void iw_line_resize_accordingly (IwLine *self)
{
        gfloat strokeWidth = iw_actor_get_stroke_width (IW_ACTOR (self));
        float lw = 0; // strokeWidth;
        float ax = self->priv->ax;
        float ay = self->priv->ay;
        float bx = self->priv->bx;
        float by = self->priv->by;
        float px = fmin (ax, bx);
        float py = fmin (ay, by);
        clutter_actor_set_position (CLUTTER_ACTOR (self), px - lw, py - lw);

        float qx = fmax (ax, bx);
        float qy = fmax (ay, by);
        clutter_actor_set_size (CLUTTER_ACTOR (self), qx - px + 2 * lw, qy - py + 2 * lw);

        if (clutter_text_get_text (CLUTTER_TEXT (self->priv->label)) != NULL && ax != bx) {
                float angle = atan ((ay - by) / (ax - bx));
                clutter_actor_set_rotation_angle (self->priv->label, CLUTTER_Z_AXIS, angle * 180 / M_PI);
                // printf ("%f, %f, %f, %f, %f\n", angle, ax, ay, bx, by);

                double c = cos (angle);
                double s = sin (angle);

                float tw = clutter_actor_get_width (CLUTTER_ACTOR (self->priv->label));
                float px = c * tw;
                float py = s * tw;

                float lh = strokeWidth;
                px += s * lh;
                py -= c * lh;

                float w = clutter_actor_get_width (CLUTTER_ACTOR (self)) - px;
                float h = clutter_actor_get_height (CLUTTER_ACTOR (self)) - py;
                clutter_actor_set_position (CLUTTER_ACTOR (self->priv->label), w / 2, h / 2);
        }
        else {
                float tw = clutter_actor_get_width (CLUTTER_ACTOR (self->priv->label));
                clutter_actor_set_position (CLUTTER_ACTOR (self->priv->label), -tw / 2.0, strokeWidth);
        }

        clutter_text_set_editable (CLUTTER_TEXT (self->priv->label), TRUE);
}

/*****************************************************************************/

void iw_line_set_point_a (IwLine *self, gfloat x, gfloat y)
{
        g_return_if_fail (IW_IS_LINE (self));
        self->priv->ax = x;
        self->priv->ay = y;
        iw_line_resize_accordingly (self);
}

/*****************************************************************************/

void iw_line_get_point_a (IwLine *self, gfloat *x, gfloat *y)
{
        g_return_if_fail (IW_IS_LINE (self));
        *x = self->priv->ax;
        *y = self->priv->ay;
}

/*****************************************************************************/

void iw_line_set_point_b (IwLine *self, gfloat x, gfloat y)
{
        g_return_if_fail (IW_IS_LINE (self));
        self->priv->bx = x;
        self->priv->by = y;
        iw_line_resize_accordingly (self);
}

/*****************************************************************************/

void iw_line_get_point_b (IwLine *self, gfloat *x, gfloat *y)
{
        g_return_if_fail (IW_IS_LINE (self));
        *x = self->priv->bx;
        *y = self->priv->by;
}

/*****************************************************************************/

ClutterActor *iw_line_new (void) { return g_object_new (IW_TYPE_LINE, NULL); }

/*****************************************************************************/

static gboolean draw_line (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data)
{
        IwLine *self = (IwLine *)data;
        IwLinePrivate *priv = self->priv;

        cairo_save (cr);

        /* clear the contents of the canvas, to avoid painting
         * over the previous frame
         */
        cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
        cairo_paint (cr);

        cairo_restore (cr);

        cairo_set_operator (cr, CAIRO_OPERATOR_OVER);

        gfloat strokeWidth = iw_actor_get_stroke_width (IW_ACTOR (self));
        gfloat strokeDash = iw_actor_get_stroke_dash (IW_ACTOR (self));
        ClutterColor *strokeColor = iw_actor_get_stroke_color (IW_ACTOR (self));

        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_width (cr, strokeWidth);

        if (strokeDash > 0) {
                double dashed1 = strokeDash;
                cairo_set_dash (cr, &dashed1, 1, 0);
        }

        clutter_cairo_set_source_color (cr, strokeColor);

        // Prevent clipping.
        float margin = strokeWidth /*/ 2.0 + 0.5*/;

        float ax = priv->ax;
        float ay = priv->ay;
        float bx = priv->bx;
        float by = priv->by;

        if (ax < bx && ay < by) {
                cairo_move_to (cr, margin, margin);
                cairo_line_to (cr, width - margin, height - margin);
        }
        else if (ax > bx && ay > by) {
                cairo_move_to (cr, width - margin, height - margin);
                cairo_line_to (cr, margin, margin);
        }

        else if (ax > bx && ay < by) {
                cairo_move_to (cr, width - margin, margin);
                cairo_line_to (cr, margin, height - margin);
        }
        else if (ax < bx && ay > by) {
                cairo_move_to (cr, margin, height - margin);
                cairo_line_to (cr, width - margin, margin);
        }

        cairo_stroke (cr);
        return TRUE;
}

/*****************************************************************************/

const gchar *iw_line_get_text (IwLine *self)
{
        g_return_val_if_fail (IW_IS_LINE (self), NULL);
        return clutter_text_get_text (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

void iw_line_set_text (IwLine *self, const gchar *s)
{
        g_return_if_fail (IW_IS_LINE (self));
        clutter_text_set_text (CLUTTER_TEXT (self->priv->label), s);
}

/*****************************************************************************/

const gchar *iw_line_get_font (IwLine *self)
{
        g_return_val_if_fail (IW_IS_LINE (self), NULL);
        return clutter_text_get_font_name (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

void iw_line_set_font (IwLine *self, const gchar *s)
{
        g_return_if_fail (IW_IS_LINE (self));
        clutter_text_set_font_name (CLUTTER_TEXT (self->priv->label), s);
}

/*****************************************************************************/

void iw_line_get_font_color (IwLine *self, ClutterColor *color)
{
        g_return_if_fail (IW_IS_LINE (self));
        return clutter_text_get_color (CLUTTER_TEXT (self->priv->label), color);
}

/*****************************************************************************/

void iw_line_set_font_color (IwLine *self, const ClutterColor *c)
{
        g_return_if_fail (IW_IS_LINE (self));
        clutter_text_set_color (CLUTTER_TEXT (self->priv->label), c);
}

/*****************************************************************************/

gboolean iw_line_is_editable (IwLine *self)
{
        g_return_val_if_fail (IW_IS_LINE (self), FALSE);
        return clutter_text_get_editable (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

void iw_line_set_editable (IwLine *self, gboolean b)
{
        g_return_if_fail (IW_IS_LINE (self));
        clutter_text_set_editable (CLUTTER_TEXT (self->priv->label), b);
}
