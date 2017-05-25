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
#include "ConnectorActor.h"
#include "clutter/iw_connector.h"
#include <core/IFlowObserver.h>

class __tiliae_reflect__ Connector : public ConnectorActor, public AbstractArcView, public flow::IFlowObserver {
public:
        Connector ();
        virtual ~Connector () {}

        // TODO this is a hack, remove someday.
        virtual void setParent (IClutterActor *parent);

        /*---------------------------------------------------------------------------*/

        virtual std::string getText () const;
        virtual void setText (std::string const t);

        virtual std::string getFont () const;
        virtual void setFont (std::string const t);

        virtual primitives::Color getFontColor () const;
        virtual void setFontColor (const primitives::Color &value);

        virtual bool isTextEditable () const;
        virtual void setTextEditable (bool b);

        /*---------------------------------------------------------------------------*/

        /// Callback called from the router
        virtual void onReroute (Avoid::ConnRef *);
        /// Callback fired from clutter stuff.
        virtual void onTextChanged (std::string const &text);
        /// Callback called when data-flow program gets or puts from an Arc.
        virtual void onValueChange (Core::Variant const &v);

        /*---------------------------------------------------------------------------*/

        virtual void visit (IDataFileSave *d) { d->onConnector (this); }

private:
        std::vector<CPoint> pointsCache;
};

#endif // LINECONNECTOR_H
