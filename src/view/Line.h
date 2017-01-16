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

        void setPointA (Point const &p);
        Point getPointA () const;

        void setPointB (Point const &p);
        Point getPointB () const;

        float getStrokeWidth () const;
        void setStrokeWidth (float value);

        float getStrokeDash () const;
        void setStrokeDash (float value);

        Color getStrokeColor () const;
        void setStrokeColor (const Color &value);

        /*---------------------------------------------------------------------------*/

        std::string getText () const;
        void setText (std::string const t);

        std::string getFont () const;
        void setFont (std::string const t);

        Color getFontColor () const;
        void setFontColor (const Color &value);

        bool isTextEditable () const;
        void setTextEditable (bool b);
};

#endif // LINE_H
