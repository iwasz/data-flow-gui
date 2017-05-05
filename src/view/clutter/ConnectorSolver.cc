/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ConnectorSolver.h"
#include "connectorSolver_c.h"
#include "primitives/PrimitiveOperations.h"
#include <cmath>

using namespace primitives;
enum { MIN_DISTANCE_BEND = 50, MIN_DISTANCE_RAYS = 100 };

PointVector ConnectorSolver::solve ()
{
        PointVector v;
        v.push_back (state.a.getA ());

        Ray currentRay = state.a;
        int infGuard = 0;

        while (true) {
                if (Point p = currentRay.isCrossing (state.b)) {
                        v.push_back (p);
                        v.push_back (state.b.getA ());
                        return v;
                }

                currentRay = findNewRay (currentRay);

                if (currentRay.getDirection () != NONE) {
                        v.push_back (currentRay.getA ());
                }

                if (++infGuard >= MAX_LOOPS) {
                        v.push_back (state.b.getA ());
                        return v;
                }
        }
}

/*****************************************************************************/

Ray ConnectorSolver::findNewRay (Ray const &ray) const
{
        //        float max = 0;
        float d = 0;
        Direction dir = NONE;

        for (RuleVector::const_iterator i = rules.cbegin (); i != rules.cend (); ++i) {
                (*i)->run (&state, ray, &d, &dir);
        }

        // If new ray was found.
        if (/*d == max && */ dir != NONE) {
                return Ray (advance (ray.getA (), ray.getDirection (), d), dir);
        }

        return Ray (Point (), NONE);
}

/*****************************************************************************/

Direction direction (SolverState const *state, primitives::Ray const &currentRay)
{
        if (currentRay.isVertical ()) { // Consider x.
                return (state->b.getA ().x >= currentRay.getA ().x) ? (EAST) : (WEST);
        }
        else if (currentRay.isHorizontal ()) {
                return (state->b.getA ().y >= currentRay.getA ().y) ? (SOUTH) : (NORTH);
        }

        return NONE;
}

/*****************************************************************************/

struct AlwaysTrueCheck : public ICheck {
        virtual ~AlwaysTrueCheck () {}
        virtual bool check (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const { return true; }
};

class OrCheck : public ICheck {
public:
        OrCheck (ICheck *a, ICheck *b) : a (a), b (b) {}
        virtual ~OrCheck () {}
        virtual bool check (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                return a->check (state, currentRay, d, dir) || b->check (state, currentRay, d, dir);
        }

private:
        ICheck *a;
        ICheck *b;
};

class AndCheck : public ICheck {
public:
        AndCheck (ICheck *a, ICheck *b) : a (a), b (b) {}
        virtual ~AndCheck () {}
        virtual bool check (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                return a->check (state, currentRay, d, dir) && b->check (state, currentRay, d, dir);
        }

private:
        ICheck *a;
        ICheck *b;
};

class NotCheck : public ICheck {
public:
        NotCheck (ICheck *a) : a (a) {}
        virtual ~NotCheck () {}

        virtual bool check (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                return !a->check (state, currentRay, d, dir);
        }

private:
        ICheck *a;
};

/**
 * We are at the first ray which origins from node A.
 */
// struct CurrentRayIsACheck : public ICheck {
//        virtual ~CurrentRayIsACheck () {}
//        virtual bool check (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const { return (currentRay == state->a); }
//};

struct RaysSameDir : public ICheck {
        virtual ~RaysSameDir () {}
        virtual bool check (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                return currentRay.getDirection () == state->b.getDirection ();
        }
};

struct RaysPerpendicular : public ICheck {
        virtual ~RaysPerpendicular () {}
        virtual bool check (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                return currentRay.isPerpendicularTo (state->b);
        }
};

struct RayDistanceGreaterCheck : public ICheck {
        virtual ~RayDistanceGreaterCheck () {}
        virtual bool check (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
//                if (currentRay.isParallelTo (state->b)) {
                        if (currentRay.isVertical ()) {
                                return fabs (currentRay.getA ().x - state->b.getA ().x) > MIN_DISTANCE_RAYS;
                        }
                        else {
                                return fabs (currentRay.getA ().y - state->b.getA ().y) > MIN_DISTANCE_RAYS;
                        }
//                }
//                else {
//                        if (currentRay.isVertical ()) {
//                                return fabs (currentRay.getA ().x - state->b.getA ().x) > MIN_DISTANCE_RAYS;
//                        }
//                        else {
//                                return fabs (currentRay.getA ().y - state->b.getA ().y) > MIN_DISTANCE_RAYS;
//                        }
//                }
        }
};

struct ProjectionsOverlapCheck : public ICheck {
        virtual ~ProjectionsOverlapCheck () {}

        virtual bool check (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                Ray const &b = state->b;

                if (b.isPerpendicularTo (currentRay)) {
                        return false;
                }

                if (b.isVertical ()) {
                        float ba = b.getA ().y;
                        float bb = b.getB ().y;
                        float aa = currentRay.getA ().y;
                        float ab = currentRay.getB ().y;

                        return (ba >= aa && ba < ab) || (bb >= aa && bb < ab) || (aa >= ba && aa < bb) || (ab >= ba && ab < bb);
                }
                else if (b.isHorizontal ()) {
                        float ba = b.getA ().x;
                        float bb = b.getB ().x;
                        float aa = currentRay.getA ().x;
                        float ab = currentRay.getB ().x;

                        return (ba >= aa && ba < ab) || (bb >= aa && bb < ab) || (aa >= ba && aa < bb) || (ab >= ba && ab < bb);
                }

                return false;
        }
};

/*****************************************************************************/

class AbstractRule : public IRule {
public:
        AbstractRule (ICheck *check) : check (check) {}
        virtual ~AbstractRule () { /*delete check;*/}

        void run (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                if (check && check->check (state, currentRay, d, dir)) {
                        runImpl (state, currentRay, d, dir);
                }
        }

        virtual void runImpl (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const = 0;

private:
        ICheck *check;
};

struct A3Rule : public AbstractRule {
public:
        A3Rule (ICheck *check) : AbstractRule (check) {}
        virtual ~A3Rule () {}

        virtual void runImpl (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                *dir = direction (state, currentRay);

                if (currentRay.isHorizontal ()) {
                        if (currentRay.getA ().x < state->b.getA ().x) {
                                if (currentRay.getDirection () == EAST) {
                                        *d = state->b.getA ().x - currentRay.getA ().x + MIN_DISTANCE_BEND;
                                }
                                else {
                                        *d = MIN_DISTANCE_BEND;
                                }
                        }
                        else {
                                if (currentRay.getDirection () == EAST) {
                                        *d = MIN_DISTANCE_BEND;
                                }
                                else {
                                        *d = currentRay.getA ().x - state->b.getA ().x + MIN_DISTANCE_BEND;
                                }
                        }
                }
                else {
                        if (currentRay.getA ().y < state->b.getA ().y) {
                                if (currentRay.getDirection () == SOUTH) {
                                        *d = state->b.getA ().y - currentRay.getA ().y + MIN_DISTANCE_BEND;
                                }
                                else {
                                        *d = MIN_DISTANCE_BEND;
                                }
                        }
                        else {
                                if (currentRay.getDirection () == SOUTH) {
                                        *d = MIN_DISTANCE_BEND;
                                }
                                else {
                                        *d = currentRay.getA ().y - state->b.getA ().y + MIN_DISTANCE_BEND;
                                }
                        }
                }
        }
};

//#include <iostream>

struct B3Rule : public AbstractRule {
        B3Rule (ICheck *check) : AbstractRule (check) {}
        virtual ~B3Rule () {}

        virtual void runImpl (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                //                std::cerr << "3B" << std::endl;
                *dir = direction (state, currentRay);

                if (currentRay.isHorizontal ()) {
                        *d = fabs (state->b.getA ().x - currentRay.getA ().x) / 2.0;
                }
                else {
                        *d = fabs (state->b.getA ().y - currentRay.getA ().y) / 2.0;
                }
        }
};

class MinDistanceRule : public AbstractRule {
public:
        MinDistanceRule (ICheck *check) : AbstractRule (check) {}
        virtual ~MinDistanceRule () {}

        virtual void runImpl (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const { *d = MIN_DISTANCE_BEND; }
};

/*****************************************************************************/

class DirectionRule : public AbstractRule {
public:
        DirectionRule (ICheck *check) : AbstractRule (check) {}
        virtual ~DirectionRule () {}

        virtual void runImpl (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                *dir = direction (state, currentRay);
        }
};

/*****************************************************************************/

bool isChanceOfCrossing (Ray const &current, Ray const &b0)
{
        Ray b = Ray (advance (b0.getA (), b0.getDirection (), MIN_DISTANCE_BEND), b0.getDirection ());

        if (b.isPerpendicularTo (current)) {
                return false;
        }

        if (b.isVertical ()) {
                return (b.getA ().y >= current.getA ().y && b.getA ().y < current.getB ().y)
                        || (b.getB ().y >= current.getA ().y && b.getB ().y < current.getB ().y);
        }
        else if (b.isHorizontal ()) {
                return (b.getA ().x >= current.getA ().x && b.getA ().x < current.getB ().x)
                        || (b.getB ().x >= current.getA ().x && b.getB ().x < current.getB ().x);
        }

        return false;
}

class HalfDistanceRule : public AbstractRule {
public:
        HalfDistanceRule (ICheck *check) : AbstractRule (check) {}
        virtual ~HalfDistanceRule () {}

        virtual void runImpl (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const
        {
                // ?
                if (!isChanceOfCrossing (currentRay, state->b)) {
                        return;
                }

                if (currentRay.isVertical ()) {
                        *d = fabs (currentRay.getA ().y - state->b.getA ().y) / 2;
                }
                else if (currentRay.isHorizontal ()) {
                        *d = fabs (currentRay.getA ().x - state->b.getA ().x) / 2;
                }
        }
};

/*****************************************************************************/

class ExtendForCrossingRule : public AbstractRule {
public:
        ExtendForCrossingRule (ICheck *check) : AbstractRule (check) {}
        virtual ~ExtendForCrossingRule () {}

        virtual void runImpl (SolverState const *state, primitives::Ray const &currentRay, float *d, Direction *dir) const {}
};

/*****************************************************************************/

ConnectorSolver::ConnectorSolver (primitives::Ray const &a, primitives::Ray const &b) : state (a, b)
{
        static RaysSameDir raysSameDir;
        static RayDistanceGreaterCheck rayDistanceGreater;
        static ProjectionsOverlapCheck projectionsOverlapCheck;

        {
                static AndCheck andCheck (&raysSameDir, &rayDistanceGreater);
                static A3Rule a3Rule (&andCheck);
                rules.push_back (&a3Rule);
        }

        {
                static NotCheck raysDifferentDirs (&raysSameDir);
                static AndCheck andCheck (&raysDifferentDirs, &projectionsOverlapCheck);
                static B3Rule b3Rule (&andCheck);
                rules.push_back (&b3Rule);
        }

        {
                static RaysPerpendicular raysPerpendicular;
                static AndCheck andCheck (&raysPerpendicular, &rayDistanceGreater);
                static A3Rule a3Rule (&andCheck);
                rules.push_back (&a3Rule);
        }

        // rules.push_back (std::unique_ptr<IRule> (new MinDistanceRule (new CurrentRayIsACheck)));
        // rules.push_back (std::unique_ptr<IRule> (new HalfDistanceRule (&state)));
        // rules.push_back (std::unique_ptr<IRule> (new DirectionRule (new AlwaysTrueCheck)));
        // rules.push_back (std::unique_ptr<IRule> (new ExtendForCrossingRule (&state)));
}

/*****************************************************************************/

extern "C" void solve (float ax, float ay, Direction aDir, float bx, float by, Direction bDir, CPoint outputPoints[], int *numOfPoints)
{
        ConnectorSolver solver (Ray (Point (ax, ay), aDir), Ray (Point (bx, by), bDir));
        PointVector v = solver.solve ();

        *numOfPoints = v.size ();
        int i = 0;

        for (Point const &p : v) {
                outputPoints[i].x = p.x;
                outputPoints[i].y = p.y;
                ++i;
        }
}
