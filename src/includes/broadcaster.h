#pragma once
#include "function.h"
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <mutex>

namespace Subscriptions {
    class Broadcaster {
    public:
        Broadcaster(Broadcaster const&) = delete;
        Broadcaster& operator=(Broadcaster const&) = delete;

        static std::shared_ptr<Broadcaster> getInstance() {
            std::lock_guard<std::mutex> lock(_mutex);
            if (!_instance) {
                _instance = std::shared_ptr<Broadcaster>(new Broadcaster);
            }
            return _instance;
        }

        template <class... Args>
        static void send(const std::string& eventId, Args&&...args) {
            if (!exists(eventId)) {
                return;
            }

            using FunctionType = void(typename std::remove_reference<Args>::type...);

            for (auto&& fun : _holders.at(eventId)) {
                if (const auto&& baseFunc = fun->cast<BaseFunction<FunctionType>>()) {
                    baseFunc->call(std::forward<Args>(args)...);
                }
            }
        }

        static void add(const std::string& eventId, const PFunction& fun) {
            _holders[eventId].emplace_back(fun);
        }

        static void remove(const std::string& eventId, const PFunction& fun) {
            if (!exists(eventId)) {
                return;
            }

            auto& arr = _holders.at(eventId);
            const auto& itr = std::find(std::begin(arr), std::end(arr), fun);
            if (itr == std::end(arr)) {
                return;
            }
            arr.erase(itr);
            if (arr.empty()) {
                _holders.erase(eventId);
                return;
            }
            _holders[eventId] = arr;
        }

    private:
        static bool exists(const std::string& eventId) {
            return _holders.count(eventId) > 0;
        }

        Broadcaster() = default;

    private:
        static std::map<std::string, std::vector<PFunction>> _holders;
        static std::shared_ptr<Broadcaster> _instance;
        static std::mutex _mutex;
    };
    using PBroadcaster = std::shared_ptr<Broadcaster>;

    std::map<std::string, std::vector<PFunction>> Broadcaster::_holders;
    std::shared_ptr<Broadcaster> Broadcaster::_instance = nullptr;
    std::mutex Broadcaster::_mutex;
}
