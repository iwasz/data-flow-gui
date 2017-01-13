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
#include <ReflectionParserAnnotation.h>
#include <container/Container.h>

class __tiliae_reflect__ ContainerFactoryStrategy : public IFactoryStrategy {
public:
        virtual ~ContainerFactoryStrategy () {}
        virtual Core::Variant run (/*Point const &a, Core::Object *oa, Point const &b, Core::Object *ob*/) __tiliae_no_reflect__;

        std::string const &getBeanName () const { return beanName; }
        void setBeanName (const std::string &value) { beanName = value; }

        Container::BeanFactoryContainer *getContainer () const { return container; }
        void setContainer (Container::BeanFactoryContainer *value) { container = value; }

private:
        std::string beanName;
        Container::BeanFactoryContainer *container;
};

#endif // CONTAINERFACTORYSTRATEGY_H
