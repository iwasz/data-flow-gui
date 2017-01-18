/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "CircularNode.h"
#include "clutter/iw_circular_node.h"

/*****************************************************************************/

class CircularNodeAnchorPositionProvider : public IAnchorPositionProvider {
public:
        CircularNodeAnchorPositionProvider (int i, IwCircularNode *self) : i (i), self (self) {}
        virtual ~CircularNodeAnchorPositionProvider () {}
        virtual Point getPosition () const
        {
                float px, py;
                iw_circular_node_get_port_absolute_position (self, i, &px, &py);
                return Point (px, py);
        }

private:
        int i;
        IwCircularNode *self;
};

/*****************************************************************************/

CircularNode::CircularNode ()
{
        self = iw_circular_node_new ();
        clutter_actor_set_reactive (self, TRUE);
        iw_circular_node_set_user_data (IW_CIRCULAR_NODE (self), this);
        setCppImplementation ();
}

/*****************************************************************************/

void CircularNode::init ()
{
        iw_circular_node_set_ports_no (IW_CIRCULAR_NODE (self), getPorts ().size ());

        int portNumber = 0;
        for (std::shared_ptr<Port> p : getPorts ()) {
                iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (self), portNumber, p->angle);
                iw_circular_node_set_port_size (IW_CIRCULAR_NODE (self), portNumber, p->size);
                ClutterColor c = p->color.toClutterColor ();
                iw_circular_node_set_port_color (IW_CIRCULAR_NODE (self), portNumber, &c);
                iw_circular_node_set_port_user_data (IW_CIRCULAR_NODE (self), portNumber, p.get ());
                p->anchor.setApProvider (std::make_shared<CircularNodeAnchorPositionProvider> (portNumber, IW_CIRCULAR_NODE (self)));
                ++portNumber;
        }

        glueInit ();
}

/*****************************************************************************/

bool CircularNode::isFill () const { return iw_circular_node_is_fill (IW_CIRCULAR_NODE (self)); }

/*****************************************************************************/

void CircularNode::setFill (bool value) { iw_circular_node_set_fill (IW_CIRCULAR_NODE (self), value); }

/*****************************************************************************/

float CircularNode::getStrokeWidth () const { return iw_circular_node_get_stroke_width (IW_CIRCULAR_NODE (self)); }

/*****************************************************************************/

void CircularNode::setStrokeWidth (float value) { iw_circular_node_set_stroke_width (IW_CIRCULAR_NODE (self), value); }

/*****************************************************************************/

float CircularNode::getStrokeDash () const { return iw_circular_node_get_stroke_dash (IW_CIRCULAR_NODE (self)); }

/*****************************************************************************/

void CircularNode::setStrokeDash (float value) { iw_circular_node_set_stroke_dash (IW_CIRCULAR_NODE (self), value); }

/*****************************************************************************/

Color CircularNode::getStrokeColor () const { return Color (iw_circular_node_get_stroke_color (IW_CIRCULAR_NODE (self))); }

/*****************************************************************************/

void CircularNode::setStrokeColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_circular_node_set_stroke_color (IW_CIRCULAR_NODE (self), &color);
}

/*****************************************************************************/

Color CircularNode::getFillColor () const { return Color (iw_circular_node_get_fill_color (IW_CIRCULAR_NODE (self))); }

/*****************************************************************************/

void CircularNode::setFillColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_circular_node_set_fill_color (IW_CIRCULAR_NODE (self), &color);
}

/*****************************************************************************/

void CircularNode::onAllocate (Box const &)
{
        int i = 0;
        for (std::shared_ptr<Port> p : getPorts ()) {
                float px = 0;
                float py = 0;
                iw_circular_node_get_port_absolute_position (IW_CIRCULAR_NODE (self), i, &px, &py);
                p->anchor.notifyMoveAnchor (Point (px, py));
                ++i;
        }
}

/*****************************************************************************/

extern "C" void circularNodeOnAllocate (void *circularNode, float x1, float y1, float x2, float y2)
{
        CircularNode *cn = static_cast<CircularNode *> (circularNode);
        cn->onAllocate (Box (x1, y1, x2, y2));
}
