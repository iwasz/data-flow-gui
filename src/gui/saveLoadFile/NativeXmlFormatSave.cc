/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "NativeXmlFormatSave.h"
#include "view/CircularNode.h"
#include "view/Connector.h"
#include "view/IClutterActor.h"
#include "view/Line.h"
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
        std::ofstream *file = nullptr;
        SceneAPI *sceneApi = nullptr;

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
        impl->reset ();
        std::ofstream file (path);
        impl->file = &file;
        impl->file->imbue (std::locale::classic ());

        file << "<flow>\n";

        for (IClutterActor *actor : impl->sceneApi->getAllActors ()) {
                actor->visit (this);
        }

        for (IClutterActor *actor : impl->sceneApi->getAllConnectors ()) {
                actor->visit (this);
        }

        file << "</flow>" << std::endl;
}

/*****************************************************************************/

void NativeXmlFormatSave::clutterActorArguments (IClutterActor *a)
{
        primitives::Point p = a->getPosition ();
        primitives::Dimension d = a->getSize ();

        // This is output directly to the stream, because it has locale set appropriately, and boost::lexical_cast has not.
        *impl->file << "position=\"" << p.x << "," << p.y << "\" size=\"" << d.width << "," << d.height << "\" fill=\"" << a->isFill () << "\" fillColor=\""
                    << primitives::Color::toString (a->getFillColor ()) << "\" ";

        clutterActorArgumentsStroke (a);
}

/*****************************************************************************/

void NativeXmlFormatSave::clutterActorArgumentsStroke (IClutterActor *a)
{
        *impl->file << "strokeWidth=\"" << a->getStrokeWidth () << "\" strokeColor=\"" << primitives::Color::toString (a->getStrokeColor ())
                    << "\" strokeDash=\"" << a->getStrokeDash () << "\" ";
}

/*****************************************************************************/

void NativeXmlFormatSave::onButton (IClutterActor *a)
{
        *impl->file << "<" << a->getId () << " ";
        clutterActorArguments (a);
        *impl->file << "/>\n";
}

/*****************************************************************************/

void NativeXmlFormatSave::onCircle (IClutterActor *a)
{
        *impl->file << "<" << a->getId () << " ";
        clutterActorArguments (a);
        *impl->file << "/>\n";
}

/*****************************************************************************/

void NativeXmlFormatSave::onCircularNode (IClutterActor *a)
{
        CircularNode *cn = dynamic_cast<CircularNode *> (a);
        INodeView *inv = dynamic_cast<INodeView *> (cn);
        unsigned int myIdx = impl->nodesNum++;
        impl->nodesMap[inv] = myIdx;

        // std::cerr << (void *)inv << "=" << myIdx << std::endl;

        *impl->file << std::string ("<") << a->getId () << " index=\"" << myIdx << "\" ";
        clutterActorArguments (a);
        *impl->file << "font=\"" << cn->getFont () << "\" fontColor=\"" << primitives::Color::toString (cn->getFontColor ()) << "\" />\n";
}

/*****************************************************************************/

void NativeXmlFormatSave::onLine (IClutterActor *a)
{
        Line *l = dynamic_cast<Line *> (a);
        *impl->file << "<" << a->getId () << " ";
        clutterActorArgumentsStroke (a);
        *impl->file << " pointA=\"" << l->getPointA ().x << "," << l->getPointA ().y << "\" pointB=\"" << l->getPointB ().x << "," << l->getPointB ().y
                    << "\" />\n";
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

        // std::cerr << (void *)pa->getNodeView () << "=" << nvaNum << " " << (void *)pb->getNodeView () << "=" << nvbNum << std::endl;

        *impl->file << "<" << a->getId () << " ";
        clutterActorArgumentsStroke (a);
        *impl->file << " objA=\"" << nvaNum << "\" portA=\"" << paNum << "\""
                    << " objB=\"" << nvbNum << "\" portB=\"" << pbNum << "\" />\n";
}

/*****************************************************************************/

void NativeXmlFormatSave::onConnector (IClutterActor *a) { onLineConnector (a); }

/*****************************************************************************/

void NativeXmlFormatSave::onRectangle (IClutterActor *a)
{
        *impl->file << "<" << a->getId () << " ";
        clutterActorArguments (a);
        *impl->file << "/>\n";
}

/*****************************************************************************/

void NativeXmlFormatSave::setSceneApi (SceneAPI *value) { impl->sceneApi = value; }

/*****************************************************************************/

void NativeXmlFormatSave::Impl::reset ()
{
        nodesMap.clear ();
        nodesNum = 0;
        file = nullptr;
}
