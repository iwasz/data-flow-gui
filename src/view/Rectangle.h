/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_RECTANGLE_H
#define DATA_FLOW_RECTANGLE_H

#include "AbstractActor.h"
#include "Stage.h"
#include <ReflectionParserAnnotation.h>
#include <clutter/clutter.h>
#include <string>

class __tiliae_reflect__ Rectangle : public AbstractActor {
public:
        Rectangle ();
        virtual ~Rectangle () {}

        bool isFill () const;
        void setFill (bool value);

        float getStrokeWidth () const;
        void setStrokeWidth (float value);

        float getStrokeDash () const;
        void setStrokeDash (float value);

        Color getStrokeColor () const;
        void setStrokeColor (const Color &value);

        Color getFillColor () const;
        void setFillColor (const Color &value);
};

#endif // RECTANGLE_H
