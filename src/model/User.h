#ifndef USER_H
#define USER_H

#include <string>
#include <ReflectionParserAnnotation.h>

struct __tiliae_reflect__ User {

        std::string toString () const;

        std::string firstname;
        std::string lastname;
        std::string occupation;
        bool happy;
};

#endif // USER_H
