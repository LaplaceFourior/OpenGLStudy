#pragma once
#include <string>
#include "Register.h"

namespace TenetEngine {

class Object
{
public:
    virtual std::string getClass() const
    {
        return std::string("Object");
    }
    virtual std::string getParentClass() const
    {
        return std::string();
    } 
    static std::string getClassStatic() { return "Object";}
    static std::string getParentClassStatic() { return std::string();}
    static void initializeClass()
    {
        static bool initialized = false;
        if (initialized) {
            return;
        }
        TenetEngine::ClassDB::addClass<Object>();
        initialized = true;
    }
};

#define ACLASS(mClass, mInherits)\
public:\
    virtual std::string getClass() const override\
    {\
        return std::string(#mClass);\
    }\
    virtual std::string getParentClass() const override\
    {\
        return std::string(#mInherits);\
    }\
    static std::string getClassStatic()\
    {\
        return std::string(#mClass);\
    }\
    static std::string getParentClassStatic()\
    {\
        return std::string(#mInherits);\
    }\
public:\
    static void initializeClass()\
    {\
        static bool initialized = false;\
        if (initialized) {\
            return;\
        }\
        mInherits::initializeClass();\
        TenetEngine::ClassDB::addClass<mClass>();\
        initialized = true;\
    }\
private:

}