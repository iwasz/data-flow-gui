/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDFNODE_H
#define IDFNODE_H

#include <ReflectionParserAnnotation.h>
#include <vector>
#include <memory>
#include <core/Object.h>

/**
 * Represents (in most abstract way) single node of a dataflow program.
 * Consists of a View (for displaying the node), and flow::INode  which
 * implements action.
 */
struct IDFNode : public Core::Object {
        virtual ~IDFNode () {}
};

typedef __tiliae_reflect__ std::vector <std::shared_ptr <IDFNode>> DFNodeVector;

#endif // IDFNODE_H
