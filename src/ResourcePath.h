#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

namespace game
{
/**
 * \brief Get absolute path of file specified, cross-platform
 * \param relativePath file relative to `res/` directory
 * \return The absolute file path
 */
std::string getResourcePath(const std::string &relativePath);
} 