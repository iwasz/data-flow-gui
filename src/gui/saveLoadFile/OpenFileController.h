/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef OPEN_FILE_CONTROLLER_OPEN_H_
#define OPEN_FILE_CONTROLLER_OPEN_H_

#include <ReflectionParserAnnotation.h>
#include <controller/AbstractController.h>
#include <gui/saveLoadFile/IDataFileLoad.h>
#include <gui/saveLoadFile/IDataFileSave.h>

/**
 *
 */
class __tiliae_reflect__ OpenFileController : public GtkForms::AbstractController {
public:
        OpenFileController () {}
        virtual ~OpenFileController () {}

        virtual GtkForms::ViewsToOpen onStart ();
        void onResponse (int responseId, std::string const &path);

        void setLoadFile (IDataFileLoad *l) { loadService = l; }

private:

        IDataFileLoad *loadService = nullptr;
};

#endif /* MainController_H_ */
