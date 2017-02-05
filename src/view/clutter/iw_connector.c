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

G_DEFINE_TYPE (IwConnector, iw_connector, IW_TYPE_ACTOR);
#define IW_CONNECTOR_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_CONNECTOR, IwConnectorPrivate))

struct _IwConnectorPrivate {
        gfloat ax, ay;
        gfloat bx, by;
        gfloat cx, cy;
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

        float ax = IW_CONNECTOR (actor)->priv->ax;
        float ay = IW_CONNECTOR (actor)->priv->ay;
        float bx = IW_CONNECTOR (actor)->priv->bx;
        float by = IW_CONNECTOR (actor)->priv->by;
        float cx = IW_CONNECTOR (actor)->priv->cx;
        float cy = IW_CONNECTOR (actor)->priv->cy;

//        ClutterActor *parent = clutter_actor_get_parent (actor);
//        clutter_actor_transform_stage_point (firstContainerActor, event->positionStageCoords.x, event->positionStageCoords.y, &event->positionParentCoords.x,
//                                             &event->positionParentCoords.y);

        float angle = atan ((ay - by) / (ax - bx));

        if (ax < bx && ay < by) {
                cogl_line (0, 0, width, height, fill, angle, lw);

                if (width < height) {
                        cogl_path_move_to (0, 0);
                        cogl_path_line_to (0, height / 2);
                        cogl_path_line_to (width, height / 2);
                        cogl_path_line_to (width, height);
                        cogl_path_stroke ();
                }
                else {
                        cogl_path_move_to (0, 0);
                        cogl_path_line_to (width / 2, 0);
                        cogl_path_line_to (width / 2, height);
                        cogl_path_line_to (width, height);
                        cogl_path_stroke ();
                }
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
}

/*****************************************************************************/

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

/*****************************************************************************/

void iw_connector_set_point_a (IwConnector *self, gfloat x, gfloat y)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        self->priv->ax = x;
        self->priv->ay = y;
        iw_connector_resize_accordingly (self);
}

/*****************************************************************************/

void iw_connector_get_point_a (IwConnector *self, gfloat *x, gfloat *y)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        *x = self->priv->ax;
        *y = self->priv->ay;
}

/*****************************************************************************/

void iw_connector_set_point_b (IwConnector *self, gfloat x, gfloat y)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        self->priv->bx = x;
        self->priv->by = y;
        iw_connector_resize_accordingly (self);
}

/*****************************************************************************/

void iw_connector_get_point_b (IwConnector *self, gfloat *x, gfloat *y)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        *x = self->priv->bx;
        *y = self->priv->by;
}

/*****************************************************************************/

void iw_connector_set_point_c (IwConnector *self, gfloat x, gfloat y)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        self->priv->cx = x;
        self->priv->cy = y;
        iw_connector_resize_accordingly (self);
}

/*****************************************************************************/

void iw_connector_get_point_c (IwConnector *self, gfloat *x, gfloat *y)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        *x = self->priv->cx;
        *y = self->priv->cy;
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
