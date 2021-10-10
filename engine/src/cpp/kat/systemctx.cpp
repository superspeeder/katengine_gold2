#include "kat/systemctx.hpp"

namespace kat {
    ExecutionContext::ExecutionContext(int argc, const char** argv) {
        for (int i = 0; i < argc; i++) {
            m_Args.push_back(argv[i]);
        }
    }

    int ExecutionContext::getExitCode() {
        return m_ExitCode;
    }

    void ExecutionContext::setExitCode(int code) {
        m_ExitCode = code;
    }


    const std::vector<std::string>& ExecutionContext::getArgs() {
        return m_Args;
    }

}