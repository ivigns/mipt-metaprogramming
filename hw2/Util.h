#pragma once

// GetBaseList

/// if T is derived from U
template <class T, class U>
struct IsDerivedFrom {
private:
    using Small = char;
    using Big = struct { char value[2]; };
    static Small Test(const U&) {}
    static Big Test(...) {}
    static T MakeT() {}

public:
    static constexpr bool value = sizeof(Test(MakeT())) == sizeof(Small);
};

/// select A if first, B if !first
template <class A, class B, bool first>
struct Select;

template <class A, class B>
struct Select<A, B, true> {
    using Result = A;
};

template <class A, class B>
struct Select<A, B, false> {
    using Result = B;
};

/// get one out of two typelists, which contains elements that are base classes for elements of other list
template <class TL1, class TL2>
struct GetBaseList;

template <class H1, class... T1, class H2, class... T2>
struct GetBaseList<TypeList<H1, T1...>, TypeList<H2, T2...>> {
    using Result = typename Select<TypeList<H1, T1...>, TypeList<H2, T2...>, IsDerivedFrom<H2, H1>::value>::Result;
};

// IsIn

/// if elem is in typelist
template <class Elem, class TL>
struct IsIn;

template <class Elem, class... T>
struct IsIn<Elem, TypeList<Elem, T...>> {
    static constexpr bool value = true;
};

template <class Elem, class H, class... T>
struct IsIn<Elem, TypeList<H, T...>> {
    static constexpr bool value = IsIn<Elem, TypeList<T...>>::value;
};

template <class Elem>
struct IsIn<Elem, TypeList<Elem>> {
    static constexpr bool value = true;
};

template <class Elem, class H>
struct IsIn<Elem, TypeList<H>> {
    static constexpr bool value = false;
};

// FindBase

/// find base class of elem in typelist
template <class Elem, class TL>
struct FindBase;

template <class Elem, class H, class... T>
struct FindBase<Elem, TypeList<H, T...>> {
private:
    using Candidate = typename FindBase<Elem, TypeList<T...>>::Result;
public:
    using Result = typename Select<H, Candidate, IsDerivedFrom<Elem, H>::value>::Result;
};

template <class Elem, class H>
struct FindBase<Elem, TypeList<H>> {
public:
    using Result = typename Select<H, EmptyType, IsDerivedFrom<Elem, H>::value>::Result;
};

// GetBaseProductList

/// get typelist of products that are base classes for other products
template <class FactoryList>
struct GetBaseProductList;

template <class H, class... T>
struct GetBaseProductList<TypeList<H, T...>> {
private:
    using Candidate = typename GetBaseProductList<TypeList<T...>>::Result;
public:
    using Result = typename GetBaseList<H, Candidate>::Result;
};

template <class H>
struct GetBaseProductList<TypeList<H>> {
public:
    using Result = H;
};

// FindProductList

template <class Product, class FactoryList, bool found>
struct SearchProduct;

template <class Product, class H, class... T>
struct SearchProduct<Product, TypeList<H, T...>, false> {
    using Result = typename SearchProduct<Product, TypeList<T...>,
        IsIn<Product, typename TypeList<T...>::Head>::value>::Result;
};

template <class Product, class H, class... T>
struct SearchProduct<Product, TypeList<H, T...>, true> {
    using Result = H;
};

/// find typelist in FactoryList that contains Product
template <class Product, class FactoryList>
struct FindProductList {
    using Result = typename SearchProduct<Product, FactoryList,
        IsIn<Product, typename FactoryList::Head>::value>::Result;
};