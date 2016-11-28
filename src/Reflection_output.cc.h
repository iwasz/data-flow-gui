/*
 * This file was aut-generated by tiliaeparser. Do not modify. Unless.
 * Include only once.
 * https://github.com/iwasz/tiliae
 */

#include <reflection/Reflection.h>
#include "/home/iwasz/workspace/data-flow-gui/src/Reflection_input.cc"

namespace {
using namespace Core;
using namespace Reflection;

void createReflectionDatabase_gtkFormsDemo ()
{
	{
		Class *clazz = new Class ("Object", typeid (Core::Object &), new Reflection::PtrDeleter <Core::Object>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Core::Object, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Core::Object, void>::Level1Wrapper::newConstructorPointer ()));
		}
	}
	{
		Class *clazz = new Class ("IEditor", typeid (Editor::IEditor &), new Reflection::PtrDeleter <Editor::IEditor>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("Object");
			clazz->addMethod (new Method ("convert", createMethodWrapper (&Editor::IEditor::convert)));
		}
	}
	{
		Class *clazz = new Class ("IFactory", typeid (Factory::IFactory &), new Reflection::PtrDeleter <Factory::IFactory>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("Object");
			clazz->addMethod (new Method ("create", createMethodWrapper (&Factory::IFactory::create)));
		}
	}
	{
		Class *clazz = new Class ("JEditor", typeid (Editor::JEditor &), new Reflection::PtrDeleter <Editor::JEditor>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("IEditor");
			clazz->addMethod (new Method ("convert", createMethodWrapper (&Editor::JEditor::convert)));
			clazz->addMethod (new Method ("edit", createMethodWrapper (&Editor::JEditor::edit)));
		}
	}
	{
		Class *clazz = new Class ("ListToStringEditor", typeid (Editor::ListToStringEditor &), new Reflection::PtrDeleter <Editor::ListToStringEditor>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("JEditor");
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Editor::ListToStringEditor, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Editor::ListToStringEditor, const std::string &, const std::string &>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("edit", createMethodWrapper (&Editor::ListToStringEditor::edit)));
			clazz->addMethod (new Method ("getDelimiter", createMethodWrapper (&Editor::ListToStringEditor::getDelimiter)));
			clazz->addMethod (new Method ("setDelimiter", createMethodWrapper (&Editor::ListToStringEditor::setDelimiter)));
			clazz->addMethod (new Method ("getQuotation", createMethodWrapper (&Editor::ListToStringEditor::getQuotation)));
			clazz->addMethod (new Method ("setQuotation", createMethodWrapper (&Editor::ListToStringEditor::setQuotation)));
		}
	}
	{
		Class *clazz = new Class ("ChainFactory", typeid (Factory::ChainFactory &), new Reflection::PtrDeleter <Factory::ChainFactory>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("IFactory");
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Factory::ChainFactory, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Factory::ChainFactory, _Bool>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("create", createMethodWrapper (&Factory::ChainFactory::create)));
			clazz->addMethod (new Method ("setFactories", createMethodWrapper (&Factory::ChainFactory::setFactories)));
			clazz->addMethod (new Method ("addFactory", createMethodWrapper (&Factory::ChainFactory::addFactory)));
			clazz->addMethod (new Method ("getFactories", createMethodWrapper (&Factory::ChainFactory::getFactories)));
		}
	}
	{
		Class *clazz = new Class ("K202", typeid (k202::K202 &), new Reflection::PtrDeleter <k202::K202>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addMethod (new Method ("setBeanWrapper", createMethodWrapper (&k202::K202::setBeanWrapper)));
		}
	}
	{
		Class *clazz = new Class ("Sender", typeid (Signal::Sender &), new Reflection::PtrDeleter <Signal::Sender>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Signal::Sender, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Signal::Sender, void *>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Signal::Sender, void *, const std::string &>::Level1Wrapper::newConstructorPointer ()));
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Signal::Sender, const std::string &>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("getOwnerObject", createMethodWrapper (&Signal::Sender::getOwnerObject)));
			clazz->addMethod (new Method ("setOwnerObject", createMethodWrapper (&Signal::Sender::setOwnerObject)));
			clazz->addMethod (new Method ("getScope", createMethodWrapper (&Signal::Sender::getScope)));
			clazz->addMethod (new Method ("setScope", createMethodWrapper (&Signal::Sender::setScope)));
			clazz->addMethod (new Method ("setPath", createMethodWrapper (&Signal::Sender::setPath)));
			clazz->addMethod (new Method ("getPath", createMethodWrapper (&Signal::Sender::getPath)));
			clazz->addMethod (new Method ("getParamVector", createMethodWrapper (&Signal::Sender::getParamVector)));
			clazz->addMethod (new Method ("setParamVector", createMethodWrapper (&Signal::Sender::setParamVector)));
			clazz->addMethod (new Method ("getParamMap", createMethodWrapper (&Signal::Sender::getParamMap)));
			clazz->addMethod (new Method ("setParamMap", createMethodWrapper (&Signal::Sender::setParamMap)));
		}
	}
	{
		Class *clazz = new Class ("IMapping", typeid (GtkForms::IMapping &), new Reflection::PtrDeleter <GtkForms::IMapping>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("Object");
			clazz->addMethod (new Method ("getWidget", createMethodWrapper (&GtkForms::IMapping::getWidget)));
			clazz->addMethod (new Method ("getModel", createMethodWrapper (&GtkForms::IMapping::getModel)));
			clazz->addMethod (new Method ("view2Model", createMethodWrapper (&GtkForms::IMapping::view2Model)));
			clazz->addMethod (new Method ("model2View", createMethodWrapper (&GtkForms::IMapping::model2View)));
		}
	}
	{
		Class *clazz = new Class ("Mapping", typeid (GtkForms::Mapping &), new Reflection::PtrDeleter <GtkForms::Mapping>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("IMapping");
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <GtkForms::Mapping, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addField (new Field ("widget", Reflection::createFieldWrapper (&GtkForms::Mapping::widget)));
			clazz->addField (new Field ("property", Reflection::createFieldWrapper (&GtkForms::Mapping::property)));
			clazz->addField (new Field ("model", Reflection::createFieldWrapper (&GtkForms::Mapping::model)));
			clazz->addField (new Field ("m2vEditor", Reflection::createFieldWrapper (&GtkForms::Mapping::m2vEditor)));
			clazz->addField (new Field ("v2mEditor", Reflection::createFieldWrapper (&GtkForms::Mapping::v2mEditor)));
			clazz->addMethod (new Method ("getWidget", createMethodWrapper (&GtkForms::Mapping::getWidget)));
			clazz->addMethod (new Method ("getProperty", createMethodWrapper (&GtkForms::Mapping::getProperty)));
			clazz->addMethod (new Method ("getModel", createMethodWrapper (&GtkForms::Mapping::getModel)));
		}
	}
	{
		Class *clazz = new Class ("MappingVector", typeid (GtkForms::MappingVector&), new PtrDeleter <GtkForms::MappingVector >);
		if (!Manager::add (clazz)) {;
			delete clazz;
		}
		else { 
			IConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <GtkForms::MappingVector, void>::Level1Wrapper::newConstructorPointer ();
			clazz->addConstructor (new Constructor (cp));

			ICallableWrapper *w = new AddWrapper <GtkForms::MappingVector > ();
			clazz->addMethod (new Method ("add", w));

			w = new GetWrapper <GtkForms::MappingVector > ();
			clazz->addMethod (new Method ("get", w));

			w = new SetWrapper <GtkForms::MappingVector > ();
			clazz->addMethod (new Method ("set", w));

			w = new IteratorWrapper <GtkForms::MappingVector > ();
			clazz->addMethod (new Method ("iterator", w));
		}
	}
	{
		Class *clazz = new Class ("IPageDecorator", typeid (GtkForms::IPageDecorator &), new Reflection::PtrDeleter <GtkForms::IPageDecorator>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("Object");
			clazz->addMethod (new Method ("run", createMethodWrapper (&GtkForms::IPageDecorator::run)));
		}
	}
	{
		Class *clazz = new Class ("PageDecoratorVector", typeid (GtkForms::PageDecoratorVector&), new PtrDeleter <GtkForms::PageDecoratorVector >);
		if (!Manager::add (clazz)) {;
			delete clazz;
		}
		else { 
			IConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <GtkForms::PageDecoratorVector, void>::Level1Wrapper::newConstructorPointer ();
			clazz->addConstructor (new Constructor (cp));

			ICallableWrapper *w = new AddWrapper <GtkForms::PageDecoratorVector > ();
			clazz->addMethod (new Method ("add", w));

			w = new GetWrapper <GtkForms::PageDecoratorVector > ();
			clazz->addMethod (new Method ("get", w));

			w = new SetWrapper <GtkForms::PageDecoratorVector > ();
			clazz->addMethod (new Method ("set", w));

			w = new IteratorWrapper <GtkForms::PageDecoratorVector > ();
			clazz->addMethod (new Method ("iterator", w));
		}
	}
	{
		Class *clazz = new Class ("AbstractView", typeid (GtkForms::AbstractView &), new Reflection::PtrDeleter <GtkForms::AbstractView>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("Object");
			clazz->addField (new Field ("name", Reflection::createFieldWrapper (&GtkForms::AbstractView::name)));
			clazz->addField (new Field ("mappings", Reflection::createFieldWrapper (&GtkForms::AbstractView::mappings)));
			clazz->addField (new Field ("decorators", Reflection::createFieldWrapper (&GtkForms::AbstractView::decorators)));
			clazz->addMethod (new Method ("getName", createMethodWrapper (&GtkForms::AbstractView::getName)));
			clazz->addMethod (new Method ("contId", createMethodWrapper (&GtkForms::AbstractView::contId)));
			clazz->addMethod (new Method ("loadUi", createMethodWrapper (&GtkForms::AbstractView::loadUi)));
			clazz->addMethod (new Method ("show", createMethodWrapper (&GtkForms::AbstractView::show)));
			clazz->addMethod (new Method ("hide", createMethodWrapper (&GtkForms::AbstractView::hide)));
			clazz->addMethod (new Method ("refresh", createMethodWrapper (&GtkForms::AbstractView::refresh)));
			clazz->addMethod (new Method ("reparent", createMethodWrapper (&GtkForms::AbstractView::reparent)));
			clazz->addMethod (new Method ("destroyUi", createMethodWrapper (&GtkForms::AbstractView::destroyUi)));
			clazz->addMethod (new Method ("isLoaded", createMethodWrapper (&GtkForms::AbstractView::isLoaded)));
			clazz->addMethod (new Method ("getUiOrThrow", createMethodWrapper (&GtkForms::AbstractView::getUiOrThrow)));
			clazz->addMethod (new Method ("getInputs", createMethodWrapper (&GtkForms::AbstractView::getInputs)));
			clazz->addMethod (new Method ("getSlots", createMethodWrapper (&GtkForms::AbstractView::getSlots)));
			clazz->addMethod (new Method ("getSlot", createMethodWrapper (&GtkForms::AbstractView::getSlot)));
			clazz->addMethod (new Method ("printStructure", createMethodWrapper (&GtkForms::AbstractView::printStructure)));
			clazz->addMethod (new Method ("getMappingsByInput", createMethodWrapper (&GtkForms::AbstractView::getMappingsByInput)));
			clazz->addMethod (new Method ("getMappingsByModelRange", createMethodWrapper (&GtkForms::AbstractView::getMappingsByModelRange)));
			clazz->addMethod (new Method ("connectSignals", createMethodWrapper (&GtkForms::AbstractView::connectSignals)));
			clazz->addMethod (new Method ("connectSignal", createMethodWrapper (&GtkForms::AbstractView::connectSignal)));
			clazz->addMethod (new Method ("getControllerFromUi", createMethodWrapper (&GtkForms::AbstractView::getControllerFromUi)));
			clazz->addMethod (new Method ("setControllerToUi", createMethodWrapper (&GtkForms::AbstractView::setControllerToUi)));
			clazz->addMethod (new Method ("getController", createMethodWrapper (&GtkForms::AbstractView::getController)));
			clazz->addMethod (new Method ("setController", createMethodWrapper (&GtkForms::AbstractView::setController)));
			clazz->addMethod (new Method ("setConfig", createMethodWrapper (&GtkForms::AbstractView::setConfig)));
		}
	}
	{
		Class *clazz = new Class ("ViewMap", typeid (GtkForms::ViewMap&), new PtrDeleter <GtkForms::ViewMap >);
		if (!Manager::add (clazz)) {;
			delete clazz;
		}
		else { 
			IConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <GtkForms::ViewMap, void>::Level1Wrapper::newConstructorPointer ();
			clazz->addConstructor (new Constructor (cp));

			ICallableWrapper *w = new AddWrapper <GtkForms::ViewMap > ();
			clazz->addMethod (new Method ("add", w));

			w = new GetWrapper <GtkForms::ViewMap > ();
			clazz->addMethod (new Method ("get", w));

			w = new SetWrapper <GtkForms::ViewMap > ();
			clazz->addMethod (new Method ("set", w));

			w = new IteratorWrapper <GtkForms::ViewMap > ();
			clazz->addMethod (new Method ("iterator", w));
		}
	}
	{
		Class *clazz = new Class ("BuilderView", typeid (GtkForms::BuilderView &), new Reflection::PtrDeleter <GtkForms::BuilderView>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("AbstractView");
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <GtkForms::BuilderView, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addField (new Field ("file", Reflection::createFieldWrapper (&GtkForms::BuilderView::file)));
			clazz->addField (new Field ("alsoLoad", Reflection::createFieldWrapper (&GtkForms::BuilderView::alsoLoad)));
			clazz->addField (new Field ("loadWholeFile", Reflection::createFieldWrapper (&GtkForms::BuilderView::loadWholeFile)));
			clazz->addMethod (new Method ("loadUi", createMethodWrapper (&GtkForms::BuilderView::loadUi)));
			clazz->addMethod (new Method ("isLoaded", createMethodWrapper (&GtkForms::BuilderView::isLoaded)));
			clazz->addMethod (new Method ("destroyUi", createMethodWrapper (&GtkForms::BuilderView::destroyUi)));
			clazz->addMethod (new Method ("getUiOrThrow", createMethodWrapper (&GtkForms::BuilderView::getUiOrThrow)));
			clazz->addMethod (new Method ("connectSignals", createMethodWrapper (&GtkForms::BuilderView::connectSignals)));
			clazz->addMethod (new Method ("connectSignal", createMethodWrapper (&GtkForms::BuilderView::connectSignal)));
		}
	}
	{
		Class *clazz = new Class ("Circle", typeid (Circle &), new Reflection::PtrDeleter <Circle>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <Circle, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("setParent", createMethodWrapper (&Circle::setParent)));
			clazz->addMethod (new Method ("getVisible", createMethodWrapper (&Circle::getVisible)));
			clazz->addMethod (new Method ("setVisible", createMethodWrapper (&Circle::setVisible)));
			clazz->addMethod (new Method ("isFill", createMethodWrapper (&Circle::isFill)));
			clazz->addMethod (new Method ("setFill", createMethodWrapper (&Circle::setFill)));
			clazz->addMethod (new Method ("getH", createMethodWrapper (&Circle::getH)));
			clazz->addMethod (new Method ("setH", createMethodWrapper (&Circle::setH)));
			clazz->addMethod (new Method ("getW", createMethodWrapper (&Circle::getW)));
			clazz->addMethod (new Method ("setW", createMethodWrapper (&Circle::setW)));
			clazz->addMethod (new Method ("getY", createMethodWrapper (&Circle::getY)));
			clazz->addMethod (new Method ("setY", createMethodWrapper (&Circle::setY)));
			clazz->addMethod (new Method ("getX", createMethodWrapper (&Circle::getX)));
			clazz->addMethod (new Method ("setX", createMethodWrapper (&Circle::setX)));
			clazz->addMethod (new Method ("getStrokeWidth", createMethodWrapper (&Circle::getStrokeWidth)));
			clazz->addMethod (new Method ("setStrokeWidth", createMethodWrapper (&Circle::setStrokeWidth)));
			clazz->addMethod (new Method ("getStrokeDash", createMethodWrapper (&Circle::getStrokeDash)));
			clazz->addMethod (new Method ("setStrokeDash", createMethodWrapper (&Circle::setStrokeDash)));
			clazz->addMethod (new Method ("getStrokeColor", createMethodWrapper (&Circle::getStrokeColor)));
			clazz->addMethod (new Method ("setStrokeColor", createMethodWrapper (&Circle::setStrokeColor)));
			clazz->addMethod (new Method ("getFillColor", createMethodWrapper (&Circle::getFillColor)));
			clazz->addMethod (new Method ("setFillColor", createMethodWrapper (&Circle::setFillColor)));
		}
	}
	{
		Class *clazz = new Class ("MainView", typeid (MainView &), new Reflection::PtrDeleter <MainView>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("BuilderView");
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <MainView, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("loadUi", createMethodWrapper (&MainView::loadUi)));
		}
	}
	{
		Class *clazz = new Class ("ISignalAdapter", typeid (GtkForms::ISignalAdapter &), new Reflection::PtrDeleter <GtkForms::ISignalAdapter>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("Object");
			clazz->addMethod (new Method ("getSignal", createMethodWrapper (&GtkForms::ISignalAdapter::getSignal)));
			clazz->addMethod (new Method ("getGObjectName", createMethodWrapper (&GtkForms::ISignalAdapter::getGObjectName)));
			clazz->addMethod (new Method ("getWidgetId", createMethodWrapper (&GtkForms::ISignalAdapter::getWidgetId)));
			clazz->addMethod (new Method ("adapt", createMethodWrapper (&GtkForms::ISignalAdapter::adapt)));
		}
	}
	{
		Class *clazz = new Class ("AbstractSignalAdapter", typeid (GtkForms::AbstractSignalAdapter &), new Reflection::PtrDeleter <GtkForms::AbstractSignalAdapter>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("ISignalAdapter");
			clazz->addMethod (new Method ("getSignal", createMethodWrapper (&GtkForms::AbstractSignalAdapter::getSignal)));
			clazz->addMethod (new Method ("getGObjectName", createMethodWrapper (&GtkForms::AbstractSignalAdapter::getGObjectName)));
			clazz->addMethod (new Method ("getWidgetId", createMethodWrapper (&GtkForms::AbstractSignalAdapter::getWidgetId)));
		}
	}
	{
		Class *clazz = new Class ("SignalAdapterVector", typeid (GtkForms::SignalAdapterVector&), new PtrDeleter <GtkForms::SignalAdapterVector >);
		if (!Manager::add (clazz)) {;
			delete clazz;
		}
		else { 
			IConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <GtkForms::SignalAdapterVector, void>::Level1Wrapper::newConstructorPointer ();
			clazz->addConstructor (new Constructor (cp));

			ICallableWrapper *w = new AddWrapper <GtkForms::SignalAdapterVector > ();
			clazz->addMethod (new Method ("add", w));

			w = new GetWrapper <GtkForms::SignalAdapterVector > ();
			clazz->addMethod (new Method ("get", w));

			w = new SetWrapper <GtkForms::SignalAdapterVector > ();
			clazz->addMethod (new Method ("set", w));

			w = new IteratorWrapper <GtkForms::SignalAdapterVector > ();
			clazz->addMethod (new Method ("iterator", w));
		}
	}
	{
		Class *clazz = new Class ("IValidator", typeid (GtkForms::IValidator &), new Reflection::PtrDeleter <GtkForms::IValidator>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("Object");
			clazz->addMethod (new Method ("validate", createMethodWrapper (&GtkForms::IValidator::validate)));
			clazz->addMethod (new Method ("getModel", createMethodWrapper (&GtkForms::IValidator::getModel)));
		}
	}
	{
		Class *clazz = new Class ("ValidatorVector", typeid (GtkForms::ValidatorVector&), new PtrDeleter <GtkForms::ValidatorVector >);
		if (!Manager::add (clazz)) {;
			delete clazz;
		}
		else { 
			IConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <GtkForms::ValidatorVector, void>::Level1Wrapper::newConstructorPointer ();
			clazz->addConstructor (new Constructor (cp));

			ICallableWrapper *w = new AddWrapper <GtkForms::ValidatorVector > ();
			clazz->addMethod (new Method ("add", w));

			w = new GetWrapper <GtkForms::ValidatorVector > ();
			clazz->addMethod (new Method ("get", w));

			w = new SetWrapper <GtkForms::ValidatorVector > ();
			clazz->addMethod (new Method ("set", w));

			w = new IteratorWrapper <GtkForms::ValidatorVector > ();
			clazz->addMethod (new Method ("iterator", w));
		}
	}
	{
		Class *clazz = new Class ("AbstractAccessor", typeid (GtkForms::AbstractAccessor &), new Reflection::PtrDeleter <GtkForms::AbstractAccessor>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addMethod (new Method ("get", createMethodWrapper (&GtkForms::AbstractAccessor::get)));
			clazz->addMethod (new Method ("set", createMethodWrapper (&GtkForms::AbstractAccessor::set)));
			clazz->addMethod (new Method ("setSessionScope", createMethodWrapper (&GtkForms::AbstractAccessor::setSessionScope)));
			clazz->addMethod (new Method ("setCurrentController", createMethodWrapper (&GtkForms::AbstractAccessor::setCurrentController)));
		}
	}
	{
		Class *clazz = new Class ("ControllerMap", typeid (GtkForms::ControllerMap&), new PtrDeleter <GtkForms::ControllerMap >);
		if (!Manager::add (clazz)) {;
			delete clazz;
		}
		else { 
			IConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <GtkForms::ControllerMap, void>::Level1Wrapper::newConstructorPointer ();
			clazz->addConstructor (new Constructor (cp));

			ICallableWrapper *w = new AddWrapper <GtkForms::ControllerMap > ();
			clazz->addMethod (new Method ("add", w));

			w = new GetWrapper <GtkForms::ControllerMap > ();
			clazz->addMethod (new Method ("get", w));

			w = new SetWrapper <GtkForms::ControllerMap > ();
			clazz->addMethod (new Method ("set", w));

			w = new IteratorWrapper <GtkForms::ControllerMap > ();
			clazz->addMethod (new Method ("iterator", w));
		}
	}
	{
		Class *clazz = new Class ("AbstractController", typeid (GtkForms::AbstractController &), new Reflection::PtrDeleter <GtkForms::AbstractController>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("Object");
			clazz->addField (new Field ("validators", Reflection::createFieldWrapper (&GtkForms::AbstractController::validators)));
			clazz->addField (new Field ("signalAdapters", Reflection::createFieldWrapper (&GtkForms::AbstractController::signalAdapters)));
			clazz->addField (new Field ("loopDelayMs", Reflection::createFieldWrapper (&GtkForms::AbstractController::loopDelayMs)));
			clazz->addField (new Field ("alsoOpen", Reflection::createFieldWrapper (&GtkForms::AbstractController::alsoOpen)));
			clazz->addMethod (new Method ("set", createMethodWrapper (&GtkForms::AbstractController::set)));
			clazz->addMethod (new Method ("get", createMethodWrapper (&GtkForms::AbstractController::get)));
			clazz->addMethod (new Method ("setToSessionScope", createMethodWrapper (&GtkForms::AbstractController::setToSessionScope)));
			clazz->addMethod (new Method ("clearControllerScope", createMethodWrapper (&GtkForms::AbstractController::clearControllerScope)));
			clazz->addMethod (new Method ("getModelAccessor", createMethodWrapper (&GtkForms::AbstractController::getModelAccessor)));
			clazz->addMethod (new Method ("open", createMethodWrapper (&GtkForms::AbstractController::open)));
			clazz->addMethod (new Method ("openList", createMethodWrapper (&GtkForms::AbstractController::openList)));
			clazz->addMethod (new Method ("closeThis", createMethodWrapper (&GtkForms::AbstractController::closeThis)));
			clazz->addMethod (new Method ("close", createMethodWrapper (&GtkForms::AbstractController::close)));
			clazz->addMethod (new Method ("closeList", createMethodWrapper (&GtkForms::AbstractController::closeList)));
			clazz->addMethod (new Method ("replace", createMethodWrapper (&GtkForms::AbstractController::replace)));
			clazz->addMethod (new Method ("getName", createMethodWrapper (&GtkForms::AbstractController::getName)));
			clazz->addMethod (new Method ("contId", createMethodWrapper (&GtkForms::AbstractController::contId)));
			clazz->addMethod (new Method ("findByName", createMethodWrapper (&GtkForms::AbstractController::findByName)));
			clazz->addMethod (new Method ("validate", createMethodWrapper (&GtkForms::AbstractController::validate)));
			clazz->addMethod (new Method ("getSignalAdapters", createMethodWrapper (&GtkForms::AbstractController::getSignalAdapters)));
			clazz->addMethod (new Method ("getValidators", createMethodWrapper (&GtkForms::AbstractController::getValidators)));
			clazz->addMethod (new Method ("refresh", createMethodWrapper (&GtkForms::AbstractController::refresh)));
			clazz->addMethod (new Method ("submit", createMethodWrapper (&GtkForms::AbstractController::submit)));
			clazz->addMethod (new Method ("onStart", createMethodWrapper (&GtkForms::AbstractController::onStart)));
			clazz->addMethod (new Method ("onSubmit", createMethodWrapper (&GtkForms::AbstractController::onSubmit)));
			clazz->addMethod (new Method ("onStop", createMethodWrapper (&GtkForms::AbstractController::onStop)));
			clazz->addMethod (new Method ("getLoopDelayMs", createMethodWrapper (&GtkForms::AbstractController::getLoopDelayMs)));
			clazz->addMethod (new Method ("getLastMs", createMethodWrapper (&GtkForms::AbstractController::getLastMs)));
			clazz->addMethod (new Method ("performIdle", createMethodWrapper (&GtkForms::AbstractController::performIdle)));
			clazz->addMethod (new Method ("onQuit", createMethodWrapper (&GtkForms::AbstractController::onQuit)));
			clazz->addMethod (new Method ("onIdle", createMethodWrapper (&GtkForms::AbstractController::onIdle)));
			clazz->addMethod (new Method ("getView", createMethodWrapper (&GtkForms::AbstractController::getView)));
			clazz->addMethod (new Method ("setView", createMethodWrapper (&GtkForms::AbstractController::setView)));
			clazz->addMethod (new Method ("getApp", createMethodWrapper (&GtkForms::AbstractController::getApp)));
		}
	}
	{
		Class *clazz = new Class ("MainController", typeid (MainController &), new Reflection::PtrDeleter <MainController>);
		if (!Manager::add (clazz)) {
			delete clazz;
		}
		else {
			clazz->addBaseClassName ("AbstractController");
			clazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <MainController, void>::Level1Wrapper::newConstructorPointer ()));
			clazz->addMethod (new Method ("init", createMethodWrapper (&MainController::init)));
			clazz->addMethod (new Method ("onStart", createMethodWrapper (&MainController::onStart)));
			clazz->addMethod (new Method ("onSubmit", createMethodWrapper (&MainController::onSubmit)));
			clazz->addMethod (new Method ("onIdle", createMethodWrapper (&MainController::onIdle)));
			clazz->addMethod (new Method ("onStop", createMethodWrapper (&MainController::onStop)));
			clazz->addMethod (new Method ("onNewNodeToolClicked", createMethodWrapper (&MainController::onNewNodeToolClicked)));
			clazz->addMethod (new Method ("onStageClicked", createMethodWrapper (&MainController::onButtonPress)));
			clazz->addMethod (new Method ("onReleased", createMethodWrapper (&MainController::onButtonRelease)));
			clazz->addMethod (new Method ("onMotion", createMethodWrapper (&MainController::onMotion)));
		}
	}
}

struct Sentinel_gtkFormsDemo {
        Sentinel_gtkFormsDemo ()
        {
                createReflectionDatabase_gtkFormsDemo ();
        }
};

static Sentinel_gtkFormsDemo sentinel_gtkFormsDemo;
} // namespace

