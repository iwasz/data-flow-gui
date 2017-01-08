/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "CircularNode.h"
#include "clutter/iw_circular_node.h"

CircularNode::CircularNode ()
{
        self = iw_circular_node_new ();
        clutter_actor_set_reactive (self, TRUE);
        ClutterAction *dragAction = clutter_drag_action_new ();
        clutter_actor_add_action (self, dragAction);
}

/*****************************************************************************/

void CircularNode::init ()
{
        iw_circular_node_set_ports_no (IW_CIRCULAR_NODE (self), ports.size ());

        int i = 0;
        for (Port const &p : ports) {
                iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (self), i, p.angle);
                iw_circular_node_set_port_size (IW_CIRCULAR_NODE (self), i, p.size);
                ClutterColor c = p.color.toClutterColor ();
                iw_circular_node_set_port_color (IW_CIRCULAR_NODE (self), i, &c);
                ++i;
        }
}

/*****************************************************************************/

bool CircularNode::isFill () const { return iw_circular_node_is_fill (IW_CIRCULAR_NODE (self)); }

void CircularNode::setFill (bool value) { iw_circular_node_set_fill (IW_CIRCULAR_NODE (self), value); }

float CircularNode::getStrokeWidth () const { return iw_circular_node_get_stroke_width (IW_CIRCULAR_NODE (self)); }

void CircularNode::setStrokeWidth (float value) { iw_circular_node_set_stroke_width (IW_CIRCULAR_NODE (self), value); }

float CircularNode::getStrokeDash () const { return iw_circular_node_get_stroke_dash (IW_CIRCULAR_NODE (self)); }

void CircularNode::setStrokeDash (float value) { iw_circular_node_set_stroke_dash (IW_CIRCULAR_NODE (self), value); }

Color CircularNode::getStrokeColor () const { return Color (iw_circular_node_get_stroke_color (IW_CIRCULAR_NODE (self))); }

void CircularNode::setStrokeColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_circular_node_set_stroke_color (IW_CIRCULAR_NODE (self), &color);
}

Color CircularNode::getFillColor () const { return Color (iw_circular_node_get_fill_color (IW_CIRCULAR_NODE (self))); }

void CircularNode::setFillColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_circular_node_set_fill_color (IW_CIRCULAR_NODE (self), &color);
}
