#include "kat/app.hpp"
#include <thread>
#include <chrono>


namespace kat {

    const std::chrono::duration<double> SIXTIETH_SECOND(1.0 / 60.0);

    App::App(ExecutionContext* ctx) {
        m_LifecycleEventManager = new OnDemandEventManager();
        m_EventManager = new AsyncEventManager();
    }

    App::~App() {
        
    }

    bool App::isOpen() noexcept {
        return m_Metrics.frameCount < 5000000;
    }

    void App::run() {
        internalConfigure();
        m_LifecycleEventManager->post(new AppConfigureEvent(this));
        internalCreate();
        m_LifecycleEventManager->post(new AppCreateEvent(this));
        mainloop();

        preDestroy();
        m_LifecycleEventManager->post(new AppDestroyEvent(this));
        postDestroy();

        m_EventManager->end_after_done();
    }

    void App::internalConfigure() {

    }

    void App::internalCreate() {

    }

    const AppMetrics& App::getMetrics() const noexcept {
        return m_Metrics;
    }

    void App::mainloop() {
        using namespace std::chrono_literals;

        preMainloop();

        std::chrono::high_resolution_clock hrc;
        
        std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<double, std::nano> > now = hrc.now();
        std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<double, std::nano> > lastFrame = now - SIXTIETH_SECOND;

        while (isOpen()) {
            std::chrono::duration<double> dt__ = now - lastFrame;
            double dt = dt__.count();

            double fps = 1.0 / dt;
            m_Metrics.averageFPS = (m_Metrics.averageFPS * (((double)m_Metrics.frameCount) / ((double)m_Metrics.frameCount + 1.0))) + ((1.0 / ((double)m_Metrics.frameCount + 1.0)) * fps);

            preUpdate(dt);
            m_LifecycleEventManager->post(new AppUpdateEvent(this, dt));
            postUpdate(dt);

            preRender(dt);
            m_LifecycleEventManager->post(new AppRenderEvent(this, dt));
            postRender(dt);

            m_Metrics.frameCount++;
            lastFrame = now;
            now = hrc.now();
        }

        postMainloop();
    }

    void App::preMainloop() {

    }

    void App::postMainloop() {

    }

    void App::preDestroy() {

    }

    void App::postDestroy() {

    }

    void App::preUpdate(double dt) {

    }

    void App::postUpdate(double dt) {

    }

    void App::preRender(double dt) {

    }

    void App::postRender(double dt) {

    }



}