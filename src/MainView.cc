/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MainView.h"

void MainView::loadUi (GtkForms::App *app)
{
        BuilderView::loadUi (app);
        std::cerr << "Hello world" << std::endl;
}
