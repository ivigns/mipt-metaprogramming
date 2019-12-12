#pragma once

#include <memory>

template <class ReturnType, class... Args>
class IFunctor {
public:
    virtual ~IFunctor() = default;
    virtual ReturnType operator()(Args...) = 0;
};

template <class Func, class ReturnType, class... Args>
class FunctorImpl : public IFunctor<ReturnType, Args...> {
public:
    explicit FunctorImpl(const Func& function) : function_(&function) {}
    ReturnType operator()(Args... args) override {
        return (*function_)(args...);
    }
private:
    Func* function_;
};

template <class ReturnType, class... Args>
class Functor : public IFunctor<ReturnType, Args...> {
public:
    template <class Func>
    explicit Functor(const Func& function) : impl_(std::make_shared<FunctorImpl<Func, ReturnType, Args...>>(function)) {}

    ReturnType operator()(Args... args) override {
        return impl_->operator()(args...);
    }

private:
    std::shared_ptr<IFunctor<ReturnType, Args...>> impl_;
};
