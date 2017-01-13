/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/
#ifndef DASHEDLINESTRATEGY_H
#define DASHEDLINESTRATEGY_H

#include <view/Line.h>
#include "IDrawStrategy.h"
#include <ReflectionParserAnnotation.h>
#include <iostream>

class __tiliae_reflect__ DashedLineStrategy : public IDrawStrategy {
public:
        virtual ~DashedLineStrategy () {}
        virtual void onButtonPress (Point p, Core::Object *o);
        virtual void onMotion (Point p, Core::Object *o);
        virtual bool onButtonRelease (Point p, Core::Object *o);
        virtual void reshape (IClutterActor *a);

        Line *getLine () const { return line; }
        void setLine (Line *value) { line = value; }

private:
        Line *line = nullptr;
        Point startPoint;
        Point endPoint;
};

#endif // DASHEDLINESTRATEGY_H
