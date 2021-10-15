#include "kat/window.hpp"

namespace kat {
    Window::Window() {

    }

    Window::~Window() {
        glfwDestroyWindow(window);
    }

    Monitor::Monitor(size_t id) {
        if (id == 0) {
            monitor = glfwGetPrimaryMonitor();
        } else {
            int count;
            GLFWmonitor** mons = glfwGetMonitors(&count);
            if (id < count) {
                monitor = mons[id];
            }
            else {
                monitor = glfwGetPrimaryMonitor();
            }
        }
    }

    Monitor::~Monitor() {
    }

}