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
#include "view/Circle.h"

class __tiliae_reflect__ MainView : public GtkForms::BuilderView {
public:
        virtual ~MainView () {}
        virtual void loadUi (GtkForms::App *app);


private:

        Circle *constructionCircle = nullptr;
};

#endif // MAINVIEW_H
