/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractRoutable.h"

/*****************************************************************************/

AbstractRoutable::~AbstractRoutable ()
{
        if (router && shapeRef) {
                router->deleteShape (shapeRef);
        }
}

/*****************************************************************************/

void AbstractRoutable::init (primitives::Point const &p, primitives::Dimension const &d0, IRoutableObserver *o)
{
        if (isRouting () && router) {
                primitives::Dimension d = d0;
#ifdef ROUTING_DEBUGS
                std::cerr << "init : " << p << ", " << d << ", " << typeid (*this).name () << std::endl;
#endif

                if (!shapeRef) {
                        if (d.width <= 0) {
                                d.width = 1;
                        }

                        if (d.height <= 0) {
                                d.height = 1;
                        }

                        Avoid::Rectangle rectangle (Avoid::Point (p.x, p.y), Avoid::Point (p.x + d.width, p.y + d.height));
                        shapeRef = new Avoid::ShapeRef (router, rectangle);
                }
        }

        observer = o;
}

/*****************************************************************************/

primitives::Point AbstractRoutable::getPosition () const
{
        if (!shapeRef) {
                return primitives::Point ();
        }

        Avoid::Rectangle const &r = dynamic_cast<Avoid::Rectangle const &> (shapeRef->polygon ());
        return primitives::Point (r.at (0).x, r.at (0).y);
}

/*****************************************************************************/

void AbstractRoutable::setPosition (primitives::Point const &p)
{

        if (isRouting () && router) {
                primitives::Point p1 = getPosition ();
                primitives::Dimension d = p - p1;
#ifdef ROUTING_DEBUGS
                std::cerr << "setPosition : " << d << ", " << typeid (*this).name () << std::endl;
#endif
                router->moveShape (shapeRef, d.width, d.height);
        }
}

/*****************************************************************************/

void AbstractRoutable::move (primitives::Dimension const &d)
{
        if (isRouting () && router) {
#ifdef ROUTING_DEBUGS
                std::cerr << "move : " << d << ", " << typeid (*this).name () << std::endl;
#endif
                router->moveShape (shapeRef, d.width, d.height);
        }
}

/*****************************************************************************/

void AbstractRoutable::setSize (const primitives::Dimension &d0)
{
        if (isRouting () && router) {
                primitives::Point p = getPosition ();
                primitives::Dimension d = d0;

                if (d.width <= 0) {
                        d.width = 1;
                }

                if (d.height <= 0) {
                        d.height = 1;
                }

                Avoid::Rectangle rectangle (Avoid::Point (p.x, p.y), Avoid::Point (p.x + d.width, p.y + d.height));
#ifdef ROUTING_DEBUGS
                std::cerr << "setSize : " << p << ", " << d << std::endl;
#endif
                router->moveShape (shapeRef, rectangle);
        }
}
