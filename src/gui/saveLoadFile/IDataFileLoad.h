/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDATAFILE_LOAD_H
#define IDATAFILE_LOAD_H

#include <ReflectionParserAnnotation.h>
#include <core/Exception.h>
#include <core/Object.h>
#include <string>

struct __tiliae_reflect__ IDataFileLoad : public Core::Object {

        virtual ~IDataFileLoad () {}
        virtual void load (std::string const &path) = 0;
};

#endif // IDATAFILE_H
