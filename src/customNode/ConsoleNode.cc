/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ConsoleNode.h"
#include "gui/console/ConsoleBuffer.h"
#include <boost/lexical_cast.hpp>
#include <string>

void ConsoleNode::process() { console->append (boost::lexical_cast<std::string> (inputs[0]->get ()) + "\n"); }
