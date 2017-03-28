/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "NativeXmlFormatLoad.h"
#include "view/CircularNode.h"
#include "view/IClutterActor.h"
#include "view/LineConnector.h"
#include "view/SceneAPI.h"
#include <beanWrapper/BeanWrapper.h>
#include <boost/lexical_cast.hpp>
#include <core/Exception.h>
#include <cstring>
#include <fstream>
#include <map>
#include <mxml.h>
#include <stdio.h>

struct NativeXmlFormatLoad::Impl {
        //        typedef std::map<INodeView *, unsigned int> NodesMap;
        //        NodesMap nodesMap;
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
        FILE *file = fopen (path.c_str (), "r");

        if (!file) {
                int e = errno;
                throw Core::Exception ("NativeXmlFormatLoad::load : problem loading file [" + path + "]. Erorr : " + strerror (e));
        }

        mxmlSAXLoadFile (nullptr, file, MXML_OPAQUE_CALLBACK, &Impl::saxHandler, &impl);
        fclose (file);
}

/*****************************************************************************/

void NativeXmlFormatLoad::setSceneApi (SceneAPI *value) { impl->sceneApi = value; }

/*****************************************************************************/

void NativeXmlFormatLoad::setWrapper (Wrapper::BeanWrapper *value) { impl->wrapper = value; }

/*****************************************************************************/

void NativeXmlFormatLoad::Impl::reset ()
{
        //        nodesMap.clear ();
        //        nodesNum = 0;
        //        file = nullptr;
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
#include <iostream>

void NativeXmlFormatLoad::Impl::onOpenElement (mxml_node_t *node)
{
        if (node->type != MXML_ELEMENT) {
                return;
        }

        char const *name = mxmlGetElement (node);

        if (std::string (name) == "flow") {
                return;
        }

#if 1
        std::cerr << "Open [" << name << "]" << std::endl;
#endif

        std::string nnn = name;
        IClutterActor *actor = sceneApi->create (nnn);
        wrapper->setWrappedObject (Core::Variant (actor));

        mxml_attr_t *attrs = node->value.element.attrs;
        int numAttrs = node->value.element.num_attrs;

        for (int i = 0; i < numAttrs; ++i) {
#if 1
                std::cerr << (attrs + i)->name << " = " << (attrs + i)->value << std::endl;
#endif

                Core::DebugContext ctx;

                if (!wrapper->set ((attrs + i)->name, Core::Variant ((attrs + i)->value), &ctx)) {
                        throw Core::Exception ("NativeXmlFormatLoad::Impl::onOpenElement : " + ctx.getMessage ());
                }
        }

        actor->setVisible (true);

        //        if ((argVal = mxmlElementGetAttr (node, "resource"))) {
        //                imports.push (argVal);
        //        }

        //        actor->setPosition (Point (4800, 5000));
        //        actor->setSize (Dimension (100, 100));
        //        actor->setVisible (true);
        //        INodeView *nodeViewA = dynamic_cast<INodeView *> (actor);

        //        actor = s->create ("copyNode");
        //        actor->setPosition (Point (5000, 5000));
        //        actor->setSize (Dimension (100, 100));
        //        actor->setVisible (true);
        //        INodeView *nodeViewB = dynamic_cast<INodeView *> (actor);

        //        // Ports
        //        Port *pa = nodeViewA->getPorts ()[2].get ();
        //        Port *pb = nodeViewB->getPorts ()[0].get ();

        //        // Connection
        //        actor = s->create ("lineConnector");
        //        actor->setVisible (true);
        //        LineConnector *lc = dynamic_cast<LineConnector *> (actor);

        //        s->connect (lc, pa, pb);
}

/****************************************************************************/

void NativeXmlFormatLoad::Impl::onCloseElement (mxml_node_t *node) { char const *name = mxmlGetElement (node); }
