#include "Visitor.h"
#include "Geometry.h"

#include <iostream>


void visitor::GeometryPrinter::visit(const geometry::Offset& offset)
{
	std::cout << R"("offset" : {)" << '\n';
	auto separator{ false };
	for (const auto& property: offset.properties())
	{
		if (separator)
			std::cout << ",";
		std::cout << property->name() << " : " << property->toString();
		separator = true;
	}		
	std::cout << "}\n";

}
