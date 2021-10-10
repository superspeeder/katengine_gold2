#pragma once

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
        inline bool operator()(const T*& a, const T*& b) {
            return std::less<T>{}(*a, *b);
        };
    };

    template<size_t count>
    class thread_pool {
    public:
        template<typename... Args>
        inline thread_pool(std::function<void(std::stop_token, Args...)> f, Args... args) {
            for (size_t i = 0; i < count; i++) {
                threads.emplace_back(f, &args...);
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
