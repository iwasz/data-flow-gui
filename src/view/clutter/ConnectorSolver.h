/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONNECTORSOLVER_H
#define CONNECTORSOLVER_H

#include "primitives/Direction.h"
#include "primitives/Geometry.h"
#include "primitives/Ray.h"

struct SolverState {
        SolverState (primitives::Ray const &a, primitives::Ray const &b) : a (a), b (b) {}
        primitives::Ray a;
        primitives::Ray b;
};

struct IRule {
        virtual ~IRule () {}
        virtual void run (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const = 0;
};

struct ICheck {
        virtual ~ICheck () {}
        virtual bool check (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const = 0;
};

using RuleVector = std::vector<IRule *>;

/**
 * Class forcomputing a shape of segmented connector connecting 2 points like
 * in Libre Office draw or Visio. Implementing this was way, way harder than I
 * expected :(
 */
class ConnectorSolver {
public:
        ConnectorSolver (primitives::Ray const &a, primitives::Ray const &b);
        primitives::PointVector solve ();

private:
        primitives::Ray findNewRay (primitives::Ray const &ray) const;

        const int MAX_LOOPS = 10;

private:
        SolverState state;
        RuleVector rules;
};

#endif // CONNECTORSOLVER_H
