/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATAFLOWAPP_H
#define DATAFLOWAPP_H

#include <GtkForms.h>

class DataFlowApp : public GtkForms::App {
public:
        virtual ~DataFlowApp () {}
        void initBeanWrapper ();
        Ptr<Container::BeanFactoryContainer> createContainer (Ptr<Container::MetaContainer> metaContainer);
};

#endif // DATAFLOWAPP_H
