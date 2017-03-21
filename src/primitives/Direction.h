/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATAFLOW_DIRECTION_H
#define DATAFLOW_DIRECTION_H

enum _Direction { NONE, EAST, SOUTH, WEST, NORTH };
typedef enum _Direction Direction;

#ifdef __cplusplus
extern "C" {
#endif

Direction getOppositeDirection (Direction d);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <core/Exception.h>
#include <core/variant/Variant.h>
#include <string>

extern Core::Variant directionFromString (std::string const &s);
#endif

#endif // DIRECTION_H
