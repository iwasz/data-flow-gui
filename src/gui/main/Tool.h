/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DRAWING_TOOL_H
#define DRAWING_TOOL_H

#include <ReflectionParserAnnotation.h>
#include <map>
#include <string>
#include <vector>

struct IDrawStrategy;
struct IFactoryStrategy;
struct ISelectorStrategy;

/**
 * Represents one tool that can be picked from left side toolbar.
 */
struct __tiliae_reflect__ Tool {
        IDrawStrategy *drawStrategy = nullptr;
        IFactoryStrategy *factoryStrategy = nullptr;
        ISelectorStrategy *selectorStrategy = nullptr;
        std::string name;
        std::string description;
        std::string imagePath;
};

typedef __tiliae_reflect__ std::vector<Tool *> ToolVector;

/**
 * Tools are groupped in categories.
 */
struct __tiliae_reflect__ ToolCategory {
        std::string name;
        std::string description;
        ToolVector tools;
};

typedef __tiliae_reflect__ std::vector<ToolCategory *> ToolCategoryVector;
typedef std::map<std::string, Tool *> ToolMap;

/**
 * @brief The ToolContainer class
 */
class __tiliae_reflect__ ToolContainer {
public:
        ToolCategoryVector const *getTools () const { return tools; }
        void setTools (ToolCategoryVector *value);

        ToolMap const &getToolMap () const __tiliae_no_reflect__ { return toolMap; }
        ToolMap &getToolMap () __tiliae_no_reflect__ { return toolMap; }

private:
        ToolCategoryVector *tools = nullptr;
        ToolMap toolMap;
};

#endif // TOOL_H
