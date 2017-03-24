/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "NativeXmlFormat.h"
#include "view/IClutterActor.h"
#include "view/SceneAPI.h"
#include <fstream>
//#include "view/

/*****************************************************************************/

void NativeXmlFormat::load (std::string const &path) {}

/*****************************************************************************/

void NativeXmlFormat::save (std::string const &path)
{
        ClutterActorVector const &allActors = sceneApi->getAllActors ();
        std::ofstream file (path);

        for (IClutterActor *actor : allActors) {
                file << actor->visit (this, SAVE);
        }
}

/*****************************************************************************/

std::string NativeXmlFormat::onButton (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<button/>\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormat::onCircle (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<circle/>\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormat::onCircularNode (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<circularNode/>\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormat::onLine (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<line/>\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormat::onLineConnector (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<lineConnector/>\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormat::onConnector (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<connector/>\n";
        }
        else {
        }
}

/*****************************************************************************/

std::string NativeXmlFormat::onRectangle (IClutterActor *a, Operation o)
{
        if (o == SAVE) {
                return "<rectangle/>\n";
        }
        else {
        }
}
