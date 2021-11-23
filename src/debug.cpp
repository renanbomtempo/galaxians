#include "moxxi/core.hpp"

namespace moxxi
{    
    void Debug::Warning(std::string msg)
    {
        Debug::Echo("WARNING::" + msg);
    }

    void Debug::Echo(std::string msg, bool endline /*=true*/)
    {
        std::cout << msg;
        if (endline)
            std::cout << std::endl;
    }

} // namespace moxxi
