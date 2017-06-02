/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "CircularNode.h"
#include "clutter/iw_circular_node.h"

#include "clutter/iw_abstract_node.h"

void NodeActor::init ()
{
        AbstractActor::init ();

        int inputProgramNumber = 0;
        int outputProgramNumber = 0;
        int viewNumber = 0;
        for (std::shared_ptr<Port> p : getPorts ()) {
                p->setNodeActor (this);

                if (p->isInput ()) {
                        p->setProgramNumber (inputProgramNumber++);
                        p->setViewNumber (viewNumber);
                }
                else {
                        p->setProgramNumber (outputProgramNumber++);
                        p->setViewNumber (viewNumber);
                }

                p->init ();
                ++viewNumber;
        }

//        iw_abstract_node_set_ports_no (IW_ABSTRACT_NODE (self), getPorts ().size ());

//        int portNumber = 0;
//        for (std::shared_ptr<Port> p : getPorts ()) {
//                iw_abstract_node_set_port_position (IW_ABSTRACT_NODE (self), portNumber, p->getPosition ().x, p->getPosition ().y);
//                iw_abstract_node_set_port_size (IW_ABSTRACT_NODE (self), portNumber, p->getSize ());
//                ClutterColor c = p->getColor ().toClutterColor ();
//                iw_abstract_node_set_port_color (IW_ABSTRACT_NODE (self), portNumber, &c);
//                iw_abstract_node_set_port_user_data (IW_ABSTRACT_NODE (self), portNumber, p.get ());
//                ++portNumber;
//        }
}

/*****************************************************************************/

CircularNode::CircularNode ()
{
        self = iw_circular_node_new ();
        clutter_actor_set_reactive (self, TRUE);
        setCppImplementation ();
}

/*****************************************************************************/

void CircularNode::init ()
{
        NodeActor::init ();
        iw_circular_node_set_ports_no (IW_CIRCULAR_NODE (self), getPorts ().size ());

        int portNumber = 0;
        for (std::shared_ptr<Port> p : getPorts ()) {
                iw_circular_node_set_port_position (IW_CIRCULAR_NODE (self), portNumber, p->getPosition ().x, p->getPosition ().y);
                iw_circular_node_set_port_size (IW_CIRCULAR_NODE (self), portNumber, p->getSize ());
                ClutterColor c = p->getColor ().toClutterColor ();
                iw_circular_node_set_port_color (IW_CIRCULAR_NODE (self), portNumber, &c);
                iw_circular_node_set_port_user_data (IW_CIRCULAR_NODE (self), portNumber, p.get ());
                ++portNumber;
        }
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

primitives::Color CircularNode::getStrokeColor () const { return primitives::Color (iw_circular_node_get_stroke_color (IW_CIRCULAR_NODE (self))); }

/*****************************************************************************/

void CircularNode::setStrokeColor (const primitives::Color &value)
{
        ClutterColor color = primitives::Color::toClutterColor (value);
        iw_circular_node_set_stroke_color (IW_CIRCULAR_NODE (self), &color);
}

/*****************************************************************************/

primitives::Color CircularNode::getFillColor () const { return primitives::Color (iw_circular_node_get_fill_color (IW_CIRCULAR_NODE (self))); }

/*****************************************************************************/

void CircularNode::setFillColor (const primitives::Color &value)
{
        ClutterColor color = primitives::Color::toClutterColor (value);
        iw_circular_node_set_fill_color (IW_CIRCULAR_NODE (self), &color);
}

/*****************************************************************************/

// primitives::Point CircularNode::getPortPosition (const Port *port) const
//{
//        primitives::Point p;
//        // TODO!!!
////        iw_circular_node_get_port_position (IW_CIRCULAR_NODE (self), p, &p.x, &p.y);
//        return p;
//}

/*****************************************************************************/

std::string CircularNode::getText () const { return iw_circular_node_get_text (IW_CIRCULAR_NODE (self)); }

/*****************************************************************************/

void CircularNode::setText (std::string const t) { iw_circular_node_set_text (IW_CIRCULAR_NODE (self), t.c_str ()); }

/*****************************************************************************/

std::string CircularNode::getFont () const { return iw_circular_node_get_font (IW_CIRCULAR_NODE (self)); }

/*****************************************************************************/

void CircularNode::setFont (std::string const t) { iw_circular_node_set_font (IW_CIRCULAR_NODE (self), t.c_str ()); }

/*****************************************************************************/

primitives::Color CircularNode::getFontColor () const
{
        ClutterColor c;
        iw_circular_node_get_font_color (IW_CIRCULAR_NODE (self), &c);
        return primitives::Color (&c);
}

/*****************************************************************************/

void CircularNode::setFontColor (const primitives::Color &value)
{
        ClutterColor color = primitives::Color::toClutterColor (value);
        iw_circular_node_set_font_color (IW_CIRCULAR_NODE (self), &color);
}

/*****************************************************************************/

bool CircularNode::isTextEditable () const { return iw_circular_node_is_editable (IW_CIRCULAR_NODE (self)); }

/*****************************************************************************/

void CircularNode::setTextEditable (bool b) { iw_circular_node_set_editable (IW_CIRCULAR_NODE (self), b); }

/*****************************************************************************/

// void CircularNode::onAllocate (primitives::Box const &)
//{
//}

/*****************************************************************************/

// extern "C" void circularNodeOnAllocate (void *circularNode, float x1, float y1, float x2, float y2)
//{
//        CircularNode *cn = static_cast<CircularNode *> (circularNode);
//        cn->onAllocate (primitives::Box (primitives::Point (x1, y1), primitives::Point (x2, y2)));
//}
