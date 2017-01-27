/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Button.h"
#include "clutter/iw_button.h"
#include <iostream>

Button::Button ()
{
        self = cb_button_new ();
        clutter_actor_set_reactive (self, TRUE);
        // iw_circular_node_set_user_data (IW_CIRCULAR_NODE (self), this);
        cb_button_set_text (CB_BUTTON (self), "Hello world");
        clutter_actor_set_position (self, 100, 300);
        static ClutterColor c = { 0xff, 0x00, 0x00, 0x88 };
        clutter_actor_set_background_color (self, &c);

        cb_button_set_user_data (CB_BUTTON (self), this);
        setCppImplementation ();
}

/*****************************************************************************/

void Button::init ()
{
        //        iw_circular_node_set_ports_no (IW_CIRCULAR_NODE (self), getPorts ().size ());

        //        int portNumber = 0;
        //        for (std::shared_ptr<Port> p : getPorts ()) {
        //                iw_circular_node_set_port_angle (IW_CIRCULAR_NODE (self), portNumber, p->angle);
        //                iw_circular_node_set_port_size (IW_CIRCULAR_NODE (self), portNumber, p->size);
        //                ClutterColor c = p->color.toClutterColor ();
        //                iw_circular_node_set_port_color (IW_CIRCULAR_NODE (self), portNumber, &c);
        //                iw_circular_node_set_port_user_data (IW_CIRCULAR_NODE (self), portNumber, p.get ());
        //                p->anchor.setApProvider (std::make_shared<ButtonAnchorPositionProvider> (portNumber, this));
        //                ++portNumber;
        //        }

        //        glueInit ();
}

/*****************************************************************************/

bool Button::isFill () const { /*return iw_circular_node_is_fill (IW_CIRCULAR_NODE (self));*/}

/*****************************************************************************/

void Button::setFill (bool value) { /*iw_circular_node_set_fill (IW_CIRCULAR_NODE (self), value);*/}

/*****************************************************************************/

float Button::getStrokeWidth () const { /*return iw_circular_node_get_stroke_width (IW_CIRCULAR_NODE (self));*/}

/*****************************************************************************/

void Button::setStrokeWidth (float value) { /*iw_circular_node_set_stroke_width (IW_CIRCULAR_NODE (self), value);*/}

/*****************************************************************************/

float Button::getStrokeDash () const { /*return iw_circular_node_get_stroke_dash (IW_CIRCULAR_NODE (self));*/}

/*****************************************************************************/

void Button::setStrokeDash (float value) { /*iw_circular_node_set_stroke_dash (IW_CIRCULAR_NODE (self), value);*/}

/*****************************************************************************/

Color Button::getStrokeColor () const { /*return Color (iw_circular_node_get_stroke_color (IW_CIRCULAR_NODE (self)));*/}

/*****************************************************************************/

void Button::setStrokeColor (const Color &value)
{
        //        ClutterColor color = Color::toClutterColor (value);
        //        iw_circular_node_set_stroke_color (IW_CIRCULAR_NODE (self), &color);
}

/*****************************************************************************/

Color Button::getFillColor () const { /*return Color (iw_circular_node_get_fill_color (IW_CIRCULAR_NODE (self)));*/}

/*****************************************************************************/

void Button::setFillColor (const Color &value)
{
        //        ClutterColor color = Color::toClutterColor (value);
        //        iw_circular_node_set_fill_color (IW_CIRCULAR_NODE (self), &color);
}

/*****************************************************************************/

Point Button::getPortPosition (int i) const
{
        //        Point p;
        //        iw_circular_node_get_port_position (IW_CIRCULAR_NODE (self), i, &p.x, &p.y);
        //        return p;
}

/*****************************************************************************/

void Button::onAllocate (Box const &)
{
        int i = 0;
        for (std::shared_ptr<Port> p : getPorts ()) {
                p->anchor.notifyMoveAnchor (convertToScaleLayer (getPortPosition (i)));
                ++i;
        }
}

/*****************************************************************************/

void Button::onClick () { std::cerr << "Clicked : " << this << std::endl; }

/*###########################################################################*/

extern "C" void buttonOnAllocate (void *ptr, float x1, float y1, float x2, float y2)
{
        Button *cn = static_cast<Button *> (ptr);
        cn->onAllocate (Box (Point (x1, y1), Point (x2, y2)));
}

/*****************************************************************************/

extern "C" void buttonOnClick (void *ptr)
{
        Button *cn = static_cast<Button *> (ptr);
        cn->onClick ();
}
