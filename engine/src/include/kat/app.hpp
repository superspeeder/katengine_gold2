#pragma once

#include "kat/core.hpp"
#include "kat/systemctx.hpp"
#include "kat/event.hpp"

namespace kat {

	struct AppMetrics {
		uint64_t frameCount;
		double averageFPS;
	};

	class App {
	public:
		
		App(ExecutionContext* ctx);
		virtual ~App();

		void run();
		
		bool isOpen() noexcept;
		ExecutionContext* getExecContext() const noexcept;

		const AppMetrics& getMetrics() const noexcept;


	protected:

		ExecutionContext* m_ExecCtx;
		OnDemandEventManager* m_LifecycleEventManager;
		AsyncEventManager* m_EventManager;

	private:

		void internalConfigure();
		void internalCreate();
		void mainloop();
		void preMainloop();
		void preUpdate(double dt);
		void postUpdate(double dt);
		void preRender(double dt);
		void postRender(double dt);
		void postMainloop();
		void preDestroy();
		void postDestroy();

		AppMetrics m_Metrics{};
	};

	class AppEvent : public BaseEvent {
	public:
		inline AppEvent(App* app) : m_App(app) {};

		inline App* getApp() { return m_App; };

	private:
		App* m_App;		
	};

	class AppConfigureEvent : public AppEvent {
	public:
		inline AppConfigureEvent(App* app) : AppEvent(app) {};
	};

	class AppCreateEvent : public AppEvent {
	public:
		inline AppCreateEvent(App* app) : AppEvent(app) {};
	};

	class AppRenderEvent : public AppEvent {
	public:
		inline AppRenderEvent(App* app, double dt_) : m_DeltaTime{dt_}, AppEvent(app) {};

		inline double dt() { return m_DeltaTime; };

	private:
		double m_DeltaTime;

	};

	class AppUpdateEvent : public AppEvent {
	public:
		inline AppUpdateEvent(App* app, double dt_) : m_DeltaTime{dt_}, AppEvent(app) {};

		inline double dt() { return m_DeltaTime; };

	private:
		double m_DeltaTime;
	};

	class AppDestroyEvent : public AppEvent {
	public:
		inline AppDestroyEvent(App* app) : AppEvent(app) {};
	};
}