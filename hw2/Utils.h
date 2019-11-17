#pragma once

#include <iostream>

template <class T, class U>
class IsDerived {
private:
    using Small = char;
    using Big = struct { char value[2]; };
    static Small Test(const U&) {}
    static Big Test(...) {}
    static T MakeT() {}

public:
    static constexpr bool value = sizeof(Test(MakeT())) == sizeof(Small);
};

template <class TList>
class TypeListPrinter {
public:
    static void Print() {
        std::cout << typeid(typename TList::Head).name() << " ";
        TypeListPrinter<typename TList::Tail>::Print();
    }
};

template <>
class TypeListPrinter<EmptyList> {
public:
    static void Print() {
        std::cout << std::endl;
    }
};