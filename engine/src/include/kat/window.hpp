#pragma once

#include "kat/core.hpp"
#include "kat/systemctx.hpp"
#include "kat/event.hpp"
#include <GLFW/glfw3.h>

namespace kat {

    struct glfw_counter_oninc {
        inline void operator()(size_t v) {
            spdlog::info("E");
            if (v == 1) {
                glfwInit();
                spdlog::info("Initialized GLFW");
            }
        };
    };
    struct glfw_counter_ondec {
        inline void operator()(size_t v) {
            spdlog::info("EE");

            if (v == 0) {
                glfwTerminate();
                spdlog::info("Terminated GLFW");
            }
        };
    };

    inline watched_counter<size_t, glfw_counter_oninc, glfw_counter_ondec> glfw_counter{};

    class Window {
    public:
        Window();
        ~Window();
    private:
        raii_counter<decltype(glfw_counter)> glfw_RC();
    };


}