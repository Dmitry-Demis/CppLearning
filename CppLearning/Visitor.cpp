#include "Visitor.h"
#include "Geometry.h"
#include "Strategy.h"
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
				oss << ",\n";
			oss << "\t\"" << property->name() << "\" : " << property->toString();
			separator = true;
		}
		oss << "\n}";

		// Вызываем для каждого компонента внутри Geometry
		if constexpr (std::is_base_of_v<geometry::Component, T> && std::is_same_v<T, geometry::Geometry>) {
			const auto& comps = component.components();
			for (const auto& [index, comp] : comps) {
				oss << ",\n";
				print(std::to_string(index.hash_code()), *comp);
			}
		}
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


