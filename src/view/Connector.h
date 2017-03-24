/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANGLE_CONNECTOR_H
#define ANGLE_CONNECTOR_H

#include "AbstractArcView.h"
#include "AbstractConnector.h"
#include "LineConnector.h"

class __tiliae_reflect__ Connector : public LineConnector {
public:
        Connector ();
        virtual ~Connector () {}

        /*---------------------------------------------------------------------------*/

        virtual void setPointA (Point const &p);
        virtual Point getPointA () const;

        virtual void setPointB (Point const &p);
        virtual Point getPointB () const;

        virtual std::string getText () const;
        virtual void setText (std::string const t);

        virtual std::string getFont () const;
        virtual void setFont (std::string const t);

        virtual Color getFontColor () const;
        virtual void setFontColor (const Color &value);

        virtual bool isTextEditable () const;
        virtual void setTextEditable (bool b);

        virtual Direction getAFacing () const;
        virtual Direction getBFacing () const;

        virtual void setAFacing (Direction value);
        virtual void setBFacing (Direction value);

        virtual std::string visit (IDataFile *d, IDataFile::Operation o) { return d->onConnector (this, o); }
};

#endif // LINECONNECTOR_H
