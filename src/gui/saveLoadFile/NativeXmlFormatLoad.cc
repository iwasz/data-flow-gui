/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "NativeXmlFormatLoad.h"
#include "view/AbstractArcView.h"
#include "view/ConnectorActor.h"
#include "view/IClutterActor.h"
#include "view/NodeActor.h"
#include "view/SceneAPI.h"
#include <beanWrapper/BeanWrapper.h>
#include <boost/lexical_cast.hpp>
#include <core/Exception.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <mxml.h>
#include <stdio.h>

struct NativeXmlFormatLoad::Impl {
        typedef std::map<unsigned int, NodeActor *> NodesMap;
        NodesMap nodesMap;
        //        unsigned int nodesNum = 0;
        //        std::ofstream *file = nullptr;
        SceneAPI *sceneApi = nullptr;
        Wrapper::BeanWrapper *wrapper;

        void reset ();

        static void saxHandler (mxml_node_t *node, mxml_sax_event_t event, void *data);

        void onOpenElement (mxml_node_t *node);
        void onCloseElement (mxml_node_t *node);
};

/*****************************************************************************/

NativeXmlFormatLoad::NativeXmlFormatLoad () { impl = new Impl; }
NativeXmlFormatLoad::~NativeXmlFormatLoad () { delete impl; }

/*****************************************************************************/

void NativeXmlFormatLoad::load (std::string const &path)
{
        impl->reset ();
        FILE *file = fopen (path.c_str (), "r");

        if (!file) {
                int e = errno;
                throw Core::Exception ("NativeXmlFormatLoad::load : problem loading file [" + path + "]. Erorr : " + strerror (e));
        }

        mxmlSAXLoadFile (nullptr, file, MXML_OPAQUE_CALLBACK, &Impl::saxHandler, impl);
        fclose (file);
}

/*****************************************************************************/

void NativeXmlFormatLoad::setSceneApi (SceneAPI *value) { impl->sceneApi = value; }

/*****************************************************************************/

void NativeXmlFormatLoad::setWrapper (Wrapper::BeanWrapper *value) { impl->wrapper = value; }

/*****************************************************************************/

void NativeXmlFormatLoad::Impl::reset ()
{
        nodesMap.clear ();
        //        nodesNum = 0;
}

/*****************************************************************************/

void NativeXmlFormatLoad::Impl::saxHandler (mxml_node_t *node, mxml_sax_event_t event, void *data)
{
        Impl *impl = static_cast<Impl *> (data);

        mxml_type_t type = mxmlGetType (node);

        switch (event) {
        //        case MXML_SAX_CDATA:
        //        case MXML_SAX_DATA:
        //                impl->onData (node);
        //                break;

        //        case MXML_SAX_ELEMENT_CLOSE:

        //                if (type == MXML_ELEMENT) {
        //                        impl->onCloseElement (node);
        //                }
        //                break;

        case MXML_SAX_ELEMENT_OPEN:

                if (type == MXML_ELEMENT) {
                        impl->onOpenElement (node);
                }

                break;

        default:
                break;
        }
}

/*****************************************************************************/

void NativeXmlFormatLoad::Impl::onOpenElement (mxml_node_t *node)
{
        if (node->type != MXML_ELEMENT) {
                return;
        }

        char const *name = mxmlGetElement (node);

        if (std::string (name) == "flow") {
                return;
        }

#if 0
        std::cerr << "Open [" << name << "]" << std::endl;
#endif

        std::string nnn = name;
        IClutterActor *actor = sceneApi->create (nnn);
        wrapper->setWrappedObject (Core::Variant (actor));

        mxml_attr_t *attrs = node->value.element.attrs;
        int numAttrs = node->value.element.num_attrs;

        for (int i = 0; i < numAttrs; ++i) {
                std::string name = (attrs + i)->name;
                std::string value = (attrs + i)->value;

#if 0
                std::cerr << name << " = " << value << std::endl;
#endif

                NodeActor *nv;
                if (name == "index" && (nv = dynamic_cast<NodeActor *> (actor))) {
                        nodesMap[boost::lexical_cast<unsigned int> (value)] = nv;
                }
                else if (name == "objA") {

                        unsigned int objAIndex = boost::lexical_cast<unsigned int> (mxmlElementGetAttr (node, "objA"));
                        unsigned int objBIndex = boost::lexical_cast<unsigned int> (mxmlElementGetAttr (node, "objB"));
                        unsigned int portANumber = boost::lexical_cast<unsigned int> (mxmlElementGetAttr (node, "portA"));
                        unsigned int portBNumber = boost::lexical_cast<unsigned int> (mxmlElementGetAttr (node, "portB"));

                        NodeActor *nodeViewA = nodesMap[objAIndex];
                        NodeActor *nodeViewB = nodesMap[objBIndex];

                        if (!nodeViewA || !nodeViewB) {
                                throw Core::Exception ("NativeXmlFormatLoad::Impl::onOpenElement : !nodeViewA || !nodeViewB. Could not cast to ");
                        }

                        // Ports
                        Port *pa = nodeViewA->getPorts ()[portANumber].get ();
                        Port *pb = nodeViewB->getPorts ()[portBNumber].get ();

                        if (!pa || !pb) {
                                throw Core::Exception ("NativeXmlFormatLoad::Impl::onOpenElement : !pa || !pb. No such port");
                        }

                        ConnectorActor *lc = dynamic_cast<ConnectorActor *> (actor);
                        sceneApi->connect (lc, pa, pb);

                        /*---------------------------------------------------------------------------*/

                        AbstractArcView *aav = dynamic_cast<AbstractArcView *> (lc);
                        flow::Arc *arc = aav->getArc ().get ();

                        if (arc) {
                                const char *initialValueStr = mxmlElementGetAttr (node, "initVal");
                                const char *initialFullStr = mxmlElementGetAttr (node, "initFull");

                                if (initialValueStr && initialFullStr) {
                                        int initialValue = boost::lexical_cast<int> (initialValueStr);
                                        bool initialFull = boost::lexical_cast<bool> (initialFullStr);

                                        if (initialFull) {
                                                arc->init (initialValue);
                                        }
                                }
                        }
                }
                else if (name == "objB" || name == "portA" || name == "portB" || name == "initVal" || name == "initFull") {
                        // skip
                }
                else {
                        Core::DebugContext ctx;

                        if (!wrapper->set (name, Core::Variant (value), &ctx)) {
                                throw Core::Exception ("NativeXmlFormatLoad::Impl::onOpenElement : " + ctx.getMessage ());
                        }
                }
        }

        actor->setVisible (true);
}

/****************************************************************************/

void NativeXmlFormatLoad::Impl::onCloseElement (mxml_node_t *node) { /*char const *name = mxmlGetElement (node);*/}
