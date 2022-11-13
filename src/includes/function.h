#pragma once
#include <memory>
#include <functional>

namespace Subscriptions {
    class Function : public std::enable_shared_from_this<Function> {
    public:
        virtual ~Function() = default;

        template <class T>
        std::shared_ptr<T> cast() {
            return std::dynamic_pointer_cast<T>(shared_from_this());
        }
    };
    using PFunction = std::shared_ptr<Function>;

    template <typename FunctionType>
    class BaseFunction : public Function {
    public:
        explicit BaseFunction(std::function<FunctionType> f)
                : _impl(std::move(f)) {
        }

        template <class... Args>
        void call(Args... args) {
            if (!_impl) {
                return;
            }
            _impl(args...);
        }

    private:
        std::function<FunctionType> _impl;
    };
}
