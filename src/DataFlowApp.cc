/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DataFlowApp.h"
#include "primitives/Color.h"
#include "primitives/Direction.h"
#include "view/routable/RoutablePin.h"

/*---------------------------------------------------------------------------*/

// Convoluted way of injecting more custom editors.
void DataFlowApp::initBeanWrapper ()
{
        GtkForms::App::initBeanWrapper ();
        Wrapper::BeanWrapper *w = getBeanWrapper ();
        Editor::ChainEditor *chain = dynamic_cast<Editor::ChainEditor *> (w->getEditor ());
        Editor::TypeEditor *typeEditor = dynamic_cast<Editor::TypeEditor *> (chain->getEditors ()[0]);
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (primitives::Color), new primitives::ColorEditor));
}

/*---------------------------------------------------------------------------*/

std::unique_ptr<Container::BeanFactoryContainer> DataFlowApp::createContainer (Ptr<Container::MetaContainer> metaContainer)
{
        std::unique_ptr<Container::BeanFactoryContainer> container (Container::ContainerFactory::create (metaContainer, true));
        container->addConversion (typeid (primitives::Color), new primitives::ColorEditor); // Auto delete is on.
        container->addConversion (typeid (Direction), directionFromString);
        container->addConversion (typeid (Avoid::ConnDirFlag), avoidDirectionFromString);
        return container;
}
