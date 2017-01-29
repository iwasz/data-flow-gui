/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_button.h"
#include "iw_circle.h"
#include <math.h>

void buttonOnAllocate (void *ptr, float x1, float y1, float x2, float y2);
void buttonOnPress (void *ptr);
void buttonOnRelease (void *ptr);
static gboolean draw_rectangle (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);
static void on_actor_resize (ClutterActor *actor, const ClutterActorBox *allocation, ClutterAllocationFlags flags, gpointer user_data);

G_DEFINE_TYPE (IwButton, iw_button, IW_TYPE_ACTOR);
#define IW_BUTTON_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_BUTTON, IwButtonPrivate))

/* private structure - should only be accessed through the public API;
 * this is used to store member variables whose properties
 * need to be accessible from the implementation; for example, if we
 * intend to create wrapper functions which modify properties on the
 * actors composing an object, we should keep a reference to the actors
 * here
 *
 * this is also the place where other state variables go:
 * for example, you might record the current state of the button
 * (toggled on or off) or a background image
 */
struct _IwButtonPrivate {
        ClutterActor *label;
        ClutterActor *port;
        gboolean mouseOver;
};

/*****************************************************************************/

static void iw_button_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags)
{
        IwButtonPrivate *priv = IW_BUTTON (actor)->priv;
        ClutterActorBox child_box = {
                0,
        };

        /* set the allocation for the whole button */
        //        CLUTTER_ACTOR_CLASS (iw_button_parent_class)->allocate (actor, box, flags);
        clutter_actor_set_allocation (actor, box, flags);

        float w = clutter_actor_box_get_width (box);
        float h = clutter_actor_box_get_height (box);
        float tw = clutter_actor_get_width (priv->label);
        float th = clutter_actor_get_height (priv->label);
        float portR = clutter_actor_get_width (priv->port);

        child_box.x1 = (w - tw) / 2;
        child_box.y1 = (h - th) / 2;
        child_box.x2 = child_box.x1 + tw;
        child_box.y2 = child_box.y1 + th;
        clutter_actor_allocate (priv->label, &child_box, flags);

        child_box.x1 = w - portR / 2;
        child_box.y1 = (h - portR) / 2;
        child_box.x2 = child_box.x1 + portR;
        child_box.y2 = child_box.y1 + portR;
        clutter_actor_allocate (priv->port, &child_box, flags);

        buttonOnAllocate (iw_actor_get_user_data (IW_ACTOR (actor)), child_box.x1, child_box.y1, child_box.x2, child_box.y2);
}

/*****************************************************************************/

gboolean on_button_button_press (ClutterActor *actor, ClutterEvent *ev, gpointer data)
{
        buttonOnPress (iw_actor_get_user_data (IW_ACTOR (actor)));
        return FALSE;
}

/*****************************************************************************/

gboolean on_button_button_release (ClutterActor *actor, ClutterEvent *ev, gpointer data)
{
        buttonOnRelease (iw_actor_get_user_data (IW_ACTOR (actor)));
        return FALSE;
}

/*****************************************************************************/

void on_button_enter (ClutterActor *actor, ClutterEvent *ev, gpointer data)
{
        IwButtonPrivate *priv = IW_BUTTON (actor)->priv;
        priv->mouseOver = TRUE;
        clutter_content_invalidate (iw_actor_get_canvas (IW_ACTOR (actor)));
}

/*****************************************************************************/

void on_button_leave (ClutterActor *actor, ClutterEvent *ev, gpointer data)
{
        IwButtonPrivate *priv = IW_BUTTON (actor)->priv;
        priv->mouseOver = FALSE;
        clutter_content_invalidate (iw_actor_get_canvas (IW_ACTOR (actor)));
}

/*****************************************************************************/

static void iw_button_class_init (IwButtonClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);
        actor_class->allocate = iw_button_allocate;

        g_type_class_add_private (klass, sizeof (IwButtonPrivate));
}

/*****************************************************************************/

static void iw_button_init (IwButton *self)
{
        IwButtonPrivate *priv;
        ClutterLayoutManager *layout;

        priv = self->priv = IW_BUTTON_GET_PRIVATE (self);
        clutter_actor_set_reactive (CLUTTER_ACTOR (self), TRUE);

        priv->label = clutter_text_new ();
        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->label);
        clutter_text_set_font_name (CLUTTER_TEXT (priv->label), "18px");
        clutter_text_set_editable (CLUTTER_TEXT (priv->label), FALSE);
        clutter_text_set_selectable (CLUTTER_TEXT (priv->label), TRUE);
        clutter_text_set_single_line_mode (CLUTTER_TEXT (priv->label), TRUE);

        self->priv->port = iw_circle_new ();
        iw_actor_set_fill (IW_ACTOR (self->priv->port), TRUE);
        iw_actor_set_stroke_width (IW_ACTOR (self->priv->port), 0);
        clutter_actor_add_child (CLUTTER_ACTOR (self), self->priv->port);
        clutter_actor_set_reactive (self->priv->port, TRUE);
        clutter_actor_set_size (self->priv->port, 20, 20);

        g_signal_connect (CLUTTER_ACTOR (self), "button-press-event", G_CALLBACK (on_button_button_press), NULL);
        g_signal_connect (CLUTTER_ACTOR (self), "button-release-event", G_CALLBACK (on_button_button_release), NULL);
        g_signal_connect (CLUTTER_ACTOR (self), "enter-event", G_CALLBACK (on_button_enter), NULL);
        g_signal_connect (CLUTTER_ACTOR (self), "leave-event", G_CALLBACK (on_button_leave), NULL);

        ClutterContent *canvas = iw_actor_get_canvas (IW_ACTOR (self));
        g_signal_connect (canvas, "draw", G_CALLBACK (draw_rectangle), self);
        clutter_content_invalidate (canvas);
}

/*****************************************************************************/

static gboolean draw_rectangle (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data)
{
        IwButton *self = (IwButton *)data;

        cairo_save (cr);

        /*
         * clear the contents of the canvas, to avoid painting
         * over the previous frame
         */
        cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
        cairo_paint (cr);
        cairo_restore (cr);
        cairo_set_operator (cr, CAIRO_OPERATOR_OVER);

        gfloat strokeWidth = iw_actor_get_stroke_width (IW_ACTOR (self));
        gfloat strokeDash = iw_actor_get_stroke_dash (IW_ACTOR (self));
        ClutterColor *strokeColor = iw_actor_get_stroke_color (IW_ACTOR (self));
        ClutterColor *fillColor = iw_actor_get_fill_color (IW_ACTOR (self));
        gboolean isFill = iw_actor_is_fill (IW_ACTOR (self));

        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_width (cr, strokeWidth);

        if (strokeDash > 0) {
                double dashed1 = strokeDash;
                cairo_set_dash (cr, &dashed1, 1, 0);
        }

        float mr = strokeWidth / 2.0 + 1;

        width -= mr;
        height -= mr + 1;

        double x = mr, y = mr, aspect = 1.0, corner_radius = 10.0;
        double radius = corner_radius / aspect;
        double degrees = M_PI / 180.0;

        cairo_new_sub_path (cr);
        cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
        cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
        cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
        cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
        cairo_close_path (cr);

        if (strokeWidth > 0) {
                clutter_cairo_set_source_color (cr, strokeColor);
                cairo_stroke_preserve (cr);
        }

        if (isFill) {
                if (self->priv->mouseOver) {
                        ClutterColor newColor;
                        clutter_color_lighten (fillColor, &newColor);
                        clutter_cairo_set_source_color (cr, &newColor);
                }
                else {
                        clutter_cairo_set_source_color (cr, fillColor);
                }

                cairo_fill (cr);
        }

        return TRUE;
}

/*****************************************************************************/

const gchar *iw_button_get_font (IwButton *self)
{
        g_return_val_if_fail (IW_IS_BUTTON (self), NULL);
        return clutter_text_get_font_name (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

void iw_button_set_font (IwButton *self, const gchar *s)
{
        g_return_if_fail (IW_IS_BUTTON (self));
        clutter_text_set_font_name (CLUTTER_TEXT (self->priv->label), s);
}

/*****************************************************************************/

void iw_button_set_font_color (IwButton *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_BUTTON (self));
        clutter_text_set_color (CLUTTER_TEXT (self->priv->label), color);
}

/*****************************************************************************/

void iw_button_get_font_color (IwButton *self, ClutterColor *color)
{
        g_return_if_fail (IW_IS_BUTTON (self));
        return clutter_text_get_color (CLUTTER_TEXT (self->priv->label), color);
}

/*****************************************************************************/

void iw_button_set_text (IwButton *self, const gchar *text)
{
        g_return_if_fail (IW_IS_BUTTON (self));
        clutter_text_set_text (CLUTTER_TEXT (self->priv->label), text);
}

/*****************************************************************************/

const gchar *iw_button_get_text (IwButton *self)
{
        g_return_val_if_fail (IW_IS_BUTTON (self), NULL);
        return clutter_text_get_text (CLUTTER_TEXT (self->priv->label));
}

/*****************************************************************************/

ClutterActor *iw_button_new (void) { return g_object_new (IW_TYPE_BUTTON, NULL); }

/*****************************************************************************/

void iw_button_set_port_color (IwButton *self, const ClutterColor *color)
{
        g_return_if_fail (IW_IS_BUTTON (self));
        iw_actor_set_fill_color (IW_ACTOR (self->priv->port), color);
}

/*****************************************************************************/

void iw_button_set_port_size (IwButton *self, float s)
{
        g_return_if_fail (IW_IS_BUTTON (self));
        clutter_actor_set_size (CLUTTER_ACTOR (self->priv->port), s, s);
}

/*****************************************************************************/

void iw_button_set_port_user_data (IwButton *self, void *p)
{
        g_return_if_fail (IW_IS_BUTTON (self));
        g_object_set_data (G_OBJECT (self->priv->port), CPP_IMPLEMENTATION_KEY, p);
}

/*****************************************************************************/

void *iw_button_node_get_port_user_data (IwButton *self)
{
        g_return_val_if_fail (IW_IS_BUTTON (self), NULL);
        return g_object_get_data (G_OBJECT (self->priv->port), CPP_IMPLEMENTATION_KEY);
}

/*****************************************************************************/

void iw_button_get_port_position (IwButton *self, float *x, float *y)
{
        g_return_if_fail (IW_IS_BUTTON (self));
        float px, py;
        ClutterActor *port = self->priv->port;
        clutter_actor_get_position (port, &px, &py);

        px += clutter_actor_get_width (port) / 2.0;
        py += clutter_actor_get_height (port) / 2.0;

        float ax, ay;
        clutter_actor_get_position (CLUTTER_ACTOR (self), &ax, &ay);

        *x = px + ax;
        *y = py + ay;
}
