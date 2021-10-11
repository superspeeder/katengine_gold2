#include "kat/app.hpp"
#include <thread>
#include <chrono>

namespace kat {

    TestEvent::TestEvent(float n) : num(n) {

    }

    App::App(ExecutionContext* ctx) {
        m_OnDemandEventManager = new OnDemandEventManager();
        m_AsyncEventManager = new AsyncEventManager();
    }

    App::~App() {
        
    }

    void App::run() {
        using namespace std::chrono_literals;
        m_AsyncEventManager->post(new TestEvent(1.0f));
        m_AsyncEventManager->post(new TestEvent(2.0f));
        m_AsyncEventManager->post(new TestEvent(3.0f));
        m_AsyncEventManager->post(new TestEvent(4.0f));
        m_AsyncEventManager->post(new TestEvent(5.0f));
        m_AsyncEventManager->post(new TestEvent(6.0f));
        m_AsyncEventManager->post(new TestEvent(7.0f));
        m_AsyncEventManager->post(new TestEvent(8.0f));
        m_AsyncEventManager->post(new TestEvent(9.0f));
        m_AsyncEventManager->end_after_done();
    }

}