// CppLearning.cpp : Here I learn how to use C++
//

#include "Geometry.h"
#include "Visitor.h"

int main() {

    geometry::Offset off{ 10.0,20.0 };
    visitor::GeometryPrinter printer{};
    off.accept(printer);
    off.x(17);
    off.accept(printer);

    return 0;
}


