/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/
#ifndef DASHEDLINESTRATEGY_H
#define DASHEDLINESTRATEGY_H

#include <iostream>
#include <ReflectionParserAnnotation.h>
#include "IDrawStrategy.h"

class __tiliae_reflect__ DashedLineStrategy : public IDrawStrategy {
public:
        virtual ~DashedLineStrategy () {}
        virtual void onButtonPress (float x, float y) { std::cerr << "POKAŻ kreseczkę " << x << ", " << y << std::endl; }
        virtual void onMotion (float x, float y) { std::cerr << "kreseczka " << x << ", " << y << std::endl; }
        virtual void onButtonRelease (float x, float y) { std::cerr << "UKRYJ kreseczkę " << x << ", " << y << std::endl; }
};

#endif // DASHEDLINESTRATEGY_H
