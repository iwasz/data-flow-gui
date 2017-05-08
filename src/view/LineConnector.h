///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/

//#ifndef LINECONNECTOR_H
//#define LINECONNECTOR_H

//#include "AbstractArcView.h"
//#include "AbstractConnector.h"
//#include "Line.h"

//class __tiliae_reflect__ LineConnector : public Line, public AbstractConnector, public AbstractArcView {
//public:
//        LineConnector ();
//        virtual ~LineConnector () {}

//        // TODO this is a hack, remove someday.
//        virtual void setParent (IClutterActor *parent);

//        virtual void onConnectAnchor (primitives::Point const &p, Side s) { onMoveAnchor (p, s); }
//        virtual void onMoveAnchor (primitives::Point const &p, Side s);
//        virtual void onDisconnectAnchor (/*Side s*/) { delete this; }
//        virtual void onTextChanged (std::string const &text);

//        virtual Direction getAFacing () const { return NONE; }
//        virtual Direction getBFacing () const { return NONE; }

//        virtual void setAFacing (Direction value) {}
//        virtual void setBFacing (Direction value) {}

//        virtual void visit (IDataFileSave *d) { d->onLineConnector (this); }
//};

//#endif // LINECONNECTOR_H
