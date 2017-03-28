/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LOAD_NATIVEXMLFORMAT_H
#define LOAD_NATIVEXMLFORMAT_H

#include <ReflectionParserAnnotation.h>
#include <string>

namespace Wrapper {
class BeanWrapper;
}
class SceneAPI;

class __tiliae_reflect__ NativeXmlFormatLoad {
public:
        NativeXmlFormatLoad ();
        virtual ~NativeXmlFormatLoad ();

        virtual void load (std::string const &path);

        void setSceneApi (SceneAPI *value);
        void setWrapper (Wrapper::BeanWrapper *value);

private:
        struct Impl;
        Impl *impl;
};

#endif // NATIVEXMLFORMAT_H
