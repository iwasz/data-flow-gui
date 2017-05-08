/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Connector.h"
#include "clutter/iw_connector.h"
#include <boost/lexical_cast.hpp>
#include <core/Core.h>

Connector::Connector ()
{
        self = iw_connector_new ();
        clutter_actor_set_reactive (self, TRUE);
        iw_actor_set_user_data (IW_ACTOR (self), this);
        setCppImplementation ();
}

/*****************************************************************************/

void Connector::setPointA (primitives::Point const &p) { iw_connector_set_point_a (IW_CONNECTOR (self), p.x, p.y); }

/*****************************************************************************/

primitives::Point Connector::getPointA () const
{
        primitives::Point p;
        iw_connector_get_point_a (IW_CONNECTOR (self), &p.x, &p.y);
        return p;
}

/*****************************************************************************/

void Connector::setPointB (primitives::Point const &p) { iw_connector_set_point_b (IW_CONNECTOR (self), p.x, p.y); }

/*****************************************************************************/

primitives::Point Connector::getPointB () const
{
        primitives::Point p;
        iw_connector_get_point_a (IW_CONNECTOR (self), &p.x, &p.y);
        return p;
}

/*****************************************************************************/

// Direction Connector::getAFacing () const { return iw_connector_get_a_facing (IW_CONNECTOR (self)); }
// Direction Connector::getBFacing () const { return iw_connector_get_b_facing (IW_CONNECTOR (self)); }

///*****************************************************************************/

// void Connector::setAFacing (Direction value) { iw_connector_set_a_facing (IW_CONNECTOR (self), value); }
// void Connector::setBFacing (Direction value) { iw_connector_set_b_facing (IW_CONNECTOR (self), value); }

/*****************************************************************************/

std::string Connector::getText () const { return iw_connector_get_text (IW_CONNECTOR (self)); }

/*****************************************************************************/

void Connector::setText (std::string const t) { iw_connector_set_text (IW_CONNECTOR (self), t.c_str ()); }

/*****************************************************************************/

std::string Connector::getFont () const { return iw_connector_get_font (IW_CONNECTOR (self)); }

/*****************************************************************************/

void Connector::setFont (std::string const t) { iw_connector_set_font (IW_CONNECTOR (self), t.c_str ()); }

/*****************************************************************************/

primitives::Color Connector::getFontColor () const
{
        ClutterColor c;
        iw_connector_get_font_color (IW_CONNECTOR (self), &c);
        return primitives::Color (&c);
}

/*****************************************************************************/

void Connector::setFontColor (const primitives::Color &value)
{
        ClutterColor color = primitives::Color::toClutterColor (value);
        iw_connector_set_font_color (IW_CONNECTOR (self), &color);
}

/*****************************************************************************/

bool Connector::isTextEditable () const { return iw_connector_is_editable (IW_CONNECTOR (self)); }

/*****************************************************************************/

void Connector::setTextEditable (bool b) { iw_connector_set_editable (IW_CONNECTOR (self), b); }

/*****************************************************************************/

void Connector::setParent (IClutterActor *p)
{
        AbstractActor::setParent (p);

        /*
         * Move to bottom. I don't want this to be separate method of AbstractActor to preven polution.
         * TODO Moving to bottom somehow decreases refresh rate when moving nodes around. It can be seen that
         * connector moves slower than the node it is connected to.
         */
        ClutterActor *parent = clutter_actor_get_parent (getActor ());
        clutter_actor_set_child_below_sibling (parent, getActor (), nullptr);
}

/*****************************************************************************/

// void Connector::onMoveAnchor (const primitives::Point &p, Side s)
//{
//        if (s == A) {
//                setPointA (p);
//        }
//        else {
//                setPointB (p);
//        }
//}

/*****************************************************************************/

// TODO encapsulate in a strategy
void Connector::onTextChanged (std::string const &text)
{
        flow::Arc *arc = getArc ().get ();

        if (!arc) {
                /*
                 * During early phases of Connector life, when you use Line::setText, but the arc is not
                 * set (it can be set with setArc), you'll get nullptr here.
                 */
                return;
        }

        try {
                if (text.empty ()) {
                        // Clear the arc.
                        arc->get ();
                }
                else {
                        arc->put (boost::lexical_cast<int> (text));
                }
        }
        catch (boost::bad_lexical_cast const &e) {
                // TODO !!!
                return;
        }
}

/*****************************************************************************/

void Connector::onReroute (Avoid::ConnRef *connRef)
{
        std::cerr << "onReroute();" << std::endl;

        const Avoid::PolyLine route = connRef->displayRoute ();
        for (size_t i = 0; i < route.size (); ++i) {
                Avoid::Point point = route.at (i);
                printf ("%f, %f\n", point.x, point.y);
        }
}

/*****************************************************************************/

extern "C" void onTextChangedConnector (void *connector, const char *text)
{
        Connector *cn = static_cast<Connector *> (connector);
        cn->onTextChanged (std::string (text));
}
