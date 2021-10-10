#include "kat/systemctx.hpp"

#ifdef ENTRYPOINT_DEFINED
#error "Entry point already defined"
#else
#define ENTRYPOINT_DEFINED

#ifndef ENTRYPOINT_NAME
#define ENTRYPOINT_NAME run_app
#endif

void ENTRYPOINT_NAME(kat::ExecutionContext* ctx);


int main(int argc, const char** argv) {
	kat::ExecutionContext* ctx = new kat::ExecutionContext(argc, argv);

	ENTRYPOINT_NAME(ctx);

	return ctx->getExitCode();
};

#endif