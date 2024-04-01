#include "FileSystem.h"

std::string FileSystem::RelativePath(const std::string& filePath)
{
    return PROJECT_PATH + std::string("/") + filePath;
}