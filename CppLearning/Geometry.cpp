#include "Geometry.h"

#include "Properties.h"
#include "Visitor.h"

namespace geometry
{
	std::set<std::shared_ptr<properties::IProperty>> Component::properties() const
	{
		return properties_;
	}
	void Component::addProperty(std::shared_ptr<properties::IProperty> property)
	{
		properties_.insert(std::move(property));
	}

	Offset::Offset(double x, double y) noexcept
		: x_{ x }, y_{ y }
	{
		addProperty(properties::makeProperty("x", x_));
		addProperty(properties::makeProperty("y", y_));
	}
	double Offset::x() const noexcept { return x_; }
	double Offset::y() const noexcept { return y_; }
	void Offset::x(double x) noexcept { x_ = x; }
	void Offset::y(double y) noexcept { y_ = y; }
	void Offset::accept(visitor::IGeometryVisitor& visitor) const
	{
		visitor.visit(*this);
	}



	Skew::Skew(double x, double y) noexcept
		: x_{ x }, y_{ y }
	{
		addProperty(properties::makeProperty("x", x_));
		addProperty(properties::makeProperty("y", y_));
	}
	double Skew::x() const noexcept
	{
		return x_;
	}
	double Skew::y() const noexcept
	{
		return y_;
	}
	void Skew::x(double x) noexcept
	{
		x_ = x;
	}
	void Skew::y(double y) noexcept
	{
		y_ = y;
	}
	void Skew::accept(visitor::IGeometryVisitor& visitor) const
	{
		visitor.visit(*this);
	}

	Geometry::Geometry()
	{
		addComponent<Offset>();
		addComponent<Skew>();
	}

	void Geometry::accept(visitor::IGeometryVisitor& visitor) const
	{
		visitor.visit(*this);
	}

	

	Geometry::Builder::Builder(Geometry geometry) noexcept
		: geometry_{std::move(geometry)}
	{
	}

	Geometry Geometry::Builder::build()
	{
		return std::move(geometry_);
	}
}


