#include "inpitUtilities.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace drw
{

namespace utilities
{

int convertScancodeToKey(int scancode, [[maybe_unused]] int mode)
{
    auto res = scancode;

#if defined(__linux__)
    switch (scancode)
    {
        case 9: res = GLFW_KEY_ESCAPE; break;
        case 111: res = GLFW_KEY_UP; break;
        case 116: res = GLFW_KEY_DOWN; break;
        default:
            std::cerr << "Cannot detect new key with scancode: " << scancode
                      << std::endl;
    }
#else
    std::cerr << "Cannot detect key for this platform" << std::endl;
#endif
    return res;
}

} // namespace utilities

} // namespace drw
