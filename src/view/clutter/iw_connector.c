/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_connector.h"
#include "drawing_stuff.h"
#include <complex.h>
#include <math.h>
#include <memory.h>
#include <stdbool.h>

G_DEFINE_TYPE (IwConnector, iw_connector, IW_TYPE_ACTOR);
#define IW_CONNECTOR_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_CONNECTOR, IwConnectorPrivate))

struct _IwConnectorPrivate {
        CPoint *points;
        size_t len;
        ClutterActor *label;

        int textPivotSegmentNumber;
        float textPivotDistance;
        float textPivotSegmentAx, textPivotSegmentAy;
        float textPivotSegmentBx, textPivotSegmentBy;
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

        clutter_actor_get_allocation_box (actor, &allocation);

        cogl_path_new ();
        cogl_set_source_color4ub (color->red, color->green, color->blue, color->alpha);

        // float lw = iw_actor_get_stroke_width (IW_ACTOR (actor));

        CPoint *points = IW_CONNECTOR (actor)->priv->points;
        size_t len = IW_CONNECTOR (actor)->priv->len;

        for (int i = 0; i < len; ++i) {
                CPoint *p = points + i;
                cogl_path_line_to (p->x - allocation.x1, p->y - allocation.y1);
        }

        cogl_path_stroke ();

        // Arrow
        if (len > 1) {
                CPoint *p1 = &points[len - 2];
                CPoint *p2 = &points[len - 1];

                double complex c1 = (p1->x - p2->x) + (p1->y - p2->y) * I;
                double arg = carg (c1);

#if 0
                printf ("len = %d, p1 = %f, %f, p2 = %f, %f | c1 = [%f, %f]\n", len, p1->x, p1->y, p2->x, p2->y, creal (c1), cimag (c1));
                printf ("arg = %f\n", arg);
#endif

                float arrowArmLength = 20;
                float arrowArmAngle = M_PI / 15;
                CPoint a1, a2;
                a1.x = arrowArmLength * cos (arg + arrowArmAngle) + p2->x;
                a1.y = arrowArmLength * sin (arg + arrowArmAngle) + p2->y;
                a2.x = arrowArmLength * cos (arg - arrowArmAngle) + p2->x;
                a2.y = arrowArmLength * sin (arg - arrowArmAngle) + p2->y;

                cogl_path_line_to (a1.x - allocation.x1, a1.y - allocation.y1);
                cogl_path_line_to (a2.x - allocation.x1, a2.y - allocation.y1);
                cogl_path_line_to (p2->x - allocation.x1, p2->y - allocation.y1);
        }

        cogl_path_fill ();
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
        iw_connector_resize_accordingly (line);
        onTextChangedConnector (iw_actor_get_user_data (IW_ACTOR (line)), clutter_text_get_text (self));
}

/*****************************************************************************/

static void iw_connector_init (IwConnector *self)
{
        IwConnectorPrivate *priv = self->priv = IW_CONNECTOR_GET_PRIVATE (self);
        priv->points = NULL;
        priv->len = 0;
        priv->textPivotSegmentNumber = 0;
        priv->textPivotDistance = 0;

        priv->label = clutter_text_new ();
        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->label);
        clutter_text_set_font_name (CLUTTER_TEXT (priv->label), "18px");
        clutter_text_set_text (CLUTTER_TEXT (priv->label), "A");
        clutter_text_set_editable (CLUTTER_TEXT (priv->label), FALSE);
        clutter_text_set_selectable (CLUTTER_TEXT (priv->label), TRUE);
        clutter_text_set_single_line_mode (CLUTTER_TEXT (priv->label), TRUE);
        clutter_actor_set_reactive (priv->label, TRUE);
        g_signal_connect (priv->label, "text-changed", G_CALLBACK (on_text_changed), self);

#if 0
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (CLUTTER_ACTOR (self), &c);
        static ClutterColor c2 = { 0xff, 0x00, 0x88, 0x88 };
        clutter_actor_set_background_color (CLUTTER_ACTOR (self->priv->label), &c2);
#endif
}

/*****************************************************************************/

#if 1
static void iw_connector_resize_accordingly (IwConnector *self)
{
        gfloat strokeWidth = iw_actor_get_stroke_width (IW_ACTOR (self));
        float lw = 0; // strokeWidth;
        float ax = self->priv->textPivotSegmentAx;
        float ay = self->priv->textPivotSegmentAy;
        float bx = self->priv->textPivotSegmentBx;
        float by = self->priv->textPivotSegmentBy;

        ClutterActorBox allocation = {
                0,
        };
        clutter_actor_get_allocation_box (CLUTTER_ACTOR (self), &allocation);
        float offsetX = ax - allocation.x1;
        float offsetY = ay - allocation.y1;

        if (clutter_text_get_text (CLUTTER_TEXT (self->priv->label)) != NULL && ax != bx) {

                // double complex c1 = (ax - bx) + (ay - by) * I;
                double complex c1 = (bx - ax) + (by - ay) * I;
                double angle = carg (c1);

                //                float angle = atan ((ay - by) / (ax - bx));
                clutter_actor_set_rotation_angle (self->priv->label, CLUTTER_Z_AXIS, angle * 180 / M_PI);
                // printf ("%f, %f, %f, %f, %f\n", angle, ax, ay, bx, by);

                double c = cos (angle);
                double s = sin (angle);

                //                float tw = clutter_actor_get_width (CLUTTER_ACTOR (self->priv->label));
                //                float px = c * tw;
                //                float py = s * tw;

                //                float lh = strokeWidth;
                //                px += s * lh;
                //                py -= c * lh;

                //                float w = clutter_actor_get_width (CLUTTER_ACTOR (self)) - px;
                //                float h = clutter_actor_get_height (CLUTTER_ACTOR (self)) - py;

                clutter_actor_set_position (CLUTTER_ACTOR (self->priv->label), self->priv->textPivotDistance * c + offsetX,
                                            self->priv->textPivotDistance * s + offsetY);
        }
        else {
                float tw = clutter_actor_get_width (CLUTTER_ACTOR (self->priv->label));
                clutter_actor_set_position (CLUTTER_ACTOR (self->priv->label), -tw / 2.0, strokeWidth);
        }

        clutter_text_set_editable (CLUTTER_TEXT (self->priv->label), TRUE);
}
#endif

/*****************************************************************************/

void iw_connector_set_points (IwConnector *self, CPoint points[], size_t len)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));

        float minX = INFINITY, minY = INFINITY, maxX = -INFINITY, maxY = -INFINITY;
        float halfLength = 0;

        // Calculate length and bounding box
        for (int i = 0; i < len; ++i) {
                double px = points[i].x;
                double py = points[i].y;

                if (px > maxX) {
                        maxX = px;
                }

                if (px < minX) {
                        minX = px;
                }

                if (py > maxY) {
                        maxY = py;
                }

                if (py < minY) {
                        minY = py;
                }

                if (i > 0) {
                        halfLength += sqrt (pow (fabs (px - points[i - 1].x), 2) + pow (fabs (py - points[i - 1].y), 2));
                }
        }

        clutter_actor_set_position (CLUTTER_ACTOR (self), minX, minY);
        clutter_actor_set_size (CLUTTER_ACTOR (self), maxX - minX, maxY - minY);

        halfLength /= 2.0;

        // Calculate which segment has middlePoint (point which is equally far from both ends).
        float length = 0;

        for (int i = 0; i < len; ++i) {
                double px = points[i].x;
                double py = points[i].y;

                if (i > 0) {
                        float actualLength = sqrt (pow (fabs (px - points[i - 1].x), 2) + pow (fabs (py - points[i - 1].y), 2));
                        length += actualLength;

                        if (length >= halfLength) {
                                // Store information regarding the segment which has text-pivot point.
                                self->priv->textPivotSegmentNumber = i - 1;
                                self->priv->textPivotDistance = actualLength - length + halfLength;
                                self->priv->textPivotSegmentAx = points[i - 1].x;
                                self->priv->textPivotSegmentAy = points[i - 1].y;
                                self->priv->textPivotSegmentBx = px;
                                self->priv->textPivotSegmentBy = py;
                                break;
                        }
                }
        }

        //                printf ("%f, %f, %f, %f, segNo : %d\n", self->priv->textPivotSegmentAx, self->priv->textPivotSegmentAy,
        //                self->priv->textPivotSegmentBx,
        //                        self->priv->textPivotSegmentBy, self->priv->textPivotSegmentNumber);
        //                printf ("remaining : %f\n", self->priv->textPivotDistance);

        self->priv->points = points;
        self->priv->len = len;
        iw_connector_resize_accordingly (self);
        clutter_actor_queue_redraw (CLUTTER_ACTOR (self));
}

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
