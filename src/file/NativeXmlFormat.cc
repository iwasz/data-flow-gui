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
        typedef std::map<INodeView *, unsigned int> NodesMap;
        NodesMap nodesMap;
        unsigned int nodesNum = 0;
        std::ofstream *file;

        void reset ();
};

/*****************************************************************************/

NativeXmlFormatSave::NativeXmlFormatSave () { impl = new Impl; }
NativeXmlFormatSave::~NativeXmlFormatSave () { delete impl; }

/*****************************************************************************/

void NativeXmlFormatSave::load (std::string const &path) {}

/*****************************************************************************/

void NativeXmlFormatSave::save (std::string const &path)
{
        ClutterActorVector const &allActors = sceneApi->getAllActors ();
        std::ofstream file (path);
        impl->file = &file;

        file << "<flow>\n";

        for (IClutterActor *actor : allActors) {
                actor->visit (this);
        }

        file << "</flow>" << std::endl;
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

void NativeXmlFormatSave::onButton (IClutterActor *a) { *impl->file << "<" + a->getId () + " " + clutterActorArguments (a) + "/>\n"; }

/*****************************************************************************/

void NativeXmlFormatSave::onCircle (IClutterActor *a) { *impl->file << "<" + a->getId () + " " + clutterActorArguments (a) + "/>\n"; }

/*****************************************************************************/

void NativeXmlFormatSave::onCircularNode (IClutterActor *a)
{
        CircularNode *cn = dynamic_cast<CircularNode *> (a);
        INodeView *inv = dynamic_cast<INodeView *> (cn);
        unsigned int myIdx = impl->nodesNum++;
        impl->nodesMap[inv] = myIdx;
        std::cerr << (void *)inv << "=" << myIdx << std::endl;

        *impl->file << std::string ("<") + a->getId () + " index=\"" + boost::lexical_cast<std::string> (myIdx) + "\" " + clutterActorArguments (a) + "font=\""
                        + cn->getFont () + "\" fontColor=\"" + Color::toString (cn->getFontColor ()) + "\" />\n";
}

/*****************************************************************************/

void NativeXmlFormatSave::onLine (IClutterActor *a)
{
        Line *l = dynamic_cast<Line *> (a);
        *impl->file << "<" + a->getId () + " " + clutterActorArgumentsStroke (a) + " pointA=\"" + boost::lexical_cast<std::string> (l->getPointA ().x) + ","
                        + boost::lexical_cast<std::string> (l->getPointA ().y) + "\" pointB=\"" + boost::lexical_cast<std::string> (l->getPointB ().x) + ","
                        + boost::lexical_cast<std::string> (l->getPointB ().y) + "\" />\n";
}

/*****************************************************************************/

void NativeXmlFormatSave::onLineConnector (IClutterActor *a)
{
        AbstractConnector *lc = dynamic_cast<AbstractConnector *> (a);

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

        unsigned int nvaNum = impl->nodesMap.at (pa->getNodeView ());
        unsigned int nvbNum = impl->nodesMap.at (pb->getNodeView ());

        std::cerr << (void *)pa->getNodeView () << "=" << nvaNum << " " << (void *)pb->getNodeView () << "=" << nvbNum << std::endl;

        *impl->file << "<" + a->getId () + " " + clutterActorArgumentsStroke (a) + " objA=\"" + boost::lexical_cast<std::string> (nvaNum) + "\" portA=\""
                        + boost::lexical_cast<std::string> (paNum) + "\"" + " objB=\"" + boost::lexical_cast<std::string> (nvbNum) + "\" portB=\""
                        + boost::lexical_cast<std::string> (pbNum) + "\" />\n";
}

/*****************************************************************************/

void NativeXmlFormatSave::onConnector (IClutterActor *a) { onLineConnector (a); }

/*****************************************************************************/

void NativeXmlFormatSave::onRectangle (IClutterActor *a) { *impl->file << "<" + a->getId () + " " + clutterActorArguments (a) + "/>\n"; }

/*****************************************************************************/

void NativeXmlFormatSave::Impl::reset ()
{
        nodesMap.clear ();
        nodesNum = 0;
}
