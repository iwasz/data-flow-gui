/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LineConnector.h"
#include <boost/lexical_cast.hpp>
#include <core/Core.h>

LineConnector::LineConnector () : Line (), AbstractConnector () {}

void LineConnector::onMoveAnchor (const Point &p, Side s)
{
        if (s == A) {
                setPointA (p);
        }
        else {
                setPointB (p);
        }
}

/*****************************************************************************/

// TODO encapsulate in a strategy
void LineConnector::onTextChanged (std::string const &text)
{
        flow::Arc *arc = getArc ().get ();

        if (!arc) {
                /*
                 * During early phases of LineConnector life, when you use Line::setText, but the arc is not
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

extern "C" void onTextChanged (void *lineConnector, const char *text)
{
        LineConnector *cn = static_cast<LineConnector *> (lineConnector);
        cn->onTextChanged (std::string (text));
}
