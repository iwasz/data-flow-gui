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
        enum Operation { SAVE, LOAD };

        virtual ~IDataFile () {}
        virtual void load (std::string const &path) = 0;
        virtual void save (std::string const &path) = 0;

        virtual std::string onButton (IClutterActor *a, Operation o) = 0;
        virtual std::string onCircle (IClutterActor *a, Operation o) = 0;
        virtual std::string onCircularNode (IClutterActor *a, Operation o) = 0;
        virtual std::string onLine (IClutterActor *a, Operation o) = 0;
        virtual std::string onLineConnector (IClutterActor *a, Operation o) = 0;
        virtual std::string onConnector (IClutterActor *a, Operation o) = 0;
        virtual std::string onRectangle (IClutterActor *a, Operation o) = 0;
};

#endif // IDATAFILE_H
