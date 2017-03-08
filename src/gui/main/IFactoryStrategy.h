/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/
#ifndef IFACTORYSTRATEGY_H
#define IFACTORYSTRATEGY_H

#include "Event.h"
#include <ReflectionParserAnnotation.h>
#include <core/Object.h>
#include <core/variant/Variant.h>

struct __tiliae_reflect__ IFactoryStrategy : public Core::Object {
        virtual ~IFactoryStrategy () {}
        virtual Core::Variant run (Event const &e) __tiliae_no_reflect__ = 0;
};

#endif // IFACTORYSTRATEGY_H
