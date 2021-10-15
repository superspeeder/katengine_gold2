#pragma once

#include "kat/core.hpp"
#include "kat/systemctx.hpp"
#include "kat/event.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

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

    class Monitor {
    public:
        Monitor(size_t id);
        ~Monitor();

        GLFWmonitor* getHandle();

    private:
        GLFWmonitor* monitor;

        RAII_COUNTER(glfw_counter) glfw_RC();
    };

    const std::string kDefaultWindowTitle = "Window";
    const glm::ivec2 kDefaultWindowSize = { 800, 800 };
    const std::unordered_map<int32_t, int32_t> kDefaultWindowHints = {
        { GLFW_RESIZABLE, true },
        { GLFW_VISIBLE, true},
        { GLFW_DECORATED, true},
        { GLFW_FOCUSED, true},
        { GLFW_AUTO_ICONIFY, true},
        { GLFW_FLOATING, false},
        { GLFW_MAXIMIZED, false},
        { GLFW_CENTER_CURSOR, true},
        { GLFW_TRANSPARENT_FRAMEBUFFER, false},
        { GLFW_FOCUS_ON_SHOW, true},
        { GLFW_SCALE_TO_MONITOR, false},
        { GLFW_RED_BITS, 8},
        { GLFW_GREEN_BITS, 8},
        { GLFW_BLUE_BITS, 8},
        { GLFW_ALPHA_BITS, 8},
        { GLFW_DEPTH_BITS, 24},
        { GLFW_STENCIL_BITS, 8},
        { GLFW_ACCUM_RED_BITS, 0},
        { GLFW_ACCUM_GREEN_BITS, 0},
        { GLFW_ACCUM_BLUE_BITS, 0},
        { GLFW_ACCUM_ALPHA_BITS, 0},
        { GLFW_AUX_BUFFERS, 0},
        { GLFW_SAMPLES, 0},
        { GLFW_REFRESH_RATE, GLFW_DONT_CARE},
        { GLFW_STEREO, false},
        { GLFW_SRGB_CAPABLE, true},
        { GLFW_DOUBLEBUFFER, true},
        { GLFW_CLIENT_API, GLFW_OPENGL_API},
        { GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API},
        { GLFW_CONTEXT_VERSION_MAJOR, 4},
        { GLFW_CONTEXT_VERSION_MINOR, 5},
        { GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS},
        { GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_ANY_RELEASE_BEHAVIOR},
        { GLFW_OPENGL_FORWARD_COMPAT, true},
        { GLFW_OPENGL_DEBUG_CONTEXT, kDebugMode},
        { GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
        { GLFW_COCOA_RETINA_FRAMEBUFFER, true},
        { GLFW_COCOA_GRAPHICS_SWITCHING, false}
    };

    const std::unordered_map<int32_t, std::string> kDefaultWindowStringHints = {
        { GLFW_COCOA_FRAME_NAME, "" },
        { GLFW_X11_CLASS_NAME, "" },
        { GLFW_X11_INSTANCE_NAME, "" }
    };

    struct WindowConfig {
        std::string title = kat::kDefaultWindowTitle;
        glm::ivec2 size = kat::kDefaultWindowSize;
        std::unordered_map<int32_t, int32_t> hints = kat::kDefaultWindowHints;
        std::unordered_map<int32_t, std::string> stringHints = kat::kDefaultWindowStringHints;

        Monitor* monitor = nullptr;
    };

    class Window {
    public:
        Window();
        ~Window();
    private:
        RAII_COUNTER(glfw_counter) glfw_RC();

        WindowConfig windowCfg;

        GLFWwindow* window;
    };


}