#pragma once

#include "kat/core.hpp"
#include "kat/systemctx.hpp"
#include <typeindex>
#include <atomic>
#include <concepts>
#include <future>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

namespace kat {

    using PFNinternaleventfun = std::function<void(BaseEvent*)>;
    
    class BaseEvent {
    public:

        inline virtual void cancel() noexcept {
            KAT_DWARN("Attempted to cancel event which doesn't support cancelling");
        }; // no-op by default

        const inline virtual bool is_cancelable() const noexcept { return false; };
        inline virtual bool is_canceled() const noexcept { return false; };

    private:

    };

    class CancelableEvent : public BaseEvent {
    public:

        const inline virtual bool is_cancelable() const noexcept override { return true; };
        inline virtual bool is_canceled() const noexcept override { return m_Canceled; };

    private:
        std::atomic<bool> m_Canceled = false;
    };

    template <typename T>
    concept event_class = std::is_base_of_v<BaseEvent, T>;

    template <event_class T>
    constexpr bool is_event_cancelable() { return std::is_base_of_v<CancelableEvent, T> };

    class EventManager;

    class EventLayer {
    public:

        EventLayer(int idx);

        int getIndex();
        bool operator<(const EventLayer& rhs) const;

        void addListener(std::type_index ti, PFNinternaleventfun fun);

        template<event_class E>
        inline void addListener(std::function<void(E*)> fun) {
            addListener(std::type_index(typeid(E)), [&](BaseEvent* evt) {
                E* evt_ = reinterpret_cast<E*>(evt);
                fun(evt);
                });
        };

        std::vector<PFNinternaleventfun>& getListeners(std::type_index ti);

        template<event_class E>
        inline std::vector<PFNinternaleventfun>& getListeners() {
            return getListeners(std::type_index(typeid(E)));
        };

    private:

        int m_Index;
        EventManager* m_EventManager;
        std::unordered_map<std::type_index, std::vector<PFNinternaleventfun> > m_Listeners;

    };

    class EventManager {
    public:

        EventManager();
        virtual ~EventManager();

        virtual void post(std::type_index ti, BaseEvent* evt) = 0;

        template<event_class E>
        inline void post(E* evt) {
            post(std::type_index(typeid(E)), dynamic_cast<BaseEvent*>(evt));
        };

    protected:
        std::set<EventLayer*, ptr_less<EventLayer>> m_Layers;
        EventLayer* m_DefaultLayer;
    };

    /**
     * @brief Most basic event manager. synchronous and runs in-time
    */
    class OnDemandEventManager : public EventManager {
    public:

        virtual void post(std::type_index ti, BaseEvent* evt) override;

    private:

    };

    const size_t MAX_EVENT_THREADS = 10;


    /**
     * @brief 
     * 
     * Separate posted events are handled asynchronously, but within the handling of a single event the listeners and layers are called synchronously
     * This prevents slowdowns due to thread syncronization, but leverages the strengths of 
     * 
    */
    class AsyncEventManager : public EventManager {
    public:

        virtual void post(std::type_index ti, BaseEvent* evt) override;

        std::pair<std::type_index, BaseEvent*> popEvent(); // will wait for event if one doesn't exist

    private:
        thread_pool<MAX_EVENT_THREADS>* m_ThreadPool;
        std::mutex m_EQMutex;
        std::queue<std::pair<std::type_index, BaseEvent*> > m_EventQueue;
        std::condition_variable m_EAVcv;
        std::mutex m_EAVcvMutex;
        std::mutex m_LayersMutex;
    };

    void event_thread(std::stop_token st, AsyncEventManager* evtm);
}