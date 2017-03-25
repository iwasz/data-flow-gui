/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SceneAPI.h"
#include "LineConnector.h"
#include "Port.h"
#include "gui/main/IFactoryStrategy.h"
#include <core/variant/Cast.h>
#include <vector>
#include <view/INodeView.h>

struct SceneAPI::Impl {
        Container::BeanFactoryContainer *container = nullptr;
        ToolContainer *toolContainer = nullptr;
        ClutterActorSet allActors;
        ClutterActorSet allConnectors;
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

        if (dynamic_cast<IConnector *> (a)) {
                impl->allConnectors.insert (a);
        }
        else {
                impl->allActors.insert (a);
        }

        return a;
}

/*****************************************************************************/

void SceneAPI::connect (LineConnector *lc, Port *pa, Port *pb)
{
        if (!pa || !pb) {
                return;
        }

        lc->connect (&pa->anchor, IConnector::A);
        lc->connect (&pb->anchor, IConnector::B);

        /*****************************************************************************/
        /* Connect flow::INodes                                                      */
        /*****************************************************************************/

        assert (lc->getArc ());
        flow::Arc *arc = lc->getArc ().get ();

        if (pa->getNodeView () && pa->getNodeView ()->getNode ()) {
                flow::INode *startNode = pa->getNodeView ()->getNode ().get ();

                if (pa->isInput ()) {
                        startNode->setInput (pa->getProgramNumber (), arc);
                }
                else {
                        startNode->addOutput (pa->getProgramNumber (), arc);
                }
        }

        if (pb->getNodeView () && pb->getNodeView ()->getNode ()) {
                flow::INode *endNode = pb->getNodeView ()->getNode ().get ();

                if (pb->isInput ()) {
                        endNode->setInput (pb->getProgramNumber (), arc);
                }
                else {
                        endNode->addOutput (pb->getProgramNumber (), arc);
                }
        }
}

/*****************************************************************************/

Container::BeanFactoryContainer *SceneAPI::getContainer () const { return impl->container; }

/*****************************************************************************/

void SceneAPI::setContainer (Container::BeanFactoryContainer *value) { impl->container = value; }

/*****************************************************************************/

const ToolContainer *SceneAPI::getToolContainer () const { return impl->toolContainer; }

/*****************************************************************************/

void SceneAPI::setToolContainer (ToolContainer *value) { impl->toolContainer = value; }

ClutterActorSet const &SceneAPI::getAllActors () const { return impl->allActors; }
ClutterActorSet &SceneAPI::getAllActors () { return impl->allActors; }
ClutterActorSet const &SceneAPI::getAllConnectors () const { return impl->allConnectors; }
ClutterActorSet &SceneAPI::getAllConnectors () { return impl->allConnectors; }
