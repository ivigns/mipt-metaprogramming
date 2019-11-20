#include "FactoryGetter.h"
#include "TypeList.h"

#include <iostream>

struct Chair {
    Chair() { std::cout << "Chair\n"; }
};
struct Table {
    Table() { std::cout << "Table\n"; }
};

struct MetalChair : public Chair {
    MetalChair() { std::cout << "MetalChair\n"; }
};
struct MetalTable : public Table {
    MetalTable() { std::cout << "MetalTable\n"; }
};

struct WoodenChair : public Chair {
    WoodenChair() { std::cout << "WoodenChair\n"; }
};
struct WoodenTable : public Table {
    WoodenTable() { std::cout << "WoodenTable\n"; }
};

struct GermanMetalChair : public MetalChair {
    GermanMetalChair() { std::cout << "GermanMetalChair\n"; }
};
struct GermanMetalTable : public MetalTable {
    GermanMetalTable() { std::cout << "GermanMetalTable\n"; }
};

struct GermanWoodenChair : public WoodenChair {
    GermanWoodenChair() { std::cout << "GermanWoodenChair\n"; }
};
struct GermanWoodenTable : public WoodenTable {
    GermanWoodenTable() { std::cout << "GermanWoodenTable\n"; }
};

struct ChineseMetalChair : public MetalChair {
    ChineseMetalChair() { std::cout << "ChineseMetalChair\n"; }
};
struct ChineseMetalTable : public MetalTable {
    ChineseMetalTable() { std::cout << "ChineseMetalTable\n"; }
};

struct ChineseWoodenChair : public WoodenChair {
    ChineseWoodenChair() { std::cout << "ChineseWoodenChair\n"; }
};
struct ChineseWoodenTable : public WoodenTable {
    ChineseWoodenTable() { std::cout << "ChineseWoodenTable\n"; }
};


int main() {
    using Furniture = FactoryGetter<TypeList<
        TypeList<GermanMetalChair, GermanMetalTable>,
        TypeList<Chair, Table>,
        TypeList<WoodenChair, WoodenTable>,
        TypeList<ChineseWoodenChair, ChineseWoodenTable>,
        TypeList<MetalChair, MetalTable>,
        TypeList<GermanWoodenChair, GermanWoodenTable>,
        TypeList<ChineseMetalChair, ChineseMetalTable>
    >>;
    Furniture factoryGetter;

    std::shared_ptr<Furniture::AbstractFactory> metalFactory1 = factoryGetter.GetFactory<MetalTable>();
    std::shared_ptr<Chair> metalChair1 = metalFactory1->Get<Chair>();
    std::shared_ptr<Table> metalTable1 = metalFactory1->Get<Table>();
    std::shared_ptr<Chair> anotherMetalChair1 = metalFactory1->Get<MetalChair>();
    std::cout << "\n";

    std::shared_ptr<Furniture::AbstractFactory> metalFactory2 = factoryGetter.GetFactory<MetalChair>();
    std::shared_ptr<Chair> metalChair2 = metalFactory2->Get<Chair>();
    std::shared_ptr<Table> metalTable2 = metalFactory2->Get<Table>();
    std::cout << "\n";

    std::shared_ptr<Furniture::AbstractFactory> germanWoodenFactory = factoryGetter.GetFactory<GermanWoodenChair>();
    std::shared_ptr<Chair> germanWoodenchair = germanWoodenFactory->Get<Chair>();
    std::shared_ptr<Table> germanWoodenTable = germanWoodenFactory->Get<Table>();
    std::cout << "\n";

    return 0;
}
