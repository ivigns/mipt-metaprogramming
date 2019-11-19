#pragma once

#include "GenHierarchy.h"
#include "Util.h"

#include <memory>

template <class Product>
class FactoryUnit {
public:
    virtual ~FactoryUnit() = default;
    virtual std::shared_ptr<Product> DoGet(Product*) = 0;
};

template <class ProductList>
class AbstractFactoryImpl
    : private GenScatterHierarchy<ProductList, FactoryUnit>
{
public:
    template <class Product>
    std::shared_ptr<Product> Get() {
        FactoryUnit<Product>* base = this;
        Product* p = nullptr;
        return base->DoGet(p);
    }
};

template <class ProductList, class Root, class BaseProductList>
class ConcreteFactoryUnit
    : public GenLinearHierarchy<ProductList, ConcreteFactoryUnit, Root, BaseProductList>
{
public:
    using Product = typename ProductList::Head;
    using BaseProduct = typename FindBase<Product, BaseProductList>::Result;

    std::shared_ptr<BaseProduct> DoGet(BaseProduct*) override {
        return std::make_shared<Product>();
    }
};

template <class FactoryList>
class FactoryGetter {
public:
    using AbstractFactory = AbstractFactoryImpl<typename GetBaseProductList<FactoryList>::Result>;

    template <class Product>
    std::shared_ptr<AbstractFactory> GetFactory() {
        using ConcreteFactory = ConcreteFactoryUnit<typename FindProductList<Product, FactoryList>::Result,
            AbstractFactory, typename GetBaseProductList<FactoryList>::Result>;

        return std::make_shared<ConcreteFactory>();
    }
};