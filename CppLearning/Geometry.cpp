#include "Geometry.h"

#include "Properties.h"
#include "Visitor.h"

namespace geometry
{
	void Component::addProperty(std::shared_ptr<properties::IProperty> property)
	{
		properties_.insert(std::move(property));
	}

	Offset::Offset(double x, double y) noexcept
		: x_{ x }, y_{ y }
	{
		
	}
	double Offset::x() const noexcept { return x_; }
	double Offset::y() const noexcept { return y_; }
	void Offset::x(double x) noexcept { x_ = x; }
	void Offset::y(double y) noexcept { y_ = y; }
	void Offset::accept(visitor::IGeometryVisitor& visitor) const
	{
		visitor.visit(*this);
	}

	std::set<std::shared_ptr<properties::IProperty>> Offset::properties() const
	{
		std::set<std::shared_ptr<properties::IProperty>> props{};
		auto propertyTuple
		{
			std::make_tuple(
				properties::makeProperty("x", x_),
				properties::makeProperty("y", y_)
			)
		};
		addProperties(propertyTuple, props);
		return props;
	}
}


