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
#include <ReflectionParserAnnotation.h>
#include <controller/AbstractController.h>
#include <map>
#include <string>

#if 1
#include "view/CircularNode.h"
#include "view/LineConnector.h"
#endif

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
        void onButtonPress (float x, float y);
        void onButtonRelease (float x, float y);
        void onMotion (float x, float y);

        ToolMap const &getTools () const { return tools; }
        void setTools (const ToolMap &value) { tools = value; }

#if 1
        void onDummyMethod ();
        CircularNode *na;
        CircularNode *nb;
        LineConnector *lc;
#endif

private:

        ToolMap tools;

        struct Impl;
        Impl *impl;
};

#endif /* MainController_H_ */
