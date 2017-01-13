/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DASHEDLINES_CONNECTOR_TRATEGY_H
#define DASHEDLINES_CONNECTOR_TRATEGY_H

#include "IDrawStrategy.h"
#include <ReflectionParserAnnotation.h>
#include <iostream>
#include <view/LineConnector.h>
#include <view/Line.h>

class __tiliae_reflect__ DashedLineConnectorStrategy : public IDrawStrategy {
public:
        virtual ~DashedLineConnectorStrategy () {}
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
        Core::Object *startObject = nullptr;
        Core::Object *endObject = nullptr;
};

#endif // DASHEDLINESTRATEGY_H
