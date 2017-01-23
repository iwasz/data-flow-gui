/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAIN_CONTROLLER_H_
#define MAIN_CONTROLLER_H_

#include "primitives/Geometry.h"
#include "view/Stage.h"
#include <ReflectionParserAnnotation.h>
#include <controller/AbstractController.h>
#include <map>
#include <string>

class Rectangle;
struct IDrawStrategy;
struct IFactoryStrategy;
namespace flow {
class Program;
}

/**
 * Represents one tool that can be picked from left side toolbar.
 */
struct __tiliae_reflect__ Tool {
        IDrawStrategy *drawStrategy;
        IFactoryStrategy *factoryStrategy;
};

typedef __tiliae_reflect__ std::map<std::string, Tool> ToolMap;


/**
 * Additional arguments for state machine. Pointer to this struct is passed
 * whenever I need some additional data in the state machine actions.
 */
struct Event {
        std::string tool;
        Point p;
        Core::Object *object = nullptr;
        int button = -1;
};

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
        void onZoom (std::string const &action);

        void onProgramRun (bool run);
        void pushMessage (std::string const &msg, Event *event);

        ToolMap const &getTools () const { return tools; }
        void setTools (const ToolMap &value) { tools = value; }

        flow::Program *getProgram () const;
        void setProgram (flow::Program *value);

        Rectangle *getRectangularSelector () const;
        void setRectangularSelector (Rectangle *value);

        ClutterActorVector *getSelectedActors ();
        void setSelectedActors (ClutterActorVector *value);

        Stage *getStage () const;
        void setStage (Stage *value);
private:
        ToolMap tools;

        struct Impl;
        Impl *impl;
};

#endif /* MainController_H_ */
