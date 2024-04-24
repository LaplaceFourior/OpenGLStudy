#pragma once
#include <memory>
#include <unordered_map>
#include <string>

struct ClassInfo
{
    std::string mClassName;
    std::string mParentClassName;
    ClassInfo* mParentClassInfo;
};

class ClassDB
{
public:

public:
    static std::unordered_map<std::string, ClassInfo> sAllClass;
public:
    template <typename T>
    static void addClass()
    {
        addClass2(T::getClassStatic(), T::getParentClassStatic());
    }
    static void addClass2(const std::string& aClass, const std::string& aParentClass);
    template <typename T>
    static void registerClass()
    {
        T::initializeClass();
    }  
};

#define REGISTER_CLASS(mClass)\
    ::ClassDB::registerClass<mClass>();

