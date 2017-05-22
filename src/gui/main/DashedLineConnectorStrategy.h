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
#include <view/Line.h>

class __tiliae_reflect__ DashedLineConnectorStrategy : public IDrawStrategy {
public:
        virtual ~DashedLineConnectorStrategy () {}

        virtual void onButtonPress (Event const &e);
        virtual void onMotion (Event const &e);
        virtual bool onButtonRelease (Event const &e);
        virtual void onObjectCreated (IClutterActor *a);

        Line *getLine () const { return line; }
        void setLine (Line *value) { line = value; }

private:
        Line *line = nullptr;
        primitives::Point startPoint;
        primitives::Point endPoint;
        Core::Object *startObject = nullptr;
        Core::Object *endObject = nullptr;
};

#endif // DASHEDLINESTRATEGY_H
