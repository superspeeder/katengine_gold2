#include "kat/event.hpp"

namespace kat {

    EventLayer::EventLayer(int idx) {
        m_Index = idx;
    }

    int EventLayer::getIndex() {
        return m_Index;
    };
   
    bool EventLayer::operator<(const EventLayer& rhs) const {
        return m_Index < rhs.m_Index;
    }


    void EventLayer::addListener(std::type_index ti, PFNinternaleventfun fun) {
        if (m_Listeners.find(ti) == m_Listeners.end()) {
            m_Listeners.emplace(ti); // create vector if it doesn't exist
        }

        m_Listeners[ti].push_back(fun);
    }

    std::vector<PFNinternaleventfun>& EventLayer::getListeners(std::type_index ti) {
        if (m_Listeners.find(ti) == m_Listeners.end()) {
            m_Listeners.emplace(ti); // create vector if it doesn't exist
        }
        return m_Listeners[ti];
    }


    void OnDemandEventManager::post(std::type_index ti, BaseEvent* evt) {
        for (EventLayer* el : m_Layers) {
            for (PFNinternaleventfun &ief : el->getListeners(ti)) {
                ief(evt);
            }

            if (evt->is_canceled()) {
                break;
            }
        }
    };

    EventManager::EventManager() {

    }

    EventManager::~EventManager() {

    }

    void AsyncEventManager::post(std::type_index ti, BaseEvent* evt) {
        std::lock_guard<std::mutex> lockg(m_EQMutex);
        m_EventQueue.push({ ti, evt });
        m_EAVcv.notify_one(); // tell 1 of the waiting threads that an event is available
    };

    std::pair<std::type_index, BaseEvent*> AsyncEventManager::popEvent() {
        {
            std::lock_guard<std::mutex> lockg(m_EQMutex);
            if (!m_EventQueue.empty()) {
                return m_EventQueue.pop();
            }
        }
        std::unique_lock<std::mutex> eavcvlk(m_EAVcvMutex);
        while (true) {
            m_EAVcv.wait(eavcvlk);
            std::lock_guard<std::mutex> lockg(m_EQMutex);
            if (!m_EventQueue.empty()) { // prevent race condition where thread A is waiting in this loop, but thread B just finished processing an event and grabbed the event this thread was notified for before this thread could
                return m_EventQueue.pop();
            }
        }
    };

    void event_thread(std::stop_token st, AsyncEventManager* evtm) {
        while (!stop_token.stop_requested()) {
            std::pair<std::type_index, BaseEvent*> evt = evtm->popEvent();
            std::vector<std::vector<PFNinternaleventfun> > listeners;
            {
                std::lock_guard<std::mutex> lk(m_LayersMutex); // safely grab all the listeners
                for (EventLayer* el : m_Layers) {
                    listeners.push_back(el->getListeners(evt.first));
                }
            }

            for (const auto& vec : listeners) {
                for (PFNinternaleventfun& f : vec) {
                    f(evt.second);
                }
                if (evt.second->is_canceled()) {
                    break;
                }
            }
            // finished processing of event
            std::this_thread::yield(); // yield to others execution to ensure other threads get to run
        }
    }




}