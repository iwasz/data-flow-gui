/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DF_MAINVIEW_H
#define DF_MAINVIEW_H

#include "view/BuilderView.h"
#include "view/Stage.h"

class __tiliae_reflect__ MainView : public GtkForms::BuilderView {
public:
        virtual ~MainView () {}
        virtual void loadUi (GtkForms::App *app);

        Stage *getStage () const { return stage; }
        void setStage (Stage *value) { stage = value; }

private:
        Stage *stage = nullptr;
};

#endif // MAINVIEW_H
