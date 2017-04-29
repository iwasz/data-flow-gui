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

using namespace primitives;

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

                if (++infGuard >= MAX_LOOPS) {
                        v.push_back (state.b.getA ());
                        return v;
                }
        }
}

/*****************************************************************************/

Ray ConnectorSolver::findNewRay (Ray const &ray) const
{
        float max = 0;
        float min = 0;
        Direction dir = NONE;

        for (RuleVector::const_iterator i = rules.cbegin (); i != rules.cend (); ++i) {
                (*i)->run (ray, &min, &max, &dir);
        }

        // If new ray was found.
        if (min == max && dir != NONE) {
                return Ray (advance (ray.getA (), ray.getDirection (), min), dir);
        }

        return ray;
}

/*****************************************************************************/

class AbstractRule : public IRule {
public:
        AbstractRule (SolverState *state) : state (state) {}
        virtual ~AbstractRule () {}

protected:
        SolverState *state;
};

/*****************************************************************************/

class MinDistanceRule : public AbstractRule {
public:
        enum { MIN_DISTANCE = 50 };

        MinDistanceRule (SolverState *state) : AbstractRule (state) {}
        virtual ~MinDistanceRule () {}

        virtual void run (primitives::Ray const &ray, float *max, float *min, Direction *dir) const
        {
                if (ray == state->a) {
                        *min = MIN_DISTANCE;
                }
        }
};

/*****************************************************************************/

ConnectorSolver::ConnectorSolver (primitives::Ray const &a, primitives::Ray const &b) : state (a, b)
{
        rules.push_back (std::unique_ptr<IRule> (new MinDistanceRule (&state)));
}

#if 0
PointVector ConnectorSolver::solve (Ray const &a, Ray const &b)
{
        PointVector v;
        v.push_back (a.getA ());
        Point p;

        // Sum of angles 90 (number of angles 1)
        if ((p = a.isCrossing (b)) || (p = a.isConnection (b))) {
                // Special case : right angle.
                v.push_back (p);
        }

        v.push_back (b.getA ());
        return v;
}
#endif

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
