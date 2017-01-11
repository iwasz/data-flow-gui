/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LINECONNECTOR_H
#define LINECONNECTOR_H

#include "Line.h"
#include "AbstractConnector.h"

class __tiliae_reflect__ LineConnector : public Line, public AbstractConnector {
public:
        virtual ~LineConnector () {}
        virtual void onMoveAnchor (float x, float y, Side s);
};

#endif // LINECONNECTOR_H
