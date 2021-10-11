#pragma once

#include "kat/core.hpp"
#include "kat/systemctx.hpp"
#include "kat/event.hpp"

namespace kat {

	class TestEvent : public CancelableEvent {
	public:
		TestEvent(float n);

		float num;
	};

	class App {
	public:
		
		App(ExecutionContext* ctx);
		virtual ~App();

		void run();
		
		bool isOpen();
		ExecutionContext* getExecContext();


	protected:

		ExecutionContext* m_ExecCtx;
		OnDemandEventManager* m_OnDemandEventManager;
		AsyncEventManager* m_AsyncEventManager;
	};
}