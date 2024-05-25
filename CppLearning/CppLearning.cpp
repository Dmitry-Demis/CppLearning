// CppLearning.cpp : Here I learn how to use C++
//

#include "Geometry.h"
#include "Visitor.h"
#include "Strategy.h"
#include <vector>
#include <utility>

int main() {

    visitor::GeometryPrinter printer{std::make_shared<strategy::ConsoleOutputStrategy>()};

	geometry::Geometry geometry = geometry::Geometry::Builder{}
	                              .setComponent<geometry::Offset>(30.0, 40.0)
	                              .setComponent<geometry::Skew>(10.0, 20.0)
	                              .build();
    geometry.accept(printer);

    geometry = geometry::Geometry::Builder{ geometry }
               .setComponent<geometry::Skew>(5.0, 2.0)
               .build();
    geometry.accept(printer);


    return 0;
}


