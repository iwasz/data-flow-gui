/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDRAWSTRATEGY_H
#define IDRAWSTRATEGY_H

#include <ReflectionParserAnnotation.h>
#include <core/Object.h>

struct __tiliae_reflect__ IDrawStrategy : public Core::Object {
        virtual ~IDrawStrategy () {}
        virtual void onButtonPress (float x, float y) = 0;
        virtual void onMotion (float x, float y) = 0;
        virtual void onButtonRelease (float x, float y) = 0;
};

#endif // IDRAWSTRATEGY_H
