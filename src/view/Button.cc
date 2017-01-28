/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Button.h"
#include "clutter/iw_button.h"
#include <core/CommonNodes.h>
#include <iostream>

struct Button::Impl {
        flow::Copy *copy;
        flow::Arc arc;
};

/*****************************************************************************/

Button::Button ()
{
        impl = new Impl;
        self = cb_button_new ();
        clutter_actor_set_reactive (self, TRUE);
        iw_actor_set_user_data (IW_ACTOR (self), this);
        setCppImplementation ();
}

/*****************************************************************************/

Button::~Button () { delete impl; }

/*****************************************************************************/

void Button::setNode (std::shared_ptr<flow::INode> n)
{
        AbstractNodeView::setNode (n);
        impl->copy = dynamic_cast<flow::Copy *> (n.get ());

        if (!impl->copy) {
                throw Core::Exception ("Button::setNode : only flow::Copy allowed here.");
        }

        impl->copy->setInput (0, &impl->arc);
}

/*****************************************************************************/

void Button::init ()
{
        if (!getPorts ().empty ()) {
                Port *p = getPorts ()[0].get ();
                cb_button_set_port_size (CB_BUTTON (self), p->size);
                ClutterColor c = p->color.toClutterColor ();
                cb_button_set_port_color (CB_BUTTON (self), &c);
                cb_button_set_port_user_data (CB_BUTTON (self), p);
                p->anchor.setApProvider (std::make_shared<NodeAnchorPositionProvider> (0, this));
        }

        glueInit ();
}

/*****************************************************************************/

Point Button::getPortPosition (int i) const
{
        Point p;
        cb_button_get_port_position (CB_BUTTON (self), &p.x, &p.y);
        return p;
}

/*****************************************************************************/

void Button::onAllocate (Box const &)
{
        if (!getPorts ().empty ()) {
                getPorts ()[0]->anchor.notifyMoveAnchor (convertToScaleLayer (getPortPosition (0)));
        }
}

/*****************************************************************************/

void Button::onPress () { impl->arc.put (1); }

/*****************************************************************************/

void Button::onRelease () { impl->arc.put (0); }

/*****************************************************************************/

extern "C" void buttonOnAllocate (void *ptr, float x1, float y1, float x2, float y2)
{
        Button *cn = static_cast<Button *> (ptr);
        cn->onAllocate (Box (Point (x1, y1), Point (x2, y2)));
}

/*****************************************************************************/

extern "C" void buttonOnPress (void *ptr)
{
        Button *cn = static_cast<Button *> (ptr);
        cn->onPress ();
}

/*****************************************************************************/

extern "C" void buttonOnRelease (void *ptr)
{
        Button *cn = static_cast<Button *> (ptr);
        cn->onRelease ();
}
