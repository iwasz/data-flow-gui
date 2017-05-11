/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCENEAPI_H
#define SCENEAPI_H

#include "IClutterActor.h"
#include "gui/main/Tool.h"
#include <ReflectionParserAnnotation.h>
#include <container/Container.h>
#include <string>

class ConnectorActor;
class Port;

/**
 * Main entry point for creating objects on stage, both as a response to user GUI actions
 * and programmaticaly for example reading a file.
 */
class __tiliae_reflect__ SceneAPI {
public:
        SceneAPI ();
        ~SceneAPI ();

        /// Creates an onject. Do not delete, managed by SceneAPI.
        IClutterActor *create (std::string const &toolName);
        static void connect (ConnectorActor *lc, Port *pa, Port *pb);

        Container::BeanFactoryContainer *getContainer () const;
        void setContainer (Container::BeanFactoryContainer *value);

        ToolContainer const *getToolContainer () const;
        void setToolContainer (ToolContainer *value);

        ClutterActorSet const &getAllActors () const __tiliae_no_reflect__;
        ClutterActorSet &getAllActors () __tiliae_no_reflect__;
        ClutterActorSet const &getAllConnectors () const __tiliae_no_reflect__;
        ClutterActorSet &getAllConnectors () __tiliae_no_reflect__;

private:
        struct Impl;
        Impl *impl;
};

#endif // SCENEAPI_H
