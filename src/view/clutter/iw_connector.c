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

/// TODO if not used, remove and change names from Line to Ray.
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

bool isVertical (Line const *a) { return a->direction == NORTH || a->direction == SOUTH; }
bool isHorizontal (Line const *a) { return a->direction == WEST || a->direction == EAST; }

bool arePerpendicular (Line const *a, Line const *b) { return (isVertical (a) && isHorizontal (b)) || (isHorizontal (a) && isVertical (b)); }

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

        //        printf ("%f, %f, %f, %f\n", a->ax, b->ax, a->ax, b->ax);

        // Only facing each other
        if ((a->direction == NORTH && a->ay < b->ay) || (a->direction == SOUTH && a->ay > b->ay) || (a->direction == EAST && a->ax > b->ax)
            || (a->direction == WEST && a->ax < b->ax)) {
                return false;
        }

        // If vertical
        if (a->direction == NORTH || a->direction == SOUTH) {
                pointOfConnection->x = a->ax;
                pointOfConnection->y = fabs (a->ay - b->ay) / 2.0;
                return ((int)a->ax == (int)b->ax);
        }
        else if (a->direction == WEST || a->direction == EAST) {
                pointOfConnection->x = fabs (a->ax - b->ax) / 2.0;
                pointOfConnection->y = a->ay;
                return ((int)a->ay == (int)b->ay);
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

        if (!arePerpendicular (a, b)) {
                return false;
        }

        float aax = a->ax; /* lineGetAx (a); */
        float aay = a->ay; /* lineGetAy (a); */
        float abx = a->bx; /* lineGetBx (a); */
        float aby = a->by; /* lineGetBy (a); */
        float bax = b->ax; /* lineGetAx (b); */
        float bay = b->ay; /* lineGetAy (b); */
        float bbx = b->bx; /* lineGetBx (b); */
        float bby = b->by; /* lineGetBy (b); */

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

        pointOfCrossing->x = vax;
        pointOfCrossing->y = hay;
        return (hay >= vay && hay <= vby) && (vax >= hax && vax <= hbx);
}

/*****************************************************************************/

void addPoint (Point *pointsFromB, float bx, float by, int *pFBCnt)
{
        pointsFromB[*pFBCnt].x = bx;
        pointsFromB[(*pFBCnt)++].y = by;
}

/**
 * Move point "point" according direction dir (always horizontally or vertically)
 * by length.
 */
Point advance (Point const *point, Direction dir, float length)
{
        Point p = *point;

        switch (dir) {
        case NORTH:
                p.y -= length;
                break;

        case SOUTH:
                p.y += length;
                break;

        case EAST:
                p.x += length;
                break;

        case WEST:
                p.x -= length;
                break;

        case NONE:
        default:
                break;
        }

        return p;
}

/**
 * Distance between two points a and b, but according to direction dir, so
 * if dir is N or S it returns dinstance between Y coordinates, and when dir
 * is E or W, between X coordinates.
 */
float distance (Point const *a, Point const *b, Direction dir)
{
        if (dir == NORTH || dir == SOUTH) {
                return fabs (a->y - b->y);
        }
        else if (dir == EAST || dir == WEST) {
                return fabs (a->x - b->x);
        }

        return 0;
}

/*****************************************************************************/

Line rayPerpendicular (Line const *perpendicularTo, Point const *towardsPoint, Point const *startPoint)
{
        Direction ld;

        if (isVertical (perpendicularTo)) {
                ld = (towardsPoint->x > perpendicularTo->ax) ? (EAST) : (WEST);
                return rayNew (startPoint->x, startPoint->y, ld);
        }
        else {
                ld = (towardsPoint->y > perpendicularTo->ay) ? (SOUTH) : (NORTH);
                return rayNew (startPoint->x, startPoint->y, ld);
        }
}

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

        float ax = IW_CONNECTOR (actor)->priv->ax - allocation.x1;
        float ay = IW_CONNECTOR (actor)->priv->ay - allocation.y1;
        float bx = IW_CONNECTOR (actor)->priv->bx - allocation.x1;
        float by = IW_CONNECTOR (actor)->priv->by - allocation.y1;
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

        Point a = { ax, ay };
        Point b = { bx, by };
        Line s0 = rayNew (ax, ay, aDir);
        Line s1;
        Line s2;
        Line s3;
        Line s4;
        Line s5 = rayNew (bx, by, bDir);

        // printf ("%f, %f, %f, %f\n", ax, ay, bx, by);
        printf ("%d, %d\n", aDir, bDir);

        // Todo decrease number of elements
        Point pointsFromA[10];
        Point pointsFromB[10];

        int pFACnt = 0;
        int pFBCnt = 0;

        // Step 1. Draw 2 rays from both points (a and b) in correct directions. Check if they corss or connec
        Point p;
        if (raysCross (&s0, &s5, &p) || raysConnect (&s0, &s5, &p)) {
                addPoint (pointsFromA, p.x, p.y, &pFACnt);
                addPoint (pointsFromB, p.x, p.y, &pFBCnt);
        }

        // Step 2.0 Compute segments s1 and s4 if s0 and s5 did not cross.
        else {
                // Ray s1
                float d = distance (&a, &b, s0.direction);
                p = advance (&a, s0.direction, MIN_SEGMENT_LENGTH);

                // Compare distance between head and tail before and after the advance.
                if (distance (&p, &b, s0.direction) < d) { // If distance decreased
                        // Make right turn in half the way between a and b.
                        p = advance (&a, s0.direction, d / 2);
                }
                // ELSE (distance increased or stayed the same) Make right turn in point p (MIN_SEGMENT_LENGTH distance from a).

                addPoint (pointsFromA, p.x, p.y, &pFACnt);
                s1 = rayPerpendicular (&s0 /*Perpendicular to*/, &b /*Towards point*/, &p /*Starting at point*/);

                // Ray s4
                d = distance (&b, &a, s5.direction);
                p = advance (&b, s5.direction, MIN_SEGMENT_LENGTH);

                // Compare distance between head and tail before and after the advance.
                if (distance (&p, &a, s5.direction) < d) { // If distance decreased
                        // Make right turn in half the way between a and b.
                        p = advance (&b, s5.direction, d / 2);
                }
                // ELSE (distance increased or stayed the same) Make right turn in point p (MIN_SEGMENT_LENGTH distance from a).

                addPoint (pointsFromB, p.x, p.y, &pFBCnt);
                s4 = rayPerpendicular (&s5 /*Perpendicular to*/, &a /*Towards point*/, &p /*Starting at point*/);

                // Step 2.1
                if (raysCross (&s1, &s4, &p) || raysConnect (&s1, &s4, &p)) {
                        addPoint (pointsFromA, p.x, p.y, &pFACnt);
                        addPoint (pointsFromB, p.x, p.y, &pFBCnt);
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
                                p = advance (&a, s1.direction, d / 2);
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
                                p = advance (&b, s4.direction, d / 2);
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
