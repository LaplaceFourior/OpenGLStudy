#include "Register.h"


std::unordered_map<std::string, ClassInfo> ClassDB::sAllClass;

void ClassDB::addClass2(const std::string &aClass, const std::string &aParentClass)
{
    sAllClass[aClass] = ClassInfo();
    ClassInfo& classInfo = sAllClass[aClass];
    classInfo.mClassName = aClass;
    classInfo.mParentClassName = aParentClass;
    
    if (aParentClass != std::string()) {
        // aParentClass
        classInfo.mParentClassInfo = &sAllClass[aParentClass];
    } else {
        classInfo.mParentClassInfo = nullptr;
    }
}
