/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CUSTOM_CONSOLENODE_H
#define CUSTOM_CONSOLENODE_H

#include <core/CommonSinks.h>

class __tiliae_reflect__ ConsoleNode : public flow::Console {
public:
        virtual ~ConsoleNode () {}
        virtual void process ();
};

#endif // CONSOLENODE_H
