// this is for Windows and Linux only
#if defined(_WIN32) || defined(__linux__)
#include "ResourcePath.hpp"

std::string game::getResourcePath(const std::string &relativePath)
{
    return "res/" + relativePath;
}

#endif