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

void Connector::setPointA (Point const &p) { iw_connector_set_point_a (IW_CONNECTOR (self), p.x, p.y); }

/*****************************************************************************/

Point Connector::getPointA () const
{
        Point p;
        iw_connector_get_point_a (IW_CONNECTOR (self), &p.x, &p.y);
        return p;
}

/*****************************************************************************/

void Connector::setPointB (Point const &p) { iw_connector_set_point_b (IW_CONNECTOR (self), p.x, p.y); }

/*****************************************************************************/

Point Connector::getPointB () const
{
        Point p;
        iw_connector_get_point_a (IW_CONNECTOR (self), &p.x, &p.y);
        return p;
}

/*****************************************************************************/

void Connector::setPointC (Point const &p) { iw_connector_set_point_c (IW_CONNECTOR (self), p.x, p.y); }

/*****************************************************************************/

Point Connector::getPointC () const
{
        Point p;
        iw_connector_get_point_c (IW_CONNECTOR (self), &p.x, &p.y);
        return p;
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

Color Connector::getFontColor () const
{
        ClutterColor c;
        iw_connector_get_font_color (IW_CONNECTOR (self), &c);
        return Color (&c);
}

/*****************************************************************************/

void Connector::setFontColor (const Color &value)
{
        ClutterColor color = Color::toClutterColor (value);
        iw_connector_set_font_color (IW_CONNECTOR (self), &color);
}

/*****************************************************************************/

bool Connector::isTextEditable () const { return iw_connector_is_editable (IW_CONNECTOR (self)); }

/*****************************************************************************/

void Connector::setTextEditable (bool b) { iw_connector_set_editable (IW_CONNECTOR (self), b); }

/*****************************************************************************/

extern "C" void onTextChangedConnector (void *connector, const char *text)
{
        Connector *cn = static_cast<Connector *> (connector);
        cn->onTextChanged (std::string (text));
}
