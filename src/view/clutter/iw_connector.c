/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_connector.h"
#include "drawing_stuff.h"
#include <math.h>
#include <memory.h>
#include <stdbool.h>

G_DEFINE_TYPE (IwConnector, iw_connector, IW_TYPE_ACTOR);
#define IW_CONNECTOR_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_CONNECTOR, IwConnectorPrivate))

struct _IwConnectorPrivate {
        CPoint *points;
        size_t len;
        ClutterActor *label;
};

static gboolean draw_line (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);
static void iw_connector_resize_accordingly (IwConnector *self);
void onTextChangedConnector (void *lineConnector, const char *text);

/*****************************************************************************/

static void iw_connector_paint_priv (ClutterActor *actor, const ClutterColor *color, gboolean fill)
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

#if 0
        cogl_path_move_to (ax, ay);

        //        cogl_path_arc (getX (actor, 0), getY (actor, 0), 10, 10, 0, 90);

        cogl_path_rel_line_to (getX (actor, 0), getY (actor, 0));
        cogl_path_rel_line_to (getX (actor, 1), getY (actor, 1));
        cogl_path_rel_line_to (getX (actor, 2), getY (actor, 2));
        cogl_path_move_to (bx, by);
        cogl_path_rel_line_to (getX (actor, 4), getY (actor, 4));
        cogl_path_rel_line_to (getX (actor, 3), getY (actor, 3));
        cogl_path_stroke ();
#endif

#if 0
        primitives::Point a = { ax, ay };
        primitives::Point b = { bx, by };
        Line s0 = rayNew (ax, ay, aDir);
        Line s1;
        Line s2;
        Line s3;
        Line s4;
        Line s5 = rayNew (bx, by, bDir);

        // printf ("%d, %d\n", aDir, bDir);

        // Todo decrease number of elements
        primitives::Point pointsFromA[10];
        primitives::Point pointsFromB[10];

        int pFACnt = 0;
        int pFBCnt = 0;

        // Step 1. Draw 2 rays from both points (a and b) in correct directions. Check if they corss or connec
        primitives::Point p, t1, t2;

        // Sum of angles 90 (number of angles 1)
        if (raysCross (&s0, &s5, &p) || raysConnect (&s0, &s5, &p)) {
                // Special case : right angle.
                addPoint (pointsFromA, p.x, p.y, &pFACnt);
                addPoint (pointsFromB, p.x, p.y, &pFBCnt);
        }

        // Sum of angles 0 (number of angles 0, 2, 4)
        // Step 2.0 Compute segments s1 and s4 if s0 and s5 did not cross.
        else {
                // Ray s1
                float d = distance (&a, &b, s0.direction);
                p = advance (&a, s0.direction, MIN_SEGMENT_LENGTH);
                float d2 = distance (&p, &b, s0.direction);

                // Compare distance between head and tail before and after the advance.
                if (d2 < d) { // If distance decreased
                        // Make right turn in half the way between a and b.
                        p = advance (&a, s0.direction, d / 2.0);
                }
                // ELSE (distance increased or stayed the same) Make right turn in point p (MIN_SEGMENT_LENGTH distance from a).

                addPoint (pointsFromA, p.x, p.y, &pFACnt);
                s1 = rayPerpendicular (&s0 /*Perpendicular to*/, &b /*Towards point*/, &p /*Starting at point*/);

                // Ray s4
                d = distance (&b, &a, s5.direction);
                p = advance (&b, s5.direction, MIN_SEGMENT_LENGTH);
                d2 = distance (&p, &a, s5.direction);

                // Compare distance between head and tail before and after the advance.
                if (d2 < d) { // If distance decreased
                        // Make right turn in half the way between a and b.
                        p = advance (&b, s5.direction, d / 2.0);
                }
                // ELSE (distance increased or stayed the same) Make right turn in point p (MIN_SEGMENT_LENGTH distance from a).

                addPoint (pointsFromB, p.x, p.y, &pFBCnt);
                s4 = rayPerpendicular (&s5 /*Perpendicular to*/, &a /*Towards point*/, &p /*Starting at point*/);

                // Step 2.1
                if (raysConnect (&s1, &s4, &p)) {
                        addPoint (pointsFromA, p.x, p.y, &pFACnt);
                        addPoint (pointsFromB, p.x, p.y, &pFBCnt);
                }
                if (raysCross (&s1, &s5, &p)) {
                        // Special case 1 : sum of angles = 180
                        addPoint (pointsFromA, p.x, p.y, &pFACnt);
                        addPoint (pointsFromA, b.x, b.y, &pFACnt);
                }
                else if (raysCross (&s4, &s0, &p)) {
                        // Special case 2 : sum of angles = 180
                        addPoint (pointsFromB, p.x, p.y, &pFBCnt);
                        addPoint (pointsFromB, a.x, a.y, &pFBCnt);
                }
                else {
                        a.x = s1.ax;
                        a.y = s1.ay;
                        b.x = s4.ax;
                        b.y = s4.ay;

                        // Ray s2
                        float d = distance (&a, &b, s1.direction);
                        p = advance (&a, s1.direction, MIN_SEGMENT_LENGTH);

                        // Compare distance between head and tail before and after the advance.
                        if (distance (&p, &b, s1.direction) < d) { // If distance decreased
                                // Make right turn in half the way between a and b.
                                p = advance (&a, s1.direction, d / 2.0);
                        }
                        // ELSE (distance increased or stayed the same) Make right turn in point p (MIN_SEGMENT_LENGTH distance from a).

                        addPoint (pointsFromA, p.x, p.y, &pFACnt);
                        s2 = rayPerpendicular (&s1 /*Perpendicular to*/, &b /*Towards point*/, &p /*Starting at point*/);

                        // Ray s3
                        d = distance (&b, &a, s4.direction);
                        p = advance (&b, s4.direction, MIN_SEGMENT_LENGTH);

                        // Compare distance between head and tail before and after the advance.
                        if (distance (&p, &a, s4.direction) < d) { // If distance decreased
                                // Make right turn in half the way between a and b.
                                p = advance (&b, s4.direction, d / 2.0);
                        }
                        // ELSE (distance increased or stayed the same) Make right turn in point p (MIN_SEGMENT_LENGTH distance from a).

                        addPoint (pointsFromB, p.x, p.y, &pFBCnt);
                        s3 = rayPerpendicular (&s4 /*Perpendicular to*/, &a /*Towards point*/, &p /*Starting at point*/);

                        // Step 2.1
                        if (raysCross (&s2, &s3, &p) || raysConnect (&s2, &s3, &p)) {
                                addPoint (pointsFromA, p.x, p.y, &pFACnt);
                                addPoint (pointsFromB, p.x, p.y, &pFBCnt);
                        }
                        else {
                                printf ("Warning! Rays mismatch!");
                        }
                }
        }
        /// Step x. Draw.

        cogl_path_move_to (ax, ay);

        for (int i = 0; i < pFACnt; ++i) {
                cogl_path_line_to (pointsFromA[i].x, pointsFromA[i].y);
        }

        cogl_path_move_to (bx, by);

        for (int i = 0; i < pFBCnt; ++i) {
                cogl_path_line_to (pointsFromB[i].x, pointsFromB[i].y);
        }

        cogl_path_stroke ();
#endif

        CPoint *points = IW_CONNECTOR (actor)->priv->points;
        size_t len = IW_CONNECTOR (actor)->priv->len;

        for (int i = 0; i < len; ++i) {
                CPoint *p = points + i;
                cogl_path_line_to (p->x, p->y);
        }

        cogl_path_stroke ();

        ClutterActor *iter = clutter_actor_get_first_child (actor);

        if (iter) {
                for (; iter != NULL; iter = clutter_actor_get_next_sibling (iter)) {
                        clutter_actor_paint (iter);
                }
        }
}

/*****************************************************************************/

static void iw_connector_pick (ClutterActor *actor, const ClutterColor *pick_color)
{
        if (!clutter_actor_should_pick_paint (actor)) {
                return;
        }

        iw_connector_paint_priv (actor, pick_color, TRUE);
}

/*****************************************************************************/

static void iw_connector_paint (ClutterActor *actor)
{
        ClutterColor *strokeColor = iw_actor_get_stroke_color (IW_ACTOR (actor));
        iw_connector_paint_priv (actor, strokeColor, TRUE);
}

/*****************************************************************************/

static void iw_connector_class_init (IwConnectorClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        actor_class->pick = iw_connector_pick;
        actor_class->paint = iw_connector_paint;
        g_type_class_add_private (klass, sizeof (IwConnectorPrivate));
}

/*****************************************************************************/

static void on_text_changed (ClutterText *self, gpointer user_data)
{
        IwConnector *line = (IwConnector *)user_data;
        //        iw_connector_resize_accordingly (line);
        onTextChangedConnector (iw_actor_get_user_data (IW_ACTOR (line)), clutter_text_get_text (self));
}

/*****************************************************************************/

static void iw_connector_init (IwConnector *self)
{
        IwConnectorPrivate *priv = self->priv = IW_CONNECTOR_GET_PRIVATE (self);
        priv->points = NULL;
        priv->len = 0;

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
}

/*****************************************************************************/

#if 0
static void iw_connector_resize_accordingly (IwConnector *self)
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
#endif

/*****************************************************************************/

ClutterActor *iw_connector_new (void) { return g_object_new (IW_TYPE_CONNECTOR, NULL); }

/*****************************************************************************/

const gchar *iw_connector_get_text (IwConnector *self)
{
        g_return_val_if_fail (IW_IS_CONNECTOR (self), NULL);
        return clutter_text_get_text (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

void iw_connector_set_text (IwConnector *self, const gchar *s)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        clutter_text_set_text (CLUTTER_TEXT (self->priv->label), s);
}

/*****************************************************************************/

const gchar *iw_connector_get_font (IwConnector *self)
{
        g_return_val_if_fail (IW_IS_CONNECTOR (self), NULL);
        return clutter_text_get_font_name (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

void iw_connector_set_font (IwConnector *self, const gchar *s)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        clutter_text_set_font_name (CLUTTER_TEXT (self->priv->label), s);
}

/*****************************************************************************/

void iw_connector_get_font_color (IwConnector *self, ClutterColor *color)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        return clutter_text_get_color (CLUTTER_TEXT (self->priv->label), color);
}

/*****************************************************************************/

void iw_connector_set_font_color (IwConnector *self, const ClutterColor *c)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        clutter_text_set_color (CLUTTER_TEXT (self->priv->label), c);
}

/*****************************************************************************/

gboolean iw_connector_is_editable (IwConnector *self)
{
        g_return_val_if_fail (IW_IS_CONNECTOR (self), FALSE);
        return clutter_text_get_editable (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

void iw_connector_set_editable (IwConnector *self, gboolean b)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        clutter_text_set_editable (CLUTTER_TEXT (self->priv->label), b);
}

/*****************************************************************************/

void iw_connector_set_points (IwConnector *self, CPoint points[], size_t len)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        self->priv->points = points;
        self->priv->len = len;
        clutter_actor_queue_redraw (CLUTTER_ACTOR (self));
}
