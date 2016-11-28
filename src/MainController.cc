/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MainController.h"
#include <App.h>
#include <Logging.h>
#include <StateMachine.h>
#include <string>

static src::logger_mt &lg = logger::get ();

/*****************************************************************************/

struct IStartPhaseStrategy {
        virtual ~IStartPhaseStrategy () {}
        virtual void run (float x, float y) = 0;
};

struct IDrawPhaseStrategy {
        virtual ~IDrawPhaseStrategy () {}
        virtual void run (float x, float y) = 0;
};

class DashedCircleStrategy : public IDrawPhaseStrategy {
public:
        virtual ~DashedCircleStrategy () {}
        virtual void run (float x, float y) { std::cerr << "kółko " << x << ", " << y << std::endl; }
};

class DashedLineStrategy : public IDrawPhaseStrategy {
public:
        virtual ~DashedLineStrategy () {}
        virtual void run (float x, float y) { std::cerr << "kreseczka " << x << ", " << y << std::endl; }
};

struct IFinishPhaseStrategy {
        virtual ~IFinishPhaseStrategy () {}
        virtual void run (float x1, float y1, float x2, float y2) = 0;
};

class FactoryStrategy : public IFinishPhaseStrategy {
public:
        virtual ~FactoryStrategy () {}
        virtual void run (float x1, float y1, float x2, float y2) { std::cerr << "Factory " << x1 << "," << y1 << "," << x2 << "," << y2 << std::endl; }
};

struct Tool {
        IStartPhaseStrategy *startPhase;
        IDrawPhaseStrategy *drawPhase;
        IFinishPhaseStrategy *finishPhase;
};

typedef std::map<std::string, Tool> ToolMap;

/*****************************************************************************/

enum MachineStates {
        IDLE,          // Nothing is happening
        TOOL_SELECTED, // Toolbox clicked, tool picked.
        DRAW,    // Creating a new object by drawing something
//        END_DRAW       // Creating a new object by drawing something
};

/*****************************************************************************/

struct MainController::Impl {

        Impl () : inputQueue (STRING_QUEUE_SIZE), machine (&inputQueue) {}

        void configureMachine ();
        void pushMessage (std::string const &msg, void *arg);

        StringQueue inputQueue;
        StateMachine machine;

        // TODO remove
        DashedCircleStrategy dashedCircleStrategy;
        DashedLineStrategy dashedLineStrategy;
        FactoryStrategy factoryStrategy;
        ToolMap tools = { { "add", { nullptr, &dashedCircleStrategy, &factoryStrategy } },
                          { "copy", { nullptr, &dashedCircleStrategy, &factoryStrategy } },
                          { "arc", { nullptr, &dashedLineStrategy, &factoryStrategy } } };

        /*
         * Additional arguments for state machine. Pointer to this struct is passed
         * whenever I need some additional data in the state machine actions.
         */
        struct Arguments {
                std::string tool;
                float x;
                float y;
        } arguments;

        // External state. Used directly in the drawing events (onMove, onRelease).
        std::string currentTool;
        float startX = 0;
        float startY = 0;
        IStartPhaseStrategy *currentStartPhase = nullptr;
        IDrawPhaseStrategy *currentDrawPhase = nullptr;
        IFinishPhaseStrategy *currentFinishPhase = nullptr;
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
                ->transition (TOOL_SELECTED)->when (eq ("selected.tool"))->then ([this] (const char *, void *arg) {
                        Arguments *args = static_cast <Arguments *> (arg);
                        currentTool = args->tool;
                        return true;
                });

        machine.state (TOOL_SELECTED)->entry ([this] (const char *, void *arg) {
                        currentStartPhase = tools[currentTool].startPhase;
                        return true;
                })
                ->exit ([this] (const char *, void *arg) {
                        currentStartPhase = nullptr;
                        return true;
                })
                ->transition (DRAW)->when (eq ("stage.clicked"))->then ([this] (const char *, void *arg) {
                        Arguments *args = static_cast <Arguments *> (arg);
                        startX = args->x;
                        startY = args->y;
                        currentDrawPhase = tools[currentTool].drawPhase;
                        currentFinishPhase = tools[currentTool].finishPhase;
                        return true;
                });

        machine.state (DRAW)
                ->transition (IDLE)->when (eq ("stage.released"))->then ([this] (const char *, void *) {
                        startX = 0;
                        startY = 0;
                        currentTool = "";
                        currentDrawPhase = nullptr;
                        currentFinishPhase = nullptr;
                        return true;
                });

        /* clang-format on */
}

/*****************************************************************************/

MainController::MainController () { impl = new Impl; }

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
//        BOOST_LOG (lg) << "MainController::onNewNodeClicked : " << name;
}

/*****************************************************************************/

void MainController::onStageClicked (float x, float y)
{
//        BOOST_LOG (lg) << "Stage clicked";
        impl->arguments.x = x;
        impl->arguments.y = y;
        impl->pushMessage ("stage.clicked", &impl->arguments);

        if (impl->currentStartPhase) {
                impl->currentStartPhase->run (x, y);
        }
}

/*****************************************************************************/

void MainController::onReleased (float x, float y)
{
//        BOOST_LOG (lg) << "Released";
        impl->pushMessage ("stage.released", &impl->arguments);

        if (impl->currentFinishPhase) {
                impl->currentFinishPhase->run (impl->startX, impl->startY, x, y);
        }
}

/*****************************************************************************/

void MainController::onMotion (float x, float y)
{
        if (impl->currentDrawPhase) {
                impl->currentDrawPhase->run (x, y);
        }
}

/*****************************************************************************/

uint32_t getCurrentMs ()
{
        static uint32_t i;
        return ++i;
}

/*****************************************************************************/

void transitionPrint (uint8_t name) { BOOST_LOG (lg) << "State changed to [" << (int)name << "]"; }

/*****************************************************************************/

void transitionIndicate () {}
