#include <kat/entry_point.hpp>
#include <spdlog/spdlog.h>

void run_app(kat::ExecutionContext* ctx) {
    spdlog::info("Hello World!");
    ctx->setExitCode(-4);
}