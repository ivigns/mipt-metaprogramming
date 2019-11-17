#include "AbstractFactoryGetter.h"
#include "TypeList.h"
#include "Utils.h"

class A {};

class B {};

class C {};

class J : public A {};

int main() {
    std::cout << IsDerived<J, A>::value << std::endl;
    AbstractFactoryGetter<TypeList<A, B, C>> factoryGetter;
    A a = factoryGetter.GetFactory<A>();

    return 0;
}
