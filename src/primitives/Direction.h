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
#include <core/Exception.h>
#include <core/variant/Variant.h>
#include <string>

extern Core::Variant directionFromString (std::string const &s);
extern Direction getOppositeDirection (Direction d);
#endif

#endif // DIRECTION_H
