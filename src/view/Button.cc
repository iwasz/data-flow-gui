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
        clutter_actor_set_position (self, 100, 300);

        iw_actor_set_user_data (IW_ACTOR (self), this);
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
