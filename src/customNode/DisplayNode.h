/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DISPLAY_NODE_H
#define DISPLAY_NODE_H

#include <core/CommonSinks.h>

class __tiliae_reflect__ DisplayNode : public flow::Sink {
public:
        virtual ~DisplayNode () {}
        virtual void process ();
        virtual void setObserver (flow::IFlowObserver *o) { this->observer = o; }

private:
        flow::IFlowObserver *observer = nullptr;
};

#endif // CONSOLENODE_H
