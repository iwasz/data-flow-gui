/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MAIN_CONTROLLER_H_
#define MAIN_CONTROLLER_H_

#include "IDrawingEventHandler.h"
#include "ISelectorStrategy.h"
#include "Tool.h"
#include "primitives/Geometry.h"
#include "view/Stage.h"
#include <ReflectionParserAnnotation.h>
#include <controller/AbstractController.h>
#include <map>
#include <string>
#include <vector>

class RectangularSelector;
struct IDrawStrategy;
struct IFactoryStrategy;
class ConsoleBuffer;
class PropertiesController;
class SceneAPI;
namespace flow {
class Program;
}

// TODO remove
#include "file/NativeXmlFormatLoad.h"

/**
 * Controller for drawing new objects like nodes, arcs and the like.
 */
class __tiliae_reflect__ MainController : public GtkForms::AbstractController, public IDrawingEventHandler {
public:
        MainController ();
        virtual ~MainController ();

        void init ();
        virtual GtkForms::ViewsToOpen onStart ();
        virtual void onSubmit ();
        virtual void onIdle ();
        virtual void onStop ();

        void onNewNodeToolClicked (std::string const &name);
        void onZoom (std::string const &action);

        void onProgramRun ();
        void onProgramStep ();
        void onProgramStop ();
        void pushMessage (std::string const &msg, Event const *event);

        ToolContainer const *getToolContainer () const;
        void setToolContainer (ToolContainer *value);

        flow::Program *getProgram () const;
        void setProgram (flow::Program *value);

        RectangularSelector *getRectangularSelector () const;
        void setRectangularSelector (RectangularSelector *value);

        ClutterActorVector *getSelectedActors ();
        void setSelectedActors (ClutterActorVector *value);

        Stage *getStage () const;
        void setStage (Stage *value);

        PropertiesController *getPropertiesController ();
        void setPropertiesController (PropertiesController *p);

        void setSceneApi (SceneAPI *api);

        void onKeyPress (unsigned int key);
        void onSelection (ClutterActorVector *s);
        void onOpen ();
        void onSave ();

        // TODO remove
        void setDataFile (IDataFile *f);
        // TODO remove
        void setLoadFile (NativeXmlFormatLoad *l);

private:
        void updateButtons();

        struct Impl;
        Impl *impl;
};

#endif /* MainController_H_ */
