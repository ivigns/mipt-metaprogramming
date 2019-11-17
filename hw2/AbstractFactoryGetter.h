#pragma once

template <class UnitType>
class FactoryUnit {
protected:
    static UnitType DoGet() {
        return UnitType();
    }
};

template <class GenTypeList, template <class> class Unit>
struct GenScatterFactoryHierarchy;

template <class H, class... T, template <class> class Unit>
class GenScatterFactoryHierarchy<TypeList<H, T...>, Unit>
    : public GenScatterFactoryHierarchy<H, Unit>
        , public GenScatterFactoryHierarchy<TypeList<T...>, Unit>
{
};

template <class H, class T, template <class> class Unit>
class GenScatterFactoryHierarchy<TypeList<H, T>, Unit>
    : public GenScatterFactoryHierarchy<H, Unit>
        , public GenScatterFactoryHierarchy<T, Unit>
{
};

template <class UnitType, template <class> class Unit>
struct GenScatterFactoryHierarchy
    : public Unit<UnitType>
{
};

template <class GenTL>
class AbstractFactoryGetter
    : GenScatterFactoryHierarchy<GenTL, FactoryUnit>
{
public:
    template <class UnitType>
    UnitType GetFactory() {
        FactoryUnit<UnitType>* baseUnit = this;
        return baseUnit->DoGet();
    }
};