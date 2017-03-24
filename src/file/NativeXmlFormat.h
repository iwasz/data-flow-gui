/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef NATIVEXMLFORMAT_H
#define NATIVEXMLFORMAT_H

#include "IDataFile.h"

class SceneAPI;

class __tiliae_reflect__ NativeXmlFormat : public IDataFile {
public:
        virtual ~NativeXmlFormat () {}
        virtual void load (std::string const &path);
        virtual void save (std::string const &path);

        virtual std::string onButton (IClutterActor *a, Operation o);
        virtual std::string onCircle (IClutterActor *a, Operation o);
        virtual std::string onCircularNode (IClutterActor *a, Operation o);
        virtual std::string onLine (IClutterActor *a, Operation o);
        virtual std::string onLineConnector (IClutterActor *a, Operation o);
        virtual std::string onConnector (IClutterActor *a, Operation o);
        virtual std::string onRectangle (IClutterActor *a, Operation o);

        void setSceneApi (SceneAPI *value) { sceneApi = value; }

private:
        SceneAPI *sceneApi = nullptr;
};

#endif // NATIVEXMLFORMAT_H
