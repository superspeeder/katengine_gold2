#pragma once

#include <condition_variable>
#include <string>
#include <vector>
#include <concepts>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <spdlog/spdlog.h>
#include <thread>

namespace kat {

    template <typename T>
    struct ptr_less {
        inline bool operator()(const T* a, const T* b) const {
            return std::less<T>{}(*a, *b);
        };
    };

    template<size_t count>
    class thread_pool {
    public:
        template<typename... Args>
        inline thread_pool(std::function<void(std::stop_token)> f) {
            for (size_t i = 0; i < count; i++) {
                threads.emplace_back(f);
            }
        };

        inline void stop() {
            for (std::jthread& t : threads) {
                t.get_stop_source().request_stop();
            }
            for (std::jthread& t : threads) {
                if (t.joinable()) {
                    t.join();
                }
            }
        };

        inline void stop(std::condition_variable& var) {
            for (std::jthread& t : threads) {
                t.get_stop_source().request_stop();
            }

            var.notify_all();
            
            for (std::jthread& t : threads) {
                if (t.joinable()) {
                    t.join();
                }
            }
        };

    private:
        std::vector<std::jthread> threads;
    };

#ifdef KAT_DEBUG
    #define KAT_DWARN(msg) spdlog::warn(msg)
    #define KAT_DEBUG(msg) spdlog::debug(msg)
    #define KAT_TRACE(msg)
#else
    #ifdef KAT_TRACE
        #define KAT_DWARN(msg) spdlog::warn(msg)
        #define KAT_DEBUG(msg) spdlog::debug(msg)
        #define KAT_TRACE(msg) spdlog::trace(msg)
    #else
        #define KAT_DWARN(msg)
        #define KAT_DEBUG(msg)
        #define KAT_TRACE(msg)
    #endif
#endif
}
