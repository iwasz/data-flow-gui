/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef NATIVEXMLFORMAT_H
#define NATIVEXMLFORMAT_H

#include "IDataFileSave.h"

class SceneAPI;

class __tiliae_reflect__ NativeXmlFormatSave : public IDataFileSave {
public:
        NativeXmlFormatSave ();
        virtual ~NativeXmlFormatSave ();

        virtual void load (std::string const &path);
        virtual void save (std::string const &path);

        virtual void onButton (IClutterActor *a);
        virtual void onCircle (IClutterActor *a);
        virtual void onCircularNode (IClutterActor *a);
        virtual void onLine (IClutterActor *a);
        virtual void onLineConnector (IClutterActor *a);
        virtual void onConnector (IClutterActor *a);
        virtual void onRectangle (IClutterActor *a);

        void setSceneApi (SceneAPI *value);

private:
        void clutterActorArguments(IClutterActor *a);
        void clutterActorArgumentsStroke(IClutterActor *a);

        struct Impl;
        Impl *impl;
};

#endif // NATIVEXMLFORMAT_H
