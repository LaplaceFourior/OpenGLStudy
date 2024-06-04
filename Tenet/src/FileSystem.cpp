#include "FileSystem.h"

using namespace TenetEngine;

std::string FileSystem::RelativePath(const std::string& filePath)
{
    return PROJECT_PATH + std::string("/") + filePath;
}