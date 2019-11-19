#pragma once

#include "TypeList.h"

// GenScatterHierarchy

template <class UnitType, template <class> class Unit>
struct GenScatterHierarchy
    : public Unit<UnitType>
{
};

template <class H, class... T, template <class> class Unit>
struct GenScatterHierarchy<TypeList<H, T...>, Unit>
    : public GenScatterHierarchy<H, Unit>
    , public GenScatterHierarchy<TypeList<T...>, Unit>
{
};

template <class H, class T, template <class> class Unit>
struct GenScatterHierarchy<TypeList<H, T>, Unit>
    : public GenScatterHierarchy<H, Unit>
    , public GenScatterHierarchy<T, Unit>
{
};

// GenLinearHierarchy

template <class UnitList, template <class, class, class...> class Unit, class Root, class... Tools>
struct GenLinearHierarchy;

template <class H, class... T, template <class, class, class...> class Unit, class Root, class... Tools>
struct GenLinearHierarchy<TypeList<H, T...>, Unit, Root, Tools...>
    : public Unit<TypeList<T...>, Root, Tools...>
{
};

template <class H, template <class, class, class...> class Unit, class Root, class... Tools>
struct GenLinearHierarchy<TypeList<H>, Unit, Root, Tools...>
    : Root
{
};
