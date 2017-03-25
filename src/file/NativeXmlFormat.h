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

class __tiliae_reflect__ NativeXmlFormatSave : public IDataFile {
public:
        NativeXmlFormatSave ();
        virtual ~NativeXmlFormatSave ();
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
        std::string clutterActorArguments (IClutterActor *a);
        std::string clutterActorArgumentsStroke (IClutterActor *a);

        SceneAPI *sceneApi = nullptr;
        struct Impl;
        Impl *impl;
};

#endif // NATIVEXMLFORMAT_H
