/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FLOW_IARCVIEW_H
#define FLOW_IARCVIEW_H

#include <ReflectionParserAnnotation.h>
#include <core/Arc.h>
#include <core/Object.h>
#include <memory>

struct __tiliae_reflect__ IArcView : public virtual Core::Object {
        virtual ~IArcView () {}
        virtual std::shared_ptr<flow::Arc> getArc () = 0;
        virtual void setArc (std::shared_ptr<flow::Arc> a) = 0;
};

#endif // IARCVIEW_H
