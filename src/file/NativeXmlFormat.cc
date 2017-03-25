/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "NativeXmlFormat.h"
#include "view/CircularNode.h"
#include "view/IClutterActor.h"
#include "view/LineConnector.h"
#include "view/SceneAPI.h"
#include <boost/lexical_cast.hpp>
#include <core/Exception.h>
#include <fstream>
#include <map>

#include <iostream>

struct NativeXmlFormatSave::Impl {
        typedef std::map<INodeView *, unsigned int> NodesForSaveMap;
        NodesForSaveMap nodesForSaveMap;
        unsigned int nodesForSaveNum = 0;

        void reset ();
};

NativeXmlFormatSave::NativeXmlFormatSave () { impl = new Impl; }
NativeXmlFormatSave::~NativeXmlFormatSave () { delete impl; }

/*****************************************************************************/

void NativeXmlFormatSave::load (std::string const &path) {}

/*****************************************************************************/

void NativeXmlFormatSave::save (std::string const &path)
{
        ClutterActorVector const &allActors = sceneApi->getAllActors ();
        std::ofstream file (path);

        for (IClutterActor *actor : allActors) {
                file << actor->visit (this, SAVE);
        }
}

/*****************************************************************************/

std::string NativeXmlFormatSave::clutterActorArguments (IClutterActor *a)
{
        Point p = a->getPosition ();
        Dimension d = a->getSize ();
        return std::string ("position=\"") + boost::lexical_cast<std::string> (p.x) + "," + boost::lexical_cast<std::string> (p.y) + "\" size=\""
                + boost::lexical_cast<std::string> (d.width) + "," + boost::lexical_cast<std::string> (d.height) + "\" fill=\""
                + boost::lexical_cast<std::string> (a->isFill ()) + "\" fillColor=\"" + Color::toString (a->getFillColor ()) + "\" "
                + clutterActorArgumentsStroke (a);
}

/*****************************************************************************/

std::string NativeXmlFormatSave::clutterActorArgumentsStroke (IClutterActor *a)
{
        return "strokeWidth=\"" + boost::lexical_cast<std::string> (a->getStrokeWidth ()) + "\" strokeColor=\"" + Color::toString (a->getStrokeColor ())
                + "\" strokeDash=\"" + boost::lexical_cast<std::string> (a->getStrokeDash ()) + "\" ";
}

/*****************************************************************************/

std::string NativeXmlFormatSave::onButton (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<button/>\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormatSave::onCircle (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<" + a->getId () + " " + clutterActorArguments (a) + "/>\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormatSave::onCircularNode (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                CircularNode *cn = dynamic_cast<CircularNode *> (a);
                INodeView *inv = dynamic_cast<INodeView *> (cn);
                unsigned int myIdx = impl->nodesForSaveNum++;
                impl->nodesForSaveMap[inv] = myIdx;
                std::cerr << (void *)inv << "=" << myIdx << std::endl;

                return std::string ("<") + a->getId () + " index=\"" + boost::lexical_cast<std::string> (myIdx) + "\" " + clutterActorArguments (a) + "font=\""
                        + cn->getFont () + "\" fontColor=\"" + Color::toString (cn->getFontColor ()) + "\" />\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormatSave::onLine (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                Line *l = dynamic_cast<Line *> (a);
                return "<" + a->getId () + " " + clutterActorArgumentsStroke (a) + " pointA=\"" + boost::lexical_cast<std::string> (l->getPointA ().x) + ","
                        + boost::lexical_cast<std::string> (l->getPointA ().y) + "\" pointB=\"" + boost::lexical_cast<std::string> (l->getPointB ().x) + ","
                        + boost::lexical_cast<std::string> (l->getPointB ().y) + "\" />\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormatSave::onLineConnector (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                LineConnector *lc = dynamic_cast<LineConnector *> (a);

                if (!lc->getAnchorA () || !lc->getAnchorA ()->getPort () || !lc->getAnchorB () || !lc->getAnchorB ()->getPort ()) {
                        throw Core::Exception ("NativeXmlFormat::onLineConnector : connector not connected");
                }

                Port *pa = lc->getAnchorA ()->getPort ();
                Port *pb = lc->getAnchorB ()->getPort ();

                if (!pa || !pb) {
                        throw Core::Exception ("NativeXmlFormat::onLineConnector : no port");
                }

                unsigned int paNum = pa->getViewNumber ();
                unsigned int pbNum = pb->getViewNumber ();

                unsigned int nvaNum = impl->nodesForSaveMap.at (pa->getNodeView ());
                unsigned int nvbNum = impl->nodesForSaveMap.at (pb->getNodeView ());

                std::cerr << (void *)pa->getNodeView () << "=" << nvaNum << " " << (void *)pb->getNodeView () << "=" << nvbNum << std::endl;

                return "<" + a->getId () + " " + clutterActorArgumentsStroke (a) + " objA=\"" + boost::lexical_cast<std::string> (nvaNum) + "\" portA=\""
                        + boost::lexical_cast<std::string> (paNum) + "\"" + " objB=\"" + boost::lexical_cast<std::string> (nvbNum) + "\" portB=\""
                        + boost::lexical_cast<std::string> (pbNum) + "\" />\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormatSave::onConnector (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<" + a->getId () + " " + clutterActorArgumentsStroke (a) + "/>\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormatSave::onRectangle (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<" + a->getId () + " " + clutterActorArguments (a) + "/>\n";
        }
        else {
        }
}

/*****************************************************************************/

void NativeXmlFormatSave::Impl::reset ()
{
        nodesForSaveMap.clear ();
        nodesForSaveNum = 0;
}
