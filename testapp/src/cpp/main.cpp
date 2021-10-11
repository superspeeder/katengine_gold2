#include <kat/entry_point.hpp>
#include <spdlog/spdlog.h>
#include <kat/app.hpp>

class TestApp : public kat::App {
public:
    TestApp(kat::ExecutionContext* ctx) : kat::App(ctx) {
        m_AsyncEventManager->addListener<kat::TestEvent>([&](kat::TestEvent* e) {
            spdlog::info("Hello! {}", e->num);
            if (e->num >= 5.0f) {
                e->cancel();
            }
        });

        auto lyr = m_AsyncEventManager->createLayer(-3);
        lyr->addListener<kat::TestEvent>([&](kat::TestEvent* e) {
            spdlog::info("Fuck! {}", e->num);
        });
    }
};

void run_app(kat::ExecutionContext* ctx) {
    spdlog::info("Hello World!");

    TestApp* a = new TestApp(ctx);
    a->run();

    ctx->setExitCode(-4);
}