/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SceneAPI.h"
#include "gui/main/IFactoryStrategy.h"
#include <core/variant/Cast.h>

struct SceneAPI::Impl {
        Container::BeanFactoryContainer *container = nullptr;
        ToolContainer *toolContainer = nullptr;
};

/*****************************************************************************/

SceneAPI::SceneAPI () { impl = new Impl; }

/*****************************************************************************/

SceneAPI::~SceneAPI () { delete impl; }

/*****************************************************************************/

IClutterActor *SceneAPI::create (std::string const &toolName)
{
        ToolMap &toolMap = impl->toolContainer->getToolMap ();

        if (toolMap.find (toolName) == toolMap.end ()) {
                throw Core::Exception ("No such tool : [" + toolName + "]");
        }

        IFactoryStrategy *factoryStrategy = toolMap[toolName]->factoryStrategy;
        IClutterActor *a = nullptr;

        if (factoryStrategy) {
                Core::Variant v = factoryStrategy->run (Event ());
                a = ocast<IClutterActor *> (v);
        }

        return a;
}

/*****************************************************************************/

Container::BeanFactoryContainer *SceneAPI::getContainer () const { return impl->container; }

/*****************************************************************************/

void SceneAPI::setContainer (Container::BeanFactoryContainer *value) { impl->container = value; }

/*****************************************************************************/

const ToolContainer *SceneAPI::getToolContainer () const { return impl->toolContainer; }

/*****************************************************************************/

void SceneAPI::setToolContainer (ToolContainer *value) { impl->toolContainer = value; }
