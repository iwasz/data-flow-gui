/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LINECONNECTOR_H
#define LINECONNECTOR_H

#include "AbstractConnector.h"
#include "Line.h"

class __tiliae_reflect__ LineConnector : public Line, public AbstractConnector {
public:
        LineConnector ();
        virtual ~LineConnector () {}

        virtual void onConnectAnchor (Point const &p, Side s) { onMoveAnchor (p, s); }
        virtual void onMoveAnchor (Point const &p, Side s);
        void virtual onDisconnectAnchor (Point const &p, Side s) { onMoveAnchor (p, s); }
};

#endif // LINECONNECTOR_H
