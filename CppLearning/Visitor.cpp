#include "Visitor.h"
#include "Geometry.h"

#include <iostream>


void visitor::GeometryPrinter::visit(const geometry::Offset& offset)
{
	for (const auto& property: offset.properties())
		std::cout << property->name() << " : " << property->toString() << '\n';
}
