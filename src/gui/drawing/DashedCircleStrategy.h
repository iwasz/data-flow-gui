/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/
#ifndef DASHEDCIRCLESTRATEGY_H
#define DASHEDCIRCLESTRATEGY_H

#include "IDrawStrategy.h"
#include "view/Circle.h"
#include <ReflectionParserAnnotation.h>

class __tiliae_reflect__ DashedCircleStrategy : public IDrawStrategy {
public:
        virtual ~DashedCircleStrategy () {}
        virtual void onButtonPress (float x, float y);
        virtual void onMotion (float x, float y);
        virtual void onButtonRelease (float x, float y);

        Circle *getCircle () const { return circle; }
        void setCircle (Circle *value) { circle = value; }

private:

        Circle *circle = nullptr;
};

#endif // DASHEDCIRCLESTRATEGY_H
