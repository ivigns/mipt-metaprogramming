#pragma once

#include <iostream>

// PrintArgs

void PrintArgs(std::ostream& out) {
    out << "no args" << std::endl;
}

template <class Arg>
void PrintArgs(std::ostream& out, const Arg& arg) {
    out << arg << std::endl;
}

template <class Arg, class... Args>
void PrintArgs(std::ostream& out, const Arg& arg, const Args&... args) {
    out << arg << ", ";
    PrintArgs(out, args...);
}