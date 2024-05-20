// CppLearning.cpp : Here I learn how to use C++
//

#include "Geometry.h"
#include "Visitor.h"
#include "Strategy.h"
#include <vector>
#include <utility>

int main() {

    geometry::Skew off{ 13.0, 17.0 };
    visitor::GeometryPrinter printer{std::make_shared<strategy::ConsoleOutputStrategy>()};
    
    std::vector<std::shared_ptr<geometry::Component>> v;
   
    v.emplace_back(std::make_shared<geometry::Offset>(off.x(), off.y()));
    v.emplace_back(std::make_shared<geometry::Skew>(15, 22));

    geometry::Geometry g{};
    g.accept(printer);

    

    return 0;
}


