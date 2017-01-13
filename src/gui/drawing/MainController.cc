/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MainController.h"
#include "view/IClutterActor.h"
#include <App.h>
#include <Logging.h>
#include <StateMachine.h>

static src::logger_mt &lg = logger::get ();

/*****************************************************************************/

enum MachineStates {
        IDLE,          // Nothing is happening
        TOOL_SELECTED, // Toolbox clicked, tool picked.
        DRAW,          // Creating a new object by drawing something
        //        END_DRAW       // Creating a new object by drawing something
};

/*****************************************************************************/

struct MainController::Impl {

        Impl (ToolMap *t) : inputQueue (STRING_QUEUE_SIZE), machine (&inputQueue), tools (t) {}

        void configureMachine ();
        void pushMessage (std::string const &msg, void *arg);

        StringQueue inputQueue;
        StateMachine machine;
        ToolMap *tools;

        /*
         * Additional arguments for state machine. Pointer to this struct is passed
         * whenever I need some additional data in the state machine actions.
         */
        struct Arguments {
                std::string tool;
                Point p;
                Core::Object *object;
        } arguments;

        /// Additional state. Used directly in the drawing events (onMove, onRelease).
        struct {
                /// Name of curently selected tool (arc, node etc).
                std::string currentTool;
                /// Coordinates of first point of current "gesture".
//                Point startPoint;
                /// Object (already on stage, usually an actor) we clicked when started drawing our new object.
//                Core::Object *startObject;
                /// Draw strategy draws shapes just prior to actual object creation.
                IDrawStrategy *currentDrawStrategy = nullptr;
                /// This strategy creates the object we are drawing.
                IFactoryStrategy *currentFactoryStrategy = nullptr;
        } vars;

        // Maybe other name and element type?
        ClutterActorVector actors;
};

/*****************************************************************************/

void MainController::Impl::pushMessage (std::string const &m, void *arg)
{
        inputQueue.push_back ();
        StringQueue::Element *el = inputQueue.back ();
        strncpy (el->data, m.c_str (), STRING_QUEUE_BUFFER_SIZE);
        el->arg = arg;
}

/*****************************************************************************/

void MainController::Impl::configureMachine ()
{
        /* clang-format off */
        machine.state (IDLE, State::INITIAL)
                ->entry ([this] (const char *, void *arg) {
                        // vars.startPoint = Point ();
                        vars.currentTool = "";
                        vars.currentDrawStrategy = nullptr;
                        vars.currentFactoryStrategy = nullptr;
                        return true;
                })
                ->transition (TOOL_SELECTED)->when (eq ("selected.tool"));

        machine.state (TOOL_SELECTED)
                ->entry ([this] (const char *, void *arg) {
                        Arguments *args = static_cast <Arguments *> (arg);
                        vars.currentTool = args->tool;

                        if (tools->find (vars.currentTool) == tools->end ()) {
                                throw Core::Exception ("No such tool : [" + vars.currentTool + "]");
                        }

                        vars.currentDrawStrategy = (*tools)[vars.currentTool].drawStrategy;
                        vars.currentFactoryStrategy = (*tools)[vars.currentTool].factoryStrategy;
                        return true;
                })
                ->transition (DRAW)->when (eq ("stage.press"))->then ([this] (const char *, void *arg) {
                        Arguments *args = static_cast <Arguments *> (arg);
                        vars.currentDrawStrategy->onButtonPress (args->p, args->object);
                        return true;
                });

        machine.state (DRAW)
                ->transition (DRAW)->when (eq ("stage.motion"))->then ([this] (const char *, void *arg) {
                        Arguments *args = static_cast <Arguments *> (arg);
                        vars.currentDrawStrategy->onMotion (args->p, args->object);
                        return true;
                })
                ->transition (IDLE)->when (eq ("stage.release"))->then ([this] (const char *, void *arg) {
                        Arguments *args = static_cast <Arguments *> (arg);

                        if (!vars.currentDrawStrategy->onButtonRelease (args->p, args->object)) {
                                return true;
                        }

                        Core::Variant v = vars.currentFactoryStrategy->run (/*vars.startX, vars.startY, args->x, args->y*/);
                        IClutterActor *a = ocast <IClutterActor *> (v);
                        vars.currentDrawStrategy->reshape (a);
                        a->setVisible (true);
                        actors.push_back (std::shared_ptr <IClutterActor> (a));
                        return true;
                });

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

void MainController::onIdle () { impl->machine.run (); }

/****************************************************************************/
/* Drawing events                                                           */
/****************************************************************************/

void MainController::onNewNodeToolClicked (std::string const &name)
{
        impl->arguments.tool = name;
        impl->pushMessage ("selected.tool", &impl->arguments);
}

/*****************************************************************************/

void MainController::onButtonPress (Point p, Object *o)
{
        impl->arguments.p = p;
        impl->arguments.object = o;
        impl->pushMessage ("stage.press", &impl->arguments);
}

/*****************************************************************************/

void MainController::onButtonRelease (Point p, Object *o)
{
        impl->arguments.p = p;
        impl->arguments.object = o;
        impl->pushMessage ("stage.release", &impl->arguments);
}

/*****************************************************************************/

void MainController::onMotion (Point p, Object *o)
{
        impl->arguments.p = p;
        impl->arguments.object = o;
        impl->pushMessage ("stage.motion", &impl->arguments);
}

/*****************************************************************************/

void MainController::onDummyMethod ()
{
        lc->connect (na->getAnchor (2), IConnector::A);
        lc->connect (nb->getAnchor (0), IConnector::B);
}

/****************************************************************************/
/* State machine low lewel deps.                                            */
/****************************************************************************/

uint32_t getCurrentMs ()
{
        static uint32_t i;
        return ++i;
}

/*****************************************************************************/

// void transitionPrint (uint8_t name) { BOOST_LOG (lg) << "State changed to [" << (int)name << "]"; }
void transitionPrint (uint8_t) {}

/*****************************************************************************/

void transitionIndicate () {}
