/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Tool.h"

void ToolContainer::setTools (ToolCategoryVector *value)
{
        tools = value;

        for (ToolCategory *category : *tools) {
                for (Tool *tool : category->tools) {
                        toolMap[tool->name] = tool;
                }
        }
}



