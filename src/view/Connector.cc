/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Connector.h"
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
        const Avoid::PolyLine route = connRef->displayRoute ();
        pointsCache.resize (route.size ());

        for (size_t i = 0; i < route.size (); ++i) {
                Avoid::Point point = route.at (i);
                pointsCache[i].x = point.x;
                pointsCache[i].y = point.y;
        }

        iw_connector_set_points (IW_CONNECTOR (self), pointsCache.data (), pointsCache.size ());
}

/*****************************************************************************/

extern "C" void onTextChangedConnector (void *connector, const char *text)
{
        Connector *cn = static_cast<Connector *> (connector);
        cn->onTextChanged (std::string (text));
}
