#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <memory>
#include <set>
#include <string>
#include "Properties.h"

namespace visitor
{
    class IGeometryVisitor;
}
namespace geometry
{
        
    class Component
    {
    public:
        virtual ~Component() = default;
        virtual void accept(visitor::IGeometryVisitor& visitor) const = 0;
        virtual _NODISCARD std::set<std::shared_ptr<properties::IProperty>> properties() const = 0;
    protected:
        void addProperty(std::shared_ptr<properties::IProperty> property);

        template<typename T>
        void updateProperty(const std::string& name, T&& value);
    protected:
        std::set<std::shared_ptr<properties::IProperty>> properties_{};
    private:
    };

    template <typename T>
    void Component::updateProperty(const std::string& name, T&& value)
    {
        auto it{ std::find_if(properties_.begin(), properties_.end(), 
            [&name](const std::shared_ptr<properties::IProperty>& property)
            {
                return property->name() == name;
            }) };
        if (it != properties_.end())
            (*it)->updateValue(std::forward<T>(value));

    }

    class Offset final : public Component {
    public:
        explicit Offset(double x = 0.0, double y = 0.0) noexcept;
        _NODISCARD double x() const noexcept;
        _NODISCARD double y() const noexcept;
        void x(double x) noexcept;
        void y(double y) noexcept;
        void accept(visitor::IGeometryVisitor& visitor) const override;
        std::set<std::shared_ptr<properties::IProperty>> properties() const override;
    private:
    private:
        double x_{};
        double y_{};
    };
    class Geometry
    {
    };
}




#endif // GEOMETRY_H
