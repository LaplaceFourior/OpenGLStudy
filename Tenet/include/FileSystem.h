#pragma once

#include <iostream>
#include <string.h>

namespace TenetEngine {

class FileSystem
{
public:
    static std::string RelativePath(const std::string& filePath);
};

}