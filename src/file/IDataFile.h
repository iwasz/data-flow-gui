/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDATAFILE_H
#define IDATAFILE_H

#include <ReflectionParserAnnotation.h>
#include <core/Exception.h>
#include <core/Object.h>
#include <string>

struct IClutterActor;

struct __tiliae_reflect__ IDataFile : public Core::Object {

        virtual ~IDataFile () {}
        virtual void load (std::string const &path) = 0;
        virtual void save (std::string const &path) = 0;

        virtual void onButton (IClutterActor *a) = 0;
        virtual void onCircle (IClutterActor *a) = 0;
        virtual void onCircularNode (IClutterActor *a) = 0;
        virtual void onLine (IClutterActor *a) = 0;
        virtual void onLineConnector (IClutterActor *a) = 0;
        virtual void onConnector (IClutterActor *a) = 0;
        virtual void onRectangle (IClutterActor *a) = 0;
};

#endif // IDATAFILE_H
