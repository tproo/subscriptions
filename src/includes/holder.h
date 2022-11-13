#pragma once
#include "function.h"
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "broadcaster.h"

namespace Subscriptions {
    class Holder : public std::enable_shared_from_this<Holder> {
    public:
        void subscribe(const std::string& eventId, const PFunction& fun) {
            _impl[eventId].emplace_back(fun);
            Broadcaster::getInstance()->add(eventId, fun);
        }

        void reset() {
            for (auto&& itr = std::begin(_impl); itr != std::end(_impl); itr++) {
                for (const auto& fun : itr->second) {
                    Broadcaster::getInstance()->remove(itr->first, fun);
                }
            }
            _impl.clear();
        }

    private:
        std::map<std::string, std::vector<PFunction>> _impl;
    };
}