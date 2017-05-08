/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANGLE_CONNECTOR_H
#define ANGLE_CONNECTOR_H

#include "AbstractActor.h"
#include "AbstractArcView.h"
#include "AbstractConnector.h"

class __tiliae_reflect__ Connector : public AbstractActor, public AbstractConnector, public AbstractArcView {
public:
        Connector ();
        virtual ~Connector () {}

        // TODO this is a hack, remove someday.
        virtual void setParent (IClutterActor *parent);

        /*---------------------------------------------------------------------------*/

        virtual void setPointA (primitives::Point const &p);
        virtual primitives::Point getPointA () const;

        virtual void setPointB (primitives::Point const &p);
        virtual primitives::Point getPointB () const;

        virtual std::string getText () const;
        virtual void setText (std::string const t);

        virtual std::string getFont () const;
        virtual void setFont (std::string const t);

        virtual primitives::Color getFontColor () const;
        virtual void setFontColor (const primitives::Color &value);

        virtual bool isTextEditable () const;
        virtual void setTextEditable (bool b);

        /*---------------------------------------------------------------------------*/

//        virtual void onConnectAnchor (primitives::Point const &p, Side s) { onMoveAnchor (p, s); }
//        virtual void onMoveAnchor (primitives::Point const &p, Side s);
//        virtual void onDisconnectAnchor (/*Side s*/) { delete this; }

        virtual void onReroute (Avoid::ConnRef *);

        virtual void onTextChanged (std::string const &text);

        //        virtual Direction getAFacing () const;
        //        virtual Direction getBFacing () const;

        //        virtual void setAFacing (Direction value);
        //        virtual void setBFacing (Direction value);

        virtual void visit (IDataFileSave *d) { d->onConnector (this); }
};

#endif // LINECONNECTOR_H
