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
#include "MoveStrategy.h"
#include "view/Rectangle.h"
#include "view/ScaleLayer.h"
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
        MOVE,          /// Moving an object around.
        STAGE_MOVE     /// Moving the viewport.
};

/*****************************************************************************/

struct MainController::Impl {

        Impl (ToolMap *t) : inputQueue (STRING_QUEUE_SIZE), machine (&inputQueue), tools (t) {}
        ~Impl () {}

        void configureMachine ();
        void pushMessage (std::string const &msg, void *arg);

        StringQueue inputQueue;
        StateMachine machine;
        ToolMap *tools;
        MoveStrategy moveStrategy;
        flow::Program *program = nullptr;
        bool runProgram = false;
        Rectangle *rectangularSelector = nullptr;
        Stage *stage = nullptr;
        Event event; // Tempporary for some handlers.
        ClutterActorVector *selectedActors = nullptr;

        /// Additional state. Used directly in the drawing events (onMove, onRelease).
        struct {
                /// Name of curently selected tool (arc, node etc).
                std::string currentTool;
                /// Draw strategy draws shapes just prior to actual object creation.
                IDrawStrategy *currentDrawStrategy = nullptr;
                /// This strategy creates the object we are drawing.
                IFactoryStrategy *currentFactoryStrategy = nullptr;
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
                        vars.currentFactoryStrategy = nullptr;
                        return true;
                })
                ->transition (TOOL_SELECTED)->when (eq ("selected.tool"))
                ->transition (MOVE)->when (eq ("stage.enter"))
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
                        return true;
                })
                ->transition (DRAW)->when (eq ("stage.press"))->then ([this] (const char *, void *arg) {
                        vars.currentTool = "select";
                        vars.currentDrawStrategy = (*tools)[vars.currentTool].drawStrategy;
                        vars.currentFactoryStrategy = (*tools)[vars.currentTool].factoryStrategy;
                        vars.currentSelectorStrategy = (*tools)[vars.currentTool].selectorStrategy;
                        vars.currentDrawStrategy->onButtonPress (*static_cast <Event *> (arg));
                        return true;
                });


        /*---------------------------------------------------------------------------*/

        machine.state (TOOL_SELECTED)
                ->entry ([this] (const char *, void *arg) {
                        Event *args = static_cast <Event *> (arg);
                        vars.currentTool = args->tool;

                        if (tools->find (vars.currentTool) == tools->end ()) {
                                throw Core::Exception ("No such tool : [" + vars.currentTool + "]");
                        }

                        vars.currentDrawStrategy = (*tools)[vars.currentTool].drawStrategy;
                        vars.currentFactoryStrategy = (*tools)[vars.currentTool].factoryStrategy;
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

                        IClutterActor *a = nullptr;
                        if (vars.currentFactoryStrategy) {
                                Core::Variant v = vars.currentFactoryStrategy->run (*args);
                                a = ocast <IClutterActor *> (v);
                        }

                        vars.currentDrawStrategy->onObjectCreated (a);

                        if (a) {
                                a->setVisible (true);
                        }

                        return true;
                });

        /*---------------------------------------------------------------------------*/

        machine.state (MOVE)
                ->entry ([this] (const char *, void *arg) {
                        moveStrategy.onEnter (*static_cast <Event *> (arg));
                        return true;
                })
                ->transition (IDLE)->when (eq ("stage.leave"))->then ([this] (const char *, void *arg) {
                        moveStrategy.onLeave (*static_cast <Event *> (arg));
                        return true;
                });

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

MainController::MainController () { impl = new Impl (&tools); }

/*****************************************************************************/

MainController::~MainController () { delete impl; }

/*****************************************************************************/

void MainController::init () { impl->configureMachine (); }

/*****************************************************************************/

std::string MainController::onStart () { return "mainView"; }

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

void MainController::pushMessage (std::string const &msg, Event *event) { impl->pushMessage (msg, event); }

/****************************************************************************/
/* Drawing events                                                           */
/****************************************************************************/

void MainController::onNewNodeToolClicked (std::string const &name)
{
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

void MainController::onProgramRun (bool run) { impl->runProgram = run; }

/*****************************************************************************/

Rectangle *MainController::getRectangularSelector () const { return impl->rectangularSelector; }

/*****************************************************************************/

void MainController::setRectangularSelector (Rectangle *value) { impl->rectangularSelector = value; }

/*****************************************************************************/

ClutterActorVector *MainController::getSelectedActors () { return impl->selectedActors; }

/*****************************************************************************/

void MainController::setSelectedActors (ClutterActorVector *value) { impl->selectedActors = value; }

/*****************************************************************************/

Stage *MainController::getStage () const { return impl->stage; }

/*****************************************************************************/

void MainController::setStage (Stage *value) { impl->stage = value; }

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
