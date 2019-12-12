#pragma once

class EmptyType {};

struct EmptyList {};

template <class H, class... T>
struct TypeList {
    using Head = H;
    using Tail = TypeList<T...>;
};

template <class H>
struct TypeList<H> {
    using Head = H;
    using Tail = EmptyList;
};