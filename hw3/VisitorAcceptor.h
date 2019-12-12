#pragma once

#include <string>
#include <vector>
#include <random>

class Circle;
class Square;

// Visitor

class Writer {
public:
    virtual std::string Visit(Circle*) = 0;
    virtual std::string Visit(Square*) = 0;

    virtual std::string VisitorType() = 0;
};

// Acceptor

class Shape {
public:
    /// @return     String template to be rendered by functor
    virtual std::string Accept(Writer*) = 0;

    virtual std::string AcceptorType() = 0;
};

// Concrete acceptors

class Circle : public Shape {
public:
    Circle(double radius, bool is_mirrored) : radius_(radius), is_mirrored_(is_mirrored) {}

    std::string Accept(Writer* writer) override {
        return writer->Visit(this);
    }

    std::string AcceptorType() override {
        return "Circle";
    }

    double GetRadius() {
        return radius_;
    }

    bool GetIsMirrored() {
        return is_mirrored_;
    }

private:
    double radius_;
    bool is_mirrored_;
};

class Square : public Shape {
public:
    enum EReferencePoint {
        center_,
        top_left_corner_,
        bottom_right_corner
    };

    Square(double side, EReferencePoint ref_point) : side_(side), ref_point_(ref_point) {}

    std::string Accept(Writer* writer) override {
        return writer->Visit(this);
    }

    std::string AcceptorType() override {
        return "Square";
    }

    double GetSide() {
        return side_;
    }

    EReferencePoint GetRefPoint() {
        return ref_point_;
    }

private:
    double side_;
    EReferencePoint ref_point_;
};

// Concrete visitors

class XMLWriter : public Writer {
public:
    XMLWriter(int xml_version, std::vector<std::string>&& users) : xml_version_(xml_version), users_(users) {}

    std::string Visit(Circle* circle) override {
        return "<?xml version=\"" + std::to_string(xml_version_) + ".0\" encoding=\"UTF-8\"?>\n"
               "<shape>\n"
               "    <type>circle</type>\n"
               "    <radius>" + std::to_string(circle->GetRadius()) + "</radius>\n"
               "    <x>{}</x>\n"
               "    <y>{}</y>\n"
               "</shape>\n";
    }
    std::string Visit(Square* square) override {
        return "<?xml version=\"" + std::to_string(xml_version_) + ".0\" encoding=\"UTF-8\"?>\n"
               "<shape>\n"
               "    <type>square</type>\n"
               "    <side>" + std::to_string(square->GetSide()) + "</side>\n"
               "    <x>{}</x>\n"
               "    <y>{}</y>\n"
               "</shape>\n";
    }

    std::string VisitorType() override {
        return "XMLWriter";
    }

    const std::vector<std::string>& GetUsers() {
        return users_;
    }

private:
    int xml_version_;
    std::vector<std::string> users_;
};

class JsonWriter : public Writer {
public:
    std::string Visit(Circle* circle) override {
        std::uniform_real_distribution distribution(0.1, 3.0);
        render_time_ = distribution(random_engine_);
        return "{\n"
               "    \"shape\": {\n"
               "        \"type\": \"circle\"\n"
               "        \"radius\": " + std::to_string(circle->GetRadius()) + "\n"
               "        \"x\": {}\n"
               "        \"y\": {}\n"
               "    }\n"
               "}\n";
    }
    std::string Visit(Square* square) override {
        std::uniform_real_distribution distribution(0.1, 3.0);
        render_time_ = distribution(random_engine_);
        return "{\n"
               "    \"shape\": {\n"
               "        \"type\": \"square\"\n"
               "        \"side\": " + std::to_string(square->GetSide()) + "\n"
               "        \"x\": {}\n"
               "        \"y\": {}\n"
               "    }\n"
               "}\n";
    }

    std::string VisitorType() override {
        return "JsonWriter";
    }

    double GetLastRenderTime() {
        return render_time_;
    }

private:
    double render_time_{0.0};
    std::default_random_engine random_engine_;
};
