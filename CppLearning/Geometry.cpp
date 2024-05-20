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
		addComponent<Offset>(10,20);
		addComponent<Skew>(20,10);
	}

	void Geometry::accept(visitor::IGeometryVisitor& visitor) const
	{
		visitor.visit(*this);
	}
	template<typename C, typename ...Args>
	void Geometry::addComponent(Args && ...args) noexcept
	{
		using ComponentType = typename std::decay_t<C>;
		auto component{ std::make_shared<ComponentType>(std::forward<Args>(args)...) };
		auto index{ std::type_index(typeid(ComponentType)) };
		if (const auto it{ components_.find(index) }; it != components_.end())
			it->second = component;
		else
			components_.emplace(index, component);
		for (const std::shared_ptr<properties::IProperty>& c : component->properties())
		{
			addProperty(c);
		}
		
	}
}


