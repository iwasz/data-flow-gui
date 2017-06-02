/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DisplayNode.h"
#include "gui/console/ConsoleBuffer.h"
#include <boost/lexical_cast.hpp>
#include <string>

void DisplayNode::process() { observer->onValueChange (Core::Variant (inputs[0]->get ())); }
