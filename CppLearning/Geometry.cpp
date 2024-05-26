#include "Geometry.h"

#include "Properties.h"
#include "Visitor.h"

namespace geometry
{
	_STD set<_STD shared_ptr<properties::IProperty>> Component::properties() const
	{
		return properties_;
	}
	void Component::addProperty(_STD shared_ptr<properties::IProperty> property)
	{
		properties_.insert(_STD move(property));
	}

	Offset::Offset(const double x, const double y) noexcept
		: x_{ x }, y_{ y }
	{
		addProperty(properties::makeProperty("x", x_));
		addProperty(properties::makeProperty("y", y_));
	}
	double Offset::x() const noexcept { return x_; }
	double Offset::y() const noexcept { return y_; }
	void Offset::x(const double x) noexcept { x_ = x; }
	void Offset::y(const double y) noexcept { y_ = y; }
	void Offset::accept(visitor::IGeometryVisitor& visitor) const
	{
		visitor.visit(*this);
	}



	Skew::Skew(const double x, const double y) noexcept
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
	void Skew::x(const double x) noexcept
	{
		x_ = x;
	}
	void Skew::y(const double y) noexcept
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
}


