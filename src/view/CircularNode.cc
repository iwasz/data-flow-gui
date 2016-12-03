/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "clutter/iw_circular_node.h"
#include "CircularNode.h"

CircularNode::CircularNode ()
{
        self = iw_circular_node_new ();
        clutter_actor_set_position (self, 100, 300);
        iw_circular_node_set_radius (IW_CIRCULAR_NODE (self), 75);
        ClutterColor actor_color = { 0, 150, 198, 201 };
        iw_circular_node_set_color (IW_CIRCULAR_NODE (self), &actor_color);

        clutter_actor_set_reactive (self, TRUE);

        ClutterAction *dragAction = clutter_drag_action_new ();
        clutter_actor_add_action (self, dragAction);
}

void CircularNode::init ()
{
        iw_circular_node_set_ports_no (IW_CIRCULAR_NODE (self), 3);
        iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (self), 0, G_PI - 0.5);
        iw_circular_node_set_port_size (IW_CIRCULAR_NODE (self), 0, 0.4);
        ClutterColor port_color = { 141, 141, 141, 255 };
        iw_circular_node_set_port_color (IW_CIRCULAR_NODE (self), 0, &port_color);

        iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (self), 1, G_PI + 0.5);
        iw_circular_node_set_port_size (IW_CIRCULAR_NODE (self), 1, 0.4);
        iw_circular_node_set_port_color (IW_CIRCULAR_NODE (self), 1, &port_color);

        iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (self), 2, 2 * G_PI);
        iw_circular_node_set_port_size (IW_CIRCULAR_NODE (self), 2, 0.4);
        ClutterColor port_color2 = { 209, 209, 209, 255 };
        iw_circular_node_set_port_color (IW_CIRCULAR_NODE (self), 2, &port_color2);
}

bool CircularNode::isFill () const
{

}

void CircularNode::setFill (bool value)
{

}

float CircularNode::getStrokeWidth () const
{

}

void CircularNode::setStrokeWidth (float value)
{

}

float CircularNode::getStrokeDash () const
{

}

void CircularNode::setStrokeDash (float value)
{

}

std::string CircularNode::getStrokeColor () const
{

}

void CircularNode::setStrokeColor (const std::string &value)
{

}

std::string CircularNode::getFillColor () const
{

}

void CircularNode::setFillColor (const std::string &value)
{

}
