/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef USERCONFIG_H
#define USERCONFIG_H

#include <ReflectionParserAnnotation.h>
#include <core/variant/Variant.h>
#include <string>

class __tiliae_reflect__ UserConfig {
public:

        void set (const std::string &name, Core::Variant data);
        Core::Variant get (const std::string &path);

};

#endif // USERCONFIG_H
