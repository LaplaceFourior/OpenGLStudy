#pragma once

#include <iostream>
#include <string.h>

class FileSystem
{
public:
    static std::string RelativePath(const std::string& filePath);
};