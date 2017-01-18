/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAIN_CONTROLLER_H_
#define MAIN_CONTROLLER_H_

#include "IDrawStrategy.h"
#include "IFactoryStrategy.h"
#include <Program.h>
#include <ReflectionParserAnnotation.h>
#include <controller/AbstractController.h>
#include <map>
#include <string>

/**
 * Represents one tool that can be picked from left side toolbar.
 */
struct __tiliae_reflect__ Tool {
        IDrawStrategy *drawStrategy;
        IFactoryStrategy *factoryStrategy;
};

typedef __tiliae_reflect__ std::map<std::string, Tool> ToolMap;

/**
 * Controller for drawing new objects like nodes, arcs and the like.
 */
class __tiliae_reflect__ MainController : public GtkForms::AbstractController {
public:
        MainController ();
        virtual ~MainController ();

        void init ();
        virtual std::string onStart ();
        virtual void onSubmit ();
        virtual void onIdle ();
        virtual void onStop ();

        void onNewNodeToolClicked (std::string const &name);
        void onButtonPress (Point p, Core::Object *o);
        void onButtonRelease (Point p, Core::Object *o);
        void onMotion (Point p, Core::Object *o);
        void onEnter (Point p, Object *o);
        void onLeave (Point p, Object *o);

        void onProgramRun ();

        ToolMap const &getTools () const { return tools; }
        void setTools (const ToolMap &value) { tools = value; }

        flow::Program *getProgram() const;
        void setProgram(flow::Program *value);

private:
        ToolMap tools;

        struct Impl;
        Impl *impl;
};

#endif /* MainController_H_ */
