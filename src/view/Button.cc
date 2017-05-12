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
        self = iw_button_new ();
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
        NodeActor::init ();

        if (!getPorts ().empty ()) {
                Port *p = getPorts ()[0].get ();
                iw_button_set_port_size (IW_BUTTON (self), p->getSize ());
                ClutterColor c = p->getColor ().toClutterColor ();
                iw_button_set_port_color (IW_BUTTON (self), &c);
                iw_button_set_port_user_data (IW_BUTTON (self), p);
        }
}

/*****************************************************************************/

// primitives::Point Button::getPortPosition (const Port *) const
//{
//        primitives::Point p;
//        iw_button_get_port_position (IW_BUTTON (self), &p.x, &p.y);
//        return p;
//}

/*****************************************************************************/

// void Button::onAllocate (primitives::Box const &)
//{
////        if (!getPorts ().empty ()) {
////                getPorts ()[0]->anchor.notifyMoveAnchor (convertToScaleLayer (getPortPosition (0)));
////        }
//}

/*****************************************************************************/
// Getters/setters
/*****************************************************************************/

std::string Button::getText () const { return iw_button_get_text (IW_BUTTON (self)); }

/*****************************************************************************/

void Button::setText (std::string const t) { iw_button_set_text (IW_BUTTON (self), t.c_str ()); }

/*****************************************************************************/

std::string Button::getFont () const { return iw_button_get_font (IW_BUTTON (self)); }

/*****************************************************************************/

void Button::setFont (std::string const t) { iw_button_set_font (IW_BUTTON (self), t.c_str ()); }

/*****************************************************************************/

primitives::Color Button::getFontColor () const
{
        ClutterColor c;
        iw_button_get_font_color (IW_BUTTON (self), &c);
        return primitives::Color (&c);
}

/*****************************************************************************/

void Button::setFontColor (const primitives::Color &value)
{
        ClutterColor color = primitives::Color::toClutterColor (value);
        iw_button_set_font_color (IW_BUTTON (self), &color);
}

/*****************************************************************************/
// C interconnection
/*****************************************************************************/

void Button::onPress () { impl->arc.put (1); }

/*****************************************************************************/

void Button::onRelease () { impl->arc.put (0); }

/*****************************************************************************/

// extern "C" void buttonOnAllocate (void *ptr, float x1, float y1, float x2, float y2)
//{
//        Button *cn = static_cast<Button *> (ptr);
//        cn->onAllocate (primitives::Box (primitives::Point (x1, y1), primitives::Point (x2, y2)));
//}

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
