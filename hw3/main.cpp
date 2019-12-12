#include "TypeList.h"
#include "Functor.h"
#include "VisitorAcceptor.h"
#include "VisitDispatcher.h"

#include <iostream>

// For basic Functor

int Add5(int& a, std::string) {
    return (a += 5) - 5;
}

// Helpful functions

void RenderTemplate(const std::string& templ, double x, double y) {
    int x_pos = templ.find("{}");
    int y_pos = templ.find("{}", x_pos + 1);

    std::string_view part(templ.data(), x_pos);
    std::cout << part << x;
    part = std::string_view(templ.data() + x_pos + 2, y_pos - x_pos - 2);
    std::cout << part << y;
    part = std::string_view(templ.data() + y_pos + 2);
    std::cout << part;
    std::flush(std::cout);
}

inline void PrintXMLAnnounsement(const std::vector<std::string>& users) {
    std::cout << "These users are still using this outdated output: ";
    for (const auto& user : users) {
        std::cout << user << " ";
    }
    std::cout << "\n";
}

inline void PrintJsonRenderTime(double render_time) {
    std::cout << "Took " << render_time << " seconds to render.\n";
}

inline void MirrorCircle(bool is_mirrored, double& x, double& y) {
    if (is_mirrored) {
        x = -x;
        y = -y;
    }
}

inline void SquareRefPointToTopLeftCorner(Square::EReferencePoint ref_point, double side, double& x, double& y) {
    if (ref_point == Square::center_) {
        x -= side / 2;
        y -= side / 2;
    } else if (ref_point == Square::bottom_right_corner) {
        x -= side;
        y -= side;
    }
}

// VisitFunctor instantiations

template <>
class VisitFunctor<void, XMLWriter, Circle, std::string, double, double> : IFunctor<void, XMLWriter*, Circle*, std::string, double, double> {
public:
    void operator()(XMLWriter* writer, Circle* circle, std::string templ, double x, double y) override {
        std::cout << "Circle by XMLWriter.\n";
        PrintXMLAnnounsement(writer->GetUsers());
        MirrorCircle(circle->GetIsMirrored(), x, y);
        RenderTemplate(templ, x, y);
    }
};

template <>
class VisitFunctor<void, XMLWriter, Square, std::string, double, double> : IFunctor<void, XMLWriter*, Square*, std::string, double, double> {
public:
    void operator()(XMLWriter* writer, Square* square, std::string templ, double x, double y) override {
        std::cout << "Square by XMLWriter.\n";
        PrintXMLAnnounsement(writer->GetUsers());
        SquareRefPointToTopLeftCorner(square->GetRefPoint(), square->GetSide(), x, y);
        RenderTemplate(templ, x, y);
    }
};

template <>
class VisitFunctor<void, JsonWriter, Circle, std::string, double, double> : IFunctor<void, JsonWriter*, Circle*, std::string, double, double> {
public:
    void operator()(JsonWriter* writer, Circle* circle, std::string templ, double x, double y) override {
        std::cout << "Circle by JsonWriter.\n";
        PrintJsonRenderTime(writer->GetLastRenderTime());
        MirrorCircle(circle->GetIsMirrored(), x, y);
        RenderTemplate(templ, x, y);
    }
};

template <>
class VisitFunctor<void, JsonWriter, Square, std::string, double, double> : IFunctor<void, JsonWriter*, Square*, std::string, double, double> {
public:
    void operator()(JsonWriter* writer, Square* square, std::string templ, double x, double y) override {
        std::cout << "Square by JsonWriter.\n";
        PrintJsonRenderTime(writer->GetLastRenderTime());
        SquareRefPointToTopLeftCorner(square->GetRefPoint(), square->GetSide(), x, y);
        RenderTemplate(templ, x, y);
    }
};

int main() {
    Functor<int, int&, std::string> functor(Add5);
    int a = 5;
    std::cout << functor(a, "not used") << " " << a << std::endl;

    VisitDispatcher<Writer, TypeList<XMLWriter, JsonWriter>, Shape, TypeList<Circle, Square>, std::string, void, double, double> dispatcher;

    XMLWriter xml_writer(1, {"rick", "morty"});
    JsonWriter json_writer;
    Circle circle(6.0, true);
    Square square(2.0, Square::center_);

    dispatcher.Go(&xml_writer, &circle, 1.0, -2.0);
    dispatcher.Go(&xml_writer, &square, -3.0, 4.0);
    dispatcher.Go(&json_writer, &circle, 5.0, 6.0);
    dispatcher.Go(&json_writer, &square, -7.0, -8.0);

    VisitFunctor<void, JsonWriter, Square, double, double>()(&json_writer, &square, 5.0, 5.0);
    VisitFunctor<void, JsonWriter, Square>()(&json_writer, &square);

    return 0;
}
