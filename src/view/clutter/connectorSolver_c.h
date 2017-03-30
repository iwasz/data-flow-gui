/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef C_HEADER_CONNECTORSOLVER_H
#define C_HEADER_CONNECTORSOLVER_H

#include "primitives/Direction.h"

/// Ray or line segment (not a line).
struct _CRay {
        float ax, ay;
        Direction direction;
};

typedef struct _CRay CRay;

struct _CPoint {
        float x, y;
};

typedef struct _CPoint CPoint;

#ifdef __cplusplus
extern "C" {
#endif

void solve (float ax, float ay, Direction aDir, float bx, float by, Direction bDir, CPoint outputPoints[], int *numOfPoints);

#ifdef __cplusplus
}
#endif

#endif // CONNECTORSOLVER_H
