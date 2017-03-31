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
};

#endif // DASHEDLINESTRATEGY_H
