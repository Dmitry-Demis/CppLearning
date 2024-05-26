// CppLearning.cpp : Here I learn how to use C++
//

#include "Geometry.h"
#include "Visitor.h"
#include "Strategy.h"
#include <vector>
#include <utility>

int main() {

    visitor::GeometryPrinter printer{_STD make_shared<strategy::ConsoleOutputStrategy>()};

   auto geometry = builder::Builder<geometry::Geometry>{}
        .setComponent<geometry::Offset>(3.0, 12)
        .setComponent<geometry::Skew>(10.0, 15.)
        .build();

    geometry->accept(printer);

    auto r = builder::Builder<geometry::Geometry>{ geometry }
               .setComponent<geometry::Skew>(5.0, 2.0)
               .build();
    geometry->accept(printer);


    return 0;
}


