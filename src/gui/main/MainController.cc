/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MainController.h"
#include "IDrawStrategy.h"
#include "IFactoryStrategy.h"
#include "ISelectorStrategy.h"
#include "gui/console/ConsoleBuffer.h"
#include "gui/main/RectangularSelectorStrategy.h"
#include "gui/properties/PropertiesController.h"
#include "view/INodeView.h"
#include "view/LineConnector.h"
#include "view/Rectangle.h"
#include "view/RectangularSelector.h"
#include "view/ScaleLayer.h"
#include "view/SceneAPI.h"
#include "view/Stage.h"
#include <App.h>
#include <Logging.h>
#include <Program.h>
#include <StateMachine.h>

static src::logger_mt &lg = logger::get ();

/*****************************************************************************/

enum MachineStates {
        IDLE,          /// Nothing is happening
        TOOL_SELECTED, /// Toolbox clicked, tool picked.
        DRAW,          /// Creating a new object by drawing something
        SELECT,        /// Drawing the selection box
        MOVE,          /// Moving an object around.
        STAGE_MOVE     /// Moving the viewport.
};

/*****************************************************************************/

struct MainController::Impl {

        Impl (MainController *t) : that (t), inputQueue (STRING_QUEUE_SIZE), machine (&inputQueue) {}
        ~Impl () {}

        void configureMachine ();
        void pushMessage (std::string const &msg, void *arg);

        MainController *that;
        StringQueue inputQueue;
        StateMachine machine;
        flow::Program *program = nullptr;
        bool runProgram = false;
        RectangularSelector *rectangularSelector = nullptr;
        Stage *stage = nullptr;
        Event event; // Tempporary for some handlers.
        ClutterActorVector *selectedActors = nullptr;
        ToolContainer *toolContainer = nullptr;
        PropertiesController *propertiesController = nullptr;
        SceneAPI *sceneAPI = nullptr;

        /// Additional state. Used directly in the drawing events (onMove, onRelease).
        struct {
                /// Name of curently selected tool (arc, node etc).
                std::string currentTool;
                /// Draw strategy draws shapes just prior to actual object creation.
                IDrawStrategy *currentDrawStrategy = nullptr;
                ISelectorStrategy *currentSelectorStrategy = nullptr;

                // TODO remove encapsulate.
                Point last;
        } vars;
};

/*****************************************************************************/

// Run machine synchronously.
void MainController::Impl::pushMessage (std::string const &m, void *arg)
{
        if (!inputQueue.back ()) {
                inputQueue.push_back ();
        }

        StringQueue::Element *el = inputQueue.back ();
        strncpy (el->data, m.c_str (), STRING_QUEUE_BUFFER_SIZE);
        el->arg = arg;
        machine.run ();
}

/*****************************************************************************/

void MainController::Impl::configureMachine ()
{
        /* clang-format off */
        machine.state (IDLE, State::INITIAL)
                ->entry ([this] (const char *, void *arg) {
                        vars.currentTool = "";
                        vars.currentDrawStrategy = nullptr;
                        return true;
                })
                ->transition (TOOL_SELECTED)->when (eq ("selected.tool"))
                ->transition (STAGE_MOVE)->when (eq ("stage.press.scroll"))
                ->transition (IDLE)->when (eq ("stage.delete"))->then ([this] (const char *, void *arg) {
                        if (selectedActors->empty ()) {
                                return true;
                        }

                        for (IClutterActor *actor : *selectedActors) {
                                delete actor;
                        }
                        selectedActors->clear ();
                        vars.currentSelectorStrategy->unselectAll();
                        that->onSelection (selectedActors);
                        return true;
                })
                ->transition (SELECT)->when (eq ("stage.press"))->then ([this] (const char *, void *arg) {
                        vars.currentTool = "select";
                        vars.currentDrawStrategy = toolContainer->getToolMap()[vars.currentTool]->drawStrategy;
                        vars.currentSelectorStrategy = toolContainer->getToolMap()[vars.currentTool]->selectorStrategy;
                        vars.currentDrawStrategy->onButtonPress (*static_cast <Event *> (arg));
                        return true;
                })
                ->transition (MOVE)->when (eq ("object.press"))->then ([this] (const char *, void *arg) {
                        vars.currentTool = "select";
                        vars.currentDrawStrategy = toolContainer->getToolMap()[vars.currentTool]->drawStrategy;
                        vars.currentSelectorStrategy = toolContainer->getToolMap()[vars.currentTool]->selectorStrategy;
                        Event *args = static_cast <Event *> (arg);

                        if (std::find (selectedActors->cbegin (), selectedActors->cend (), args->object) == selectedActors->cend ()) {
                                vars.currentDrawStrategy->onButtonPress (*args);
                                vars.currentDrawStrategy->onButtonRelease (*args);
                                // TODO this cant be like that!
                                dynamic_cast <RectangularSelectorStrategy *> (vars.currentDrawStrategy)->onObjectCreated (nullptr, false);
                        }

                        that->onSelection (selectedActors);
                        return true;
                });

        /*---------------------------------------------------------------------------*/

        machine.state (TOOL_SELECTED)
                ->entry ([this] (const char *, void *arg) {
                        Event *args = static_cast <Event *> (arg);
                        vars.currentTool = args->tool;

                        ToolMap &toolMap = toolContainer->getToolMap ();
                        if (toolMap.find (vars.currentTool) == toolMap.end ()) {
                                throw Core::Exception ("No such tool : [" + vars.currentTool + "]");
                        }

                        vars.currentDrawStrategy = toolMap[vars.currentTool]->drawStrategy;
                        return true;
                })
                ->transition (TOOL_SELECTED)->when (eq ("selected.tool"))
                ->transition (IDLE)->when (eq ("selected.select"))
                ->transition (DRAW)->when (eq ("stage.press"))->then ([this] (const char *, void *arg) {
                        vars.currentDrawStrategy->onButtonPress (*static_cast <Event *> (arg));
                        return true;
                });

        /*---------------------------------------------------------------------------*/

        machine.state (DRAW)
                ->transition (DRAW)->when (eq ("stage.motion"))->then ([this] (const char *, void *arg) {
                        vars.currentDrawStrategy->onMotion (*static_cast <Event *> (arg));
                        return true;
                })
                ->transition (IDLE)->when (eq ("stage.release"))->then ([this] (const char *, void *arg) {
                        Event *args = static_cast <Event *> (arg);

                        if (!vars.currentDrawStrategy->onButtonRelease (*args)) {
                                return true;
                        }

                        IClutterActor *a = sceneAPI->create(vars.currentTool);
                        vars.currentDrawStrategy->onObjectCreated (a);

                        if (a) {
                                a->setVisible (true);
                        }

                        return true;
                });

        /*---------------------------------------------------------------------------*/

        machine.state (SELECT)
                ->transition (SELECT)->when (eq ("stage.motion"))->then ([this] (const char *, void *arg) {
                        vars.currentDrawStrategy->onMotion (*static_cast <Event *> (arg));
                        return true;
                })
                ->transition (IDLE)->when (eq ("stage.release"))->then ([this] (const char *, void *arg) {
                        Event *args = static_cast <Event *> (arg);

                        if (!vars.currentDrawStrategy->onButtonRelease (*args)) {
                                return true;
                        }

                        vars.currentDrawStrategy->onObjectCreated (nullptr);
                        that->onSelection (selectedActors);
                        return true;
                });

        /*---------------------------------------------------------------------------*/

        machine.state (MOVE)
//                ->entry ([this] (const char *, void *arg) {
//                        Event *event = static_cast <Event *> (arg);
//                        vars.last = event->positionStageCoords;
//                        return true;
//                })
                ->transition (MOVE)->when (eq ("stage.motion"))->then ([this] (const char *, void *arg) {
                        Event *event = static_cast <Event *> (arg);

                        Point p2;
                        clutter_actor_get_position (rectangularSelector->getActor(), &p2.x, &p2.y);
                        p2.x += event->stageDelta.x;
                        p2.y += event->stageDelta.y;
                        //std::cerr << "++ " << event.stageDelta << std::endl;
                        clutter_actor_set_position (rectangularSelector->getActor (), p2.x, p2.y);

                        return true;
                })
                ->transition (IDLE)->when (eq ("stage.release"));

        /*---------------------------------------------------------------------------*/

        machine.state (STAGE_MOVE)
                ->entry ([this] (const char *, void *arg) {
                        Event *event = static_cast <Event *> (arg);
                        vars.last = event->positionStageCoords;
                        return true;
                })
                ->transition (STAGE_MOVE)->when (eq ("stage.motion"))->then ([this] (const char *, void *arg) {
                        Event *event = static_cast <Event *> (arg);

                        Point n;
                        n.x = event->positionStageCoords.x - vars.last.x;
                        n.y = event->positionStageCoords.y - vars.last.y;
                        stage->getScaleLayer ()->pan (n);

                        vars.last = event->positionStageCoords;
                        return true;
                })
                ->transition (IDLE)->when (eq ("stage.release.scroll"));

        /* clang-format on */
}

/*****************************************************************************/

MainController::MainController () { impl = new Impl (this); }

/*****************************************************************************/

MainController::~MainController () { delete impl; }

/*****************************************************************************/

void MainController::init () { impl->configureMachine (); }

/*****************************************************************************/

GtkForms::ViewsToOpen MainController::onStart () { return "mainView"; }

/*
 * Po konwersji wykonuje się metoda IController::onSubmit:
 */
void MainController::onSubmit () {}

/****************************************************************************/

void MainController::onStop () {}

/****************************************************************************/

/*
 * This state machine engine was menat to be used in asynchronouch environments, thus
 * the queue and running the machine in a loop. In this program though, I wanted to use
 * the state machine synchronously (since everything interesing me is running in one
 * thread here), so I run the machine instantly after sending it a message (see
 * MainController::Impl::pushMessage), but it is not enough. Sometimes StateMachine::run
 * must be run a few times (not only one) to enable multiple transitions caused by one event
 * (this is the case sometimes). So I consider the following method a workaround, and
 * it should be fixed someday, but state machind would have to be modified.
 */
void MainController::onIdle ()
{
        impl->machine.run ();
        if (impl->runProgram) {
                impl->program->step ();
        }
}

/****************************************************************************/

void MainController::pushMessage (std::string const &msg, Event const *event) { impl->pushMessage (msg, const_cast<Event *> (event)); }

/****************************************************************************/
/* Drawing events                                                           */
/****************************************************************************/

void MainController::onNewNodeToolClicked (std::string const &name)
{
        console->append (name + "\n");

        if (name == "select") {
                impl->pushMessage ("selected.select", &impl->event);
        }
        else {
                impl->event.tool = name;
                impl->pushMessage ("selected.tool", &impl->event);
        }
}

/*****************************************************************************/

void MainController::onZoom (std::string const &action)
{
        if (action == "in") {
                impl->stage->getScaleLayer ()->zoomIn ();
        }
        else if (action == "out") {
                impl->stage->getScaleLayer ()->zoomOut ();
        }
        else if (action == "1") {
                impl->stage->getScaleLayer ()->zoom (1.0);
        }
}

/*****************************************************************************/

flow::Program *MainController::getProgram () const { return impl->program; }

/*****************************************************************************/

void MainController::setProgram (flow::Program *value) { impl->program = value; }

/*****************************************************************************/

void MainController::onProgramStop ()
{
        impl->runProgram = false;
        impl->program->reset ();
        updateButtons ();
}

/*****************************************************************************/

void MainController::updateButtons ()
{
        set ("buttonStep", Core::Variant (!impl->runProgram));
        refresh ("buttonStep");

        if (impl->runProgram) {
                set ("buttonRun", Core::Variant ("gtk-media-pause"));
        }
        else {
                set ("buttonRun", Core::Variant ("gtk-media-play"));
        }

        refresh ("buttonRun");
}

/*****************************************************************************/

void MainController::onProgramRun ()
{
        impl->runProgram = !impl->runProgram;
        updateButtons ();
}

void MainController::onProgramStep () { impl->program->step (); }

/*****************************************************************************/

RectangularSelector *MainController::getRectangularSelector () const { return impl->rectangularSelector; }

/*****************************************************************************/

void MainController::setRectangularSelector (RectangularSelector *value)
{
        impl->rectangularSelector = value;
        value->setEventHandler (this);
}

/*****************************************************************************/

ClutterActorVector *MainController::getSelectedActors () { return impl->selectedActors; }

/*****************************************************************************/

void MainController::setSelectedActors (ClutterActorVector *value) { impl->selectedActors = value; }

/*****************************************************************************/

Stage *MainController::getStage () const { return impl->stage; }

/*****************************************************************************/

void MainController::setStage (Stage *value)
{
        impl->stage = value;
        value->setEventHandler (this);
}

/*****************************************************************************/

const ToolContainer *MainController::getToolContainer () const { return impl->toolContainer; }

/*****************************************************************************/

void MainController::setToolContainer (ToolContainer *value) { impl->toolContainer = value; }

/*****************************************************************************/

void MainController::onKeyPress (unsigned int key)
{
        BOOST_LOG (lg) << "Key pressed : [" << key << "]";
        if (key == GDK_KEY_a) {
                open ("addNodeController");
        }
}

/*****************************************************************************/

void MainController::onSelection (ClutterActorVector *s) { impl->propertiesController->onSelection (s); }

/*****************************************************************************/

PropertiesController *MainController::getPropertiesController () { return impl->propertiesController; }

/*****************************************************************************/

void MainController::onOpen ()
{
        SceneAPI *s = impl->sceneAPI;
        IClutterActor *actor = nullptr;
        actor = s->create ("addNode");
        actor->setPosition (Point (4800, 5000));
        actor->setSize (Dimension (100, 100));
        actor->setVisible (true);
        INodeView *nodeViewA = dynamic_cast<INodeView *> (actor);

        actor = s->create ("copyNode");
        actor->setPosition (Point (5000, 5000));
        actor->setSize (Dimension (100, 100));
        actor->setVisible (true);
        INodeView *nodeViewB = dynamic_cast<INodeView *> (actor);

        // Ports
        Port *pa = nodeViewA->getPorts ()[2].get ();
        Port *pb = nodeViewB->getPorts ()[0].get ();

        // Connection
        actor = s->create ("lineConnector");
        actor->setVisible (true);
        LineConnector *lc = dynamic_cast<LineConnector *> (actor);

        s->connect (lc, pa, pb);
}

/*****************************************************************************/

// TODO remove
IDataFile *ff;
void MainController::setDataFile (IDataFile *f) { ff = f; }

void MainController::onSave ()
{
//        SceneAPI *s = impl->sceneAPI;
        ff->save("file.xml");
}

/*****************************************************************************/

void MainController::setPropertiesController (PropertiesController *p) { impl->propertiesController = p; }
void MainController::setSceneApi (SceneAPI *api) { impl->sceneAPI = api; }

/****************************************************************************/
/* State machine low lewel deps.                                            */
/****************************************************************************/

uint32_t getCurrentMs ()
{
        static uint32_t i;
        return ++i;
}

/*****************************************************************************/

#if 0
void transitionPrint (uint8_t name) { BOOST_LOG (lg) << "State changed to [" << (int)name << "]"; }
#else
void transitionPrint (uint8_t) {}
#endif

/*****************************************************************************/

void transitionIndicate () {}
