/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONTAINERFACTORYSTRATEGY_H
#define CONTAINERFACTORYSTRATEGY_H

#include "IFactoryStrategy.h"
#include <Program.h>
#include <ReflectionParserAnnotation.h>
#include <container/Container.h>

/**
 * Facory strategy which only creates a bean from the container.
 */
class __tiliae_reflect__ ContainerFactoryStrategy : public IFactoryStrategy {
public:
        virtual ~ContainerFactoryStrategy () {}
        virtual Core::Variant run () __tiliae_no_reflect__;

        std::string const &getBeanName () const { return beanName; }
        void setBeanName (const std::string &value) { beanName = value; }

        Container::BeanFactoryContainer *getContainer () const { return container; }
        void setContainer (Container::BeanFactoryContainer *value) { container = value; }

private:
        std::string beanName;
        Container::BeanFactoryContainer *container = nullptr;
};

/**
 * Creates a bean, like ContainerFactoryStrategy do, but in addition it tries to cast
 * this newly created bean to INodeView, get the flow::INode and insert it into the
 * Program.
 */
class __tiliae_reflect__ NodeContainerFactoryStrategy : public ContainerFactoryStrategy {
public:
        virtual ~NodeContainerFactoryStrategy () {}
        virtual Core::Variant run () __tiliae_no_reflect__;

        flow::Program *getProgram () const { return program; }
        void setProgram (flow::Program *value) { program = value; }

private:
        flow::Program *program = nullptr;
};

#endif // CONTAINERFACTORYSTRATEGY_H
