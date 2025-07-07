// this is for Apple MacOS only
#ifdef __APPLE__
#include "ResourcePath.h"
#import <Foundation/Foundation.h>

std::string game::getResourcePath(const std::string &relativePath)
{
    NSBundle *mainBundle = [NSBundle mainBundle];
    NSString *resourcePath = [mainBundle pathForResource:@(relativePath.c_str()) ofType:nil];

    if (resourcePath == nil)
    {
        std::cerr << "Error: File '" << relativePath << "' not found." << std::endl;
        return "";
    }

    return [resourcePath UTF8String];
}
#endif