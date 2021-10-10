#pragma once

#include "kat/core.hpp"

namespace kat {

    class ExecutionContext {
    public:
        ExecutionContext(int argc, const char** argv);

        int getExitCode();
        void setExitCode(int code);

        const std::vector<std::string>& getArgs();


    private:

        int m_ExitCode = EXIT_SUCCESS;
        std::vector<std::string> m_Args;
    };
}