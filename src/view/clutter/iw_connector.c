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

/// Ray or line segment (not a line).
struct _Line {
        float ax, ay, bx, by;
        Direction direction;
};

typedef struct _Line Line;

struct _Point {
        float x, y;
};

typedef struct _Point Point;

Line lineNew (float ax, float ay, float bx, float by)
{
        Line l;
        l.ax = ax;
        l.ay = ay;
        l.bx = bx;
        l.by = by;
        l.direction = NONE;
        return l;
}

Line rayNew (float ax, float ay, Direction dir)
{
        Line l;
        l.ax = ax;
        l.ay = ay;

        switch (dir) {
        case NORTH:
                l.bx = ax;
                l.by = -INFINITY;
                break;

        case SOUTH:
                l.bx = ax;
                l.by = INFINITY;
                break;

        case EAST:
                l.bx = INFINITY;
                l.by = ay;
                break;

        case WEST:
                l.bx = -INFINITY;
                l.by = ay;
                break;

        case NONE:
        default:
                break;
        }

        l.direction = dir;
        return l;
}

float lineGetAx (Line const *l) { return l->ax; }
float lineGetAy (Line const *l) { return l->ay; }

float lineGetBx (Line const *l)
{
        return l->bx;

        //        if (l->direction == NONE) {
        //                return l->bx;
        //        }

        //        switch (l->direction) {
        //        case NORTH:
        //        case SOUTH:
        //                return l->ax;

        //        case EAST:
        //                return INFINITY;

        //        case WEST:
        //                return -INFINITY;

        //        case NONE:
        //        default:
        //                return NAN;
        //        }
}

float lineGetBy (Line const *l)
{
        return l->by;

        //        if (l->direction == NONE) {
        //                return l->by;
        //        }

        //        switch (l->direction) {
        //        case NORTH:
        //                return INFINITY;

        //        case SOUTH:
        //                return -INFINITY;

        //        case EAST:
        //        case WEST:
        //                return l->ay;

        //        case NONE:
        //        default:
        //                return NAN;
        //        }
}

/// Tells if Line is a ray.
bool isRay (Line const *l) { return l->direction != NONE; }

/// Returns if two rays facing one another overlays.
bool raysConnect (Line const *a, Line const *b, Point *pointOfConnection)
{
        // Consider only rays
        if (!isRay (a) || !isRay (b)) {
                return false;
        }

        // Only rays facing eachother will be taken into account.
        if (a->direction != getOppositeDirection (b->direction)) {
                return false;
        }

        printf ("%f, %f, %f, %f\n", a->ax, b->ax, a->ax, b->ax);

        // Only facing each other
        if ((a->direction == NORTH && a->ay < b->ay) || (a->direction == SOUTH && a->ay > b->ay) || (a->direction == EAST && a->ax > b->ax)
            || (a->direction == WEST && a->ax < b->ax)) {
                return false;
        }

        printf ("!");

        // If vertical
        if (a->direction == NORTH || a->direction == SOUTH) {
                pointOfConnection->x = a->ax;
                pointOfConnection->y = fabs (a->ay - b->ay) / 2.0;
                return (a->ax == b->ax);
        }
        else if (a->direction == WEST || a->direction == EAST) {
                pointOfConnection->x = fabs (a->ax - b->ax) / 2.0;
                pointOfConnection->y = a->ay;
                return (a->ay == b->ay);
        }

        return false;
}

/// Returns if two perpendicullar rays cross (at right angle).
bool raysCross (Line const *a, Line const *b, Point *pointOfCrossing)
{
        // Consider only rays
        if (!isRay (a) || !isRay (b)) {
                return false;
        }

        float aax = lineGetAx (a);
        float aay = lineGetAy (a);
        float abx = lineGetBx (a);
        float aby = lineGetBy (a);
        float bax = lineGetAx (b);
        float bay = lineGetAy (b);
        float bbx = lineGetBx (b);
        float bby = lineGetBy (b);

        // Normalised coordinates of horizontal ray. Point A is on the left, point B is on the right.
        float hax, hay, hbx, hby;
        // Normalised coordinates of vertical ray. Point A is on the top, point B is on the bottom.
        float vax, vay, vbx, vby;

        if (a->direction == NORTH || a->direction == SOUTH) {
                vax = aax;
                vay = fmin (aay, aby);
                vbx = aax;
                vby = fmax (aay, aby);
        }
        else {
                hax = fmin (aax, abx);
                hay = aay;
                hbx = fmax (aax, abx);
                hby = aay;
        }

        if (b->direction == NORTH || b->direction == SOUTH) {
                vax = bax;
                vay = fmin (bay, bby);
                vbx = bax;
                vby = fmax (bay, bby);
        }
        else {
                hax = fmin (bax, bbx);
                hay = bay;
                hbx = fmax (bax, bbx);
                hby = bay;
        }

        return (hay >= vay && hay <= vby) && (vax >= hax && vax <= hbx);
}

G_DEFINE_TYPE (IwConnector, iw_connector, IW_TYPE_ACTOR);
#define IW_CONNECTOR_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IW_TYPE_CONNECTOR, IwConnectorPrivate))

struct _IwConnectorPrivate {
        gfloat ax, ay; // Begin
        Direction aFacing;
        gfloat bx, by; // End
        Direction bFacing;
        ClutterActor *label;
};

static gboolean draw_line (ClutterCanvas *canvas, cairo_t *cr, int width, int height, gpointer *data);
static void iw_connector_resize_accordingly (IwConnector *self);
void onTextChangedConnector (void *lineConnector, const char *text);

/*****************************************************************************/

gfloat getX (ClutterActor *actor, int segment)
{
        ClutterActorBox allocation;
        clutter_actor_get_allocation_box (actor, &allocation);
        float ax = IW_CONNECTOR (actor)->priv->ax - allocation.x1;
        float ay = IW_CONNECTOR (actor)->priv->ay - allocation.y1;
        float bx = IW_CONNECTOR (actor)->priv->bx - allocation.x1;
        float by = IW_CONNECTOR (actor)->priv->by - allocation.y1;

        if (segment == 0) {
                switch (IW_CONNECTOR (actor)->priv->aFacing) {
                case EAST:
                        if (bx - ax > 2 * MIN_SEGMENT_LENGTH) {
                                return (bx - ax) / 2;
                        }
                        else {
                                return MIN_SEGMENT_LENGTH;
                        }
                case WEST:
                        if (ax - bx > 2 * MIN_SEGMENT_LENGTH) {
                                return (bx - ax) / 2;
                        }
                        else {
                                return -MIN_SEGMENT_LENGTH;
                        }

                case NORTH:
                case SOUTH:
                case NONE:
                default:
                        return 0;
                }
        }
        if (segment == 1) {
                switch (IW_CONNECTOR (actor)->priv->aFacing) {
                case NORTH:
                case SOUTH:
                        return -(ax - bx) / 2;

                case EAST:
                case WEST:
                case NONE:
                default:
                        return 0;
                }
        }

        if (segment == 2) {
                switch (IW_CONNECTOR (actor)->priv->aFacing) {
                case EAST:
                        if (bx - ax < 2 * MIN_SEGMENT_LENGTH) {
                                return (bx - ax) - 2 * MIN_SEGMENT_LENGTH;
                        }
                        else {
                                return 0;
                        }

                case WEST:
                        if (ax - bx < 2 * MIN_SEGMENT_LENGTH) {
                                return (bx - ax) + 2 * MIN_SEGMENT_LENGTH;
                        }
                        else {
                                return 0;
                        }

                case NORTH:
                case SOUTH:
                case NONE:
                default:
                        return 0;
                }
        }

        if (segment == 3) {
                switch (IW_CONNECTOR (actor)->priv->bFacing) {
                case NORTH:
                case SOUTH:
                        return (ax - bx) / 2;

                case EAST:
                case WEST:
                case NONE:
                default:
                        return 0;
                }
        }
        if (segment == 4) {
                switch (IW_CONNECTOR (actor)->priv->bFacing) {
                case EAST:
                        if (ax - bx > 2 * MIN_SEGMENT_LENGTH) {
                                return -(bx - ax) / 2;
                        }
                        else {
                                return MIN_SEGMENT_LENGTH;
                        }
                case WEST:
                        if (bx - ax > 2 * MIN_SEGMENT_LENGTH) {
                                return -(bx - ax) / 2;
                        }
                        else {
                                return -MIN_SEGMENT_LENGTH;
                        }
                case NORTH:
                case SOUTH:
                case NONE:
                default:
                        return 0;
                }
        }

        return 0;
}

/*****************************************************************************/

gfloat getY (ClutterActor *actor, int segment)
{
        ClutterActorBox allocation;
        clutter_actor_get_allocation_box (actor, &allocation);
        float ax = IW_CONNECTOR (actor)->priv->ax - allocation.x1;
        float ay = IW_CONNECTOR (actor)->priv->ay - allocation.y1;
        float bx = IW_CONNECTOR (actor)->priv->bx - allocation.x1;
        float by = IW_CONNECTOR (actor)->priv->by - allocation.y1;

        if (segment == 0) {
                switch (IW_CONNECTOR (actor)->priv->aFacing) {
                case NORTH:
                        if (ay - by > 2 * MIN_SEGMENT_LENGTH) {
                                return (by - ay) / 2;
                        }
                        else {
                                return -MIN_SEGMENT_LENGTH;
                        }

                case SOUTH:
                        if (by - ay > 2 * MIN_SEGMENT_LENGTH) {
                                return (by - ay) / 2;
                        }
                        else {
                                return MIN_SEGMENT_LENGTH;
                        }

                case EAST:
                case WEST:
                case NONE:
                default:
                        return 0;
                }
        }

        if (segment == 1) {
                switch (IW_CONNECTOR (actor)->priv->aFacing) {
                case EAST:
                case WEST:
                        return -(ay - by) / 2;

                case NORTH:
                case SOUTH:
                case NONE:
                default:
                        return 0;
                }
        }

        if (segment == 2) {
                switch (IW_CONNECTOR (actor)->priv->aFacing) {
                case SOUTH:
                        if (by - ay < 2 * MIN_SEGMENT_LENGTH) {
                                return (by - ay) - 2 * MIN_SEGMENT_LENGTH;
                        }
                        else {
                                return 0;
                        }

                case NORTH:
                        if (ay - by < 2 * MIN_SEGMENT_LENGTH) {
                                return (by - ay) + 2 * MIN_SEGMENT_LENGTH;
                        }
                        else {
                                return 0;
                        }

                case WEST:
                case EAST:
                case NONE:
                default:
                        return 0;
                }
        }

        if (segment == 3) {
                switch (IW_CONNECTOR (actor)->priv->bFacing) {
                case EAST:
                case WEST:
                        return (ay - by) / 2;

                case NORTH:
                case SOUTH:
                case NONE:
                default:
                        return 0;
                }
        }

        if (segment == 4) {
                switch (IW_CONNECTOR (actor)->priv->bFacing) {
                case NORTH:
                        if (by - ay > 2 * MIN_SEGMENT_LENGTH) {
                                return -(by - ay) / 2;
                        }
                        else {
                                return -MIN_SEGMENT_LENGTH;
                        }

                case SOUTH:
                        if (ay - by > 2 * MIN_SEGMENT_LENGTH) {
                                return -(by - ay) / 2;
                        }
                        else {
                                return MIN_SEGMENT_LENGTH;
                        }
                case EAST:
                case WEST:
                case NONE:
                default:
                        return 0;
                }
        }

        return 0;
}

/*****************************************************************************/

void addPoint (Point *pointsFromB, float bx, float by, int *pFBCnt)
{
        pointsFromB[*pFBCnt].x = bx;
        pointsFromB[(*pFBCnt)++].y = by;
}

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

        float ax = IW_CONNECTOR (actor)->priv->ax /*- allocation.x1*/;
        float ay = IW_CONNECTOR (actor)->priv->ay /*- allocation.y1*/;
        float bx = IW_CONNECTOR (actor)->priv->bx /*- allocation.x1*/;
        float by = IW_CONNECTOR (actor)->priv->by /*- allocation.y1*/;
        Direction aDir = IW_CONNECTOR (actor)->priv->aFacing;
        Direction bDir = IW_CONNECTOR (actor)->priv->bFacing;

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

        Line s0 = rayNew (ax, ay, aDir);
        Line s4 = rayNew (bx, by, bDir);

        // printf ("%f, %f, %f, %f\n", ax, ay, bx, by);
                printf ("%d, %d\n", aDir, bDir);

        // Todo decrease number of elements
        Point pointsFromA[10];
        Point pointsFromB[10];

        //        bzero (&pointsFromA, sizeof (pointsFromA) * sizeof (Point));
        //        bzero (&pointsFromB, sizeof (pointsFromB) * sizeof (Point));

        int pFACnt = 0;
        int pFBCnt = 0;

        Point p;
        if (raysCross (&s0, &s4, &p) || raysConnect (&s0, &s4, &p)) {
                addPoint (pointsFromA, p.x, p.y, &pFACnt);
                addPoint (pointsFromB, p.x, p.y, &pFBCnt);
                //                printf (".");
        }

        cogl_path_move_to (ax, ay);

        for (int i = 0; i < pFACnt; ++i) {
                cogl_path_line_to (pointsFromA[i].x, pointsFromA[i].y);
        }

        cogl_path_move_to (bx, by);

        for (int i = 0; i < pFBCnt; ++i) {
                cogl_path_line_to (pointsFromB[i].x, pointsFromB[i].y);
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
        priv->aFacing = NONE;
        priv->bFacing = NONE;

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

void iw_connector_set_a_facing (IwConnector *self, Direction d)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        self->priv->aFacing = d;
}

/*****************************************************************************/

Direction iw_connector_get_a_facing (IwConnector *self)
{
        g_return_val_if_fail (IW_IS_CONNECTOR (self), NONE);
        return self->priv->aFacing;
}

/*****************************************************************************/

void iw_connector_set_b_facing (IwConnector *self, Direction d)
{
        g_return_if_fail (IW_IS_CONNECTOR (self));
        self->priv->bFacing = d;
}

/*****************************************************************************/

Direction iw_connector_get_b_facing (IwConnector *self)
{
        g_return_val_if_fail (IW_IS_CONNECTOR (self), NONE);
        return self->priv->bFacing;
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
