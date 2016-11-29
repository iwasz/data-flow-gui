/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_CIRCLE_H
#define DATA_FLOW_CIRCLE_H

#include "IClutterActor.h"
#include "Stage.h"
#include <ReflectionParserAnnotation.h>
#include <clutter/clutter.h>
#include <string>

class __tiliae_reflect__ Circle : public IClutterActor {
public:
        Circle ();
        virtual ~Circle () {}

        void setParent (IClutterActor *parent);
        ClutterActor *getActor () { return self; }

        bool getVisible () const;
        void setVisible (bool value);

        bool isFill () const;
        void setFill (bool value);

        float getH () const;
        void setH (float value);

        float getW () const;
        void setW (float value);

        float getY () const;
        void setY (float value);

        float getX () const;
        void setX (float x);

        float getStrokeWidth () const;
        void setStrokeWidth (float value);

        float getStrokeDash () const;
        void setStrokeDash (float value);

        std::string getStrokeColor () const;
        void setStrokeColor (const std::string &value);

        std::string getFillColor () const;
        void setFillColor (const std::string &value);

private:
        ClutterActor *self;
};

#endif // CIRCLE_H
