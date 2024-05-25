#include "Visitor.h"
#include "Geometry.h"
#include "Strategy.h"
#include "Properties.h"
#include <iostream>
#include <sstream>

namespace visitor
{
	visitor::GeometryPrinter::GeometryPrinter(std::shared_ptr<strategy::IOutputStrategy> strategy)
		:inherited{ std::move(strategy) }
	{
	}

	void visitor::GeometryPrinter::visit(const geometry::Offset& offset)
	{
		print("offset", offset);
	}
	void visitor::GeometryPrinter::visit(const geometry::Skew& skew)
	{
		print("skew", skew);
	}

	void visitor::GeometryPrinter::visit(const geometry::Geometry& geometry)
	{
		print("geometry", geometry);
	}

	template<typename T>
	inline void GeometryPrinter::print(const std::string& name, const T& component) const {
		std::stringstream oss{};
		oss << "\"" << name << "\" : {\n";
		auto separator{ false };
		for (const auto& property : component.properties()) {
			if (separator)
				oss << ",";
			oss << property->name() << " : " << property->toString();
			separator = true;
		}
		oss << "}\n";
		inherited::print(oss);
	}


	visitor::IGeometryVisitor::IGeometryVisitor(std::shared_ptr<strategy::IOutputStrategy> strategy)
		: outputStrategy_{ std::move(strategy) }
	{
	}

	void visitor::IGeometryVisitor::print(const std::stringstream& stream) const
	{
		if (outputStrategy_)
			outputStrategy_->print(stream.str());
	}
}


