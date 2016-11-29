/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_CIRCLE_H
#define DATA_FLOW_CIRCLE_H

#include "AbstractActor.h"
#include "Stage.h"
#include <ReflectionParserAnnotation.h>
#include <clutter/clutter.h>
#include <string>

class __tiliae_reflect__ Circle : public AbstractActor {
public:
        Circle ();
        virtual ~Circle () {}

        bool isFill () const;
        void setFill (bool value);

        float getStrokeWidth () const;
        void setStrokeWidth (float value);

        float getStrokeDash () const;
        void setStrokeDash (float value);

        std::string getStrokeColor () const;
        void setStrokeColor (const std::string &value);

        std::string getFillColor () const;
        void setFillColor (const std::string &value);
};

#endif // CIRCLE_H
