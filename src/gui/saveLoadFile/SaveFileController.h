/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FILE_CONTROLLER_SAVE_H_
#define FILE_CONTROLLER_SAVE_H_

#include <ReflectionParserAnnotation.h>
#include <controller/AbstractController.h>
#include <gui/saveLoadFile/IDataFileLoad.h>
#include <gui/saveLoadFile/IDataFileSave.h>

/**
 *
 */
class __tiliae_reflect__ SaveFileController : public GtkForms::AbstractController {
public:
        SaveFileController () {}
        virtual ~SaveFileController () {}

        virtual GtkForms::ViewsToOpen onStart ();
        void onResponse (int responseId, std::string const &path);

        void setDataFile (IDataFileSave *s) { saveService = s; }

private:

        IDataFileSave *saveService = nullptr;
};

#endif /* MainController_H_ */
