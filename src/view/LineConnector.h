/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LINECONNECTOR_H
#define LINECONNECTOR_H

#include "AbstractArcView.h"
#include "AbstractConnector.h"
#include "Line.h"

class __tiliae_reflect__ LineConnector : public Line, public AbstractConnector, public AbstractArcView {
public:
        LineConnector ();
        virtual ~LineConnector () {}

        virtual void onConnectAnchor (Point const &p, Side s) { onMoveAnchor (p, s); }
        virtual void onMoveAnchor (Point const &p, Side s);
        virtual void onDisconnectAnchor (Point const &p, Side s) { onMoveAnchor (p, s); }
        virtual void onTextChanged (std::string const &text);
};

#endif // LINECONNECTOR_H
