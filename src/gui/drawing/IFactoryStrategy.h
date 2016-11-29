/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/
#ifndef IFACTORYSTRATEGY_H
#define IFACTORYSTRATEGY_H

#include <ReflectionParserAnnotation.h>
#include <core/Object.h>

struct __tiliae_reflect__ IFactoryStrategy : public Core::Object {
        virtual ~IFactoryStrategy () {}
        virtual void run (float x1, float y1, float x2, float y2) __tiliae_no_reflect__ = 0;
};

#endif // IFACTORYSTRATEGY_H
