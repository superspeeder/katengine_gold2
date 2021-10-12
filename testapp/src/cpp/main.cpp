#include <kat/entry_point.hpp>
#include <spdlog/spdlog.h>
#include <kat/app.hpp>

class TestApp : public kat::App {
public:
    TestApp(kat::ExecutionContext* ctx) : kat::App(ctx) {
        m_LifecycleEventManager->addListener<kat::AppConfigureEvent>([this](kat::AppConfigureEvent* evt) {
            spdlog::info("Configureisms");
        });
    }
};

void run_app(kat::ExecutionContext* ctx) {
    spdlog::info("Hello World!");

    TestApp* a = new TestApp(ctx);
    a->run();

    ctx->setExitCode(-4);
}