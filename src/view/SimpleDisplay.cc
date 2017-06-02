/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SimpleDisplay.h"
#include "clutter/iw_simple_display.h"
#include "customNode/DisplayNode.h"
#include <boost/lexical_cast.hpp>
#include <core/Exception.h>
#include <core/variant/Cast.h>

/*****************************************************************************/

SimpleDisplay::SimpleDisplay ()
{
        self = iw_simple_display_new ();
        clutter_actor_set_reactive (self, TRUE);
        iw_actor_set_user_data (IW_ACTOR (self), this);
        setCppImplementation ();
}

/*****************************************************************************/

void SimpleDisplay::onValueChange (Core::Variant const &v)
{
        iw_simple_display_set_text (IW_SIMPLE_DISPLAY (self), boost::lexical_cast<std::string> (vcast<int> (v)).c_str ());
}
