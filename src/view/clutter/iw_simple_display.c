/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "iw_simple_display.h"
#include "iw_circle.h"
#include <cogl-pango/cogl-pango.h>
#include <math.h>

G_DEFINE_TYPE (IwSimpleDisplay, iw_simple_display, IW_TYPE_ABSTRACT_NODE);

#define IW_SIMPLE_DISPLAY_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_SIMPLE_DISPLAY, IwSimpleDisplayPrivate))

struct _IwSimpleDisplayPrivate {
        ClutterActor *label;
        ClutterActor *port;
};

/*****************************************************************************/

static void iw_simple_display_paint (ClutterActor *actor)
{
        //        ClutterActorBox allocation = {
        //                0,
        //        };
        //        gfloat width, height;

        //        clutter_actor_get_allocation_box (actor, &allocation);
        //        clutter_actor_box_get_size (&allocation, &width, &height);

        //        cogl_path_new ();
        //        cogl_path_ellipse (width / 2.0, height / 2.0, width / 2.0, height / 2.0);

        //        gfloat strokeWidth = iw_actor_get_stroke_width (IW_ACTOR (actor));
        //        //        gfloat strokeDash = iw_actor_get_stroke_dash (IW_ACTOR (actor));
        //        ClutterColor *strokeColor = iw_actor_get_stroke_color (IW_ACTOR (actor));
        //        ClutterColor *fillColor = iw_actor_get_fill_color (IW_ACTOR (actor));
        //        gboolean isFill = iw_actor_is_fill (IW_ACTOR (actor));

        //        if (isFill) {
        //                cogl_set_source_color4ub (fillColor->red, fillColor->green, fillColor->blue, fillColor->alpha);
        //                cogl_path_fill_preserve ();
        //        }

        //        if (strokeWidth > 0) {
        //                cogl_set_source_color4ub (strokeColor->red, strokeColor->green, strokeColor->blue, strokeColor->alpha);
        //                cogl_path_stroke ();
        //        }

        //        for (ClutterActor *iter = clutter_actor_get_first_child (actor); iter != NULL; iter = clutter_actor_get_next_sibling (iter)) {
        //                clutter_actor_paint (iter);
        //        }
        PangoLayout *layout;
        guint8 real_opacity;

        CoglColor color;
        //        ClutterText *text = CLUTTER_TEXT (actor);
        ClutterColor text_color = { 0, 0, 0, 0xff };

        IwSimpleDisplayPrivate *priv = IW_SIMPLE_DISPLAY (actor)->priv;

        /* Get the PangoLayout that the Text actor is going to paint */
        layout = clutter_text_get_layout (CLUTTER_TEXT (priv->label));

        /* Get the color of the text, to extract the alpha component */
        clutter_text_get_color (CLUTTER_TEXT (priv->label), &text_color);

        /* Composite the opacity so that the shadow is correctly blended */
        real_opacity = clutter_actor_get_paint_opacity (actor) * text_color.alpha / 255;

        /* Create a #ccc color and premultiply it */
        cogl_color_init_from_4ub (&color, 0xcc, 0xcc, 0xcc, real_opacity);
        cogl_color_premultiply (&color);

        /* Finally, render the Text layout at a given offset using the color */
        cogl_pango_render_layout (layout, 0, 0, &text_color, 0);
}

/*****************************************************************************/

static void iw_simple_display_pick (ClutterActor *actor, const ClutterColor *pick_color)
{
        if (!clutter_actor_should_pick_paint (actor)) {
                return;
        }

        ClutterActorBox allocation = {
                0,
        };
        gfloat width, height;

        clutter_actor_get_allocation_box (actor, &allocation);
        clutter_actor_box_get_size (&allocation, &width, &height);

        cogl_path_new ();
        cogl_set_source_color4ub (pick_color->red, pick_color->green, pick_color->blue, pick_color->alpha);
        cogl_path_ellipse (width / 2.0, height / 2.0, width / 2.0, height / 2.0);
        cogl_path_fill ();

        for (ClutterActor *iter = clutter_actor_get_first_child (actor); iter != NULL; iter = clutter_actor_get_next_sibling (iter)) {
                clutter_actor_paint (iter);
        }
}

/*****************************************************************************/

static void iw_simple_display_class_init (IwSimpleDisplayClass *klass)
{
        ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);

        //        actor_class->pick = iw_simple_display_pick;
        //        actor_class->paint = iw_simple_display_paint;

        g_type_class_add_private (klass, sizeof (IwSimpleDisplayPrivate));
}

/*****************************************************************************/

static void iw_simple_display_init (IwSimpleDisplay *self)
{
        clutter_actor_set_reactive (CLUTTER_ACTOR (self), TRUE);

        IwSimpleDisplayPrivate *priv = self->priv = IW_SIMPLE_DISPLAY_GET_PRIVATE (self);
        priv->label = clutter_text_new ();
        clutter_actor_add_child (CLUTTER_ACTOR (self), priv->label);
        clutter_text_set_font_name (CLUTTER_TEXT (priv->label), "Terminus Regular 12");
        clutter_text_set_editable (CLUTTER_TEXT (priv->label), FALSE);
        clutter_text_set_text (CLUTTER_TEXT (priv->label), "123");
        clutter_text_set_selectable (CLUTTER_TEXT (priv->label), TRUE);
        clutter_text_set_single_line_mode (CLUTTER_TEXT (priv->label), TRUE);

        //        self->priv->port = iw_circle_new ();
        //        iw_actor_set_fill (IW_ACTOR (self->priv->port), TRUE);
        //        iw_actor_set_stroke_width (IW_ACTOR (self->priv->port), 0);
        //        clutter_actor_add_child (CLUTTER_ACTOR (self), self->priv->port);
        //        clutter_actor_set_reactive (self->priv->port, TRUE);
        //        clutter_actor_set_size (self->priv->port, 20, 20);
}

/*****************************************************************************/

ClutterActor *iw_simple_display_new (void) { return g_object_new (IW_TYPE_SIMPLE_DISPLAY, NULL); }

/*****************************************************************************/

void iw_simple_display_set_text (IwSimpleDisplay *d, const char *text)
{
        g_return_if_fail (IW_IS_SIMPLE_DISPLAY (d));
        clutter_text_set_text (CLUTTER_TEXT (d->priv->label), text);
}
