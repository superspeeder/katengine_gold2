#include <kat/entry_point.hpp>
#include <spdlog/spdlog.h>
#include <kat/app.hpp>

class TestApp : public kat::App {
public:
    TestApp(kat::ExecutionContext* ctx) : kat::App(ctx) {
        m_LifecycleEventManager->addListener<kat::AppConfigureEvent>(&TestApp::configure, this);
        m_LifecycleEventManager->addListener<kat::AppCreateEvent>(&TestApp::create, this);
        m_LifecycleEventManager->addListener<kat::AppDestroyEvent>(&TestApp::destroy, this);
//        m_LifecycleEventManager->addListener<kat::AppUpdateEvent>(&TestApp::update, this);
    }

    void configure(kat::AppConfigureEvent* evt) {
        spdlog::info("Configureisms");
    };

    void create(kat::AppCreateEvent* evt) {
        spdlog::info("Create!");
    };

    void update(kat::AppUpdateEvent* evt) {

    };

    void destroy(kat::AppDestroyEvent* evt) {
        spdlog::info("Destroy! ran for {} frames", getMetrics().frameCount);
        spdlog::info("Average fps: {}", getMetrics().averageFPS);
    };
};

void run_app(kat::ExecutionContext* ctx) {
    spdlog::info("Hello World!");

    TestApp* a = new TestApp(ctx);
    a->run();
}
