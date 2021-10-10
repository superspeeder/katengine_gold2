#pragma once

#include "kat/core.hpp"
#include "kat/systemctx.hpp"

namespace kat {
	class App {
	public:
		
		App(ExecutionContext* ctx);
		virtual ~App();

		void run();
		
		virtual void create() = 0;
		virtual void update(double dt) = 0;
		inline virtual void render(double dt) {}; // do nothing by default (allow internal rendering systems to handle everything)
		virtual void destroy() = 0;

		bool isOpen();
		ExecutionContext* getExecContext();


	private:

		/*
		Order:

		preCreate
		create
		postCreate
		mainloop
			preUpdate
			update
			postUpdate
			preRender
			internalRender1
			render
			internalRender2
			postRender
		preDestroy
		destroy
		postDestroy
		*/


		void preCreate();
		void postCreate();
		void mainloop();
		void preUpdate(double dt);
		void postUpdate(double dt);
		void preRender(double dt);
		void internalRender1(double dt);
		void internalRender2(double dt);
		void postRender(double dt);

		ExecutionContext* m_ExecCtx;

	};
}