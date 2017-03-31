/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VIEW_DATA_FLOW_LINE_H
#define VIEW_DATA_FLOW_LINE_H

#include "AbstractActor.h"
#include "Stage.h"
#include <ReflectionParserAnnotation.h>
#include <clutter/clutter.h>
#include <string>

class __tiliae_reflect__ Line : public AbstractActor {
public:
        Line ();
        virtual ~Line () {}

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

        virtual void visit (IDataFile *d) { d->onLine (this); }
};

#endif // LINE_H
