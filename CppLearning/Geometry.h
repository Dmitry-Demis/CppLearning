#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <memory>
#include <set>
#include <string>
#include "Properties.h"
#include <unordered_map>
#include <typeindex>

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
        _NODISCARD std::set<std::shared_ptr<properties::IProperty>> properties() const;
    protected:
        void addProperty(std::shared_ptr<properties::IProperty> property);
    private:
        std::set<std::shared_ptr<properties::IProperty>> properties_{};
    };
    

    class Offset final : public Component {
    public:
        explicit Offset(double x = 0.0, double y = 0.0) noexcept;
        _NODISCARD double x() const noexcept;
        _NODISCARD double y() const noexcept;
        void x(double x) noexcept;
        void y(double y) noexcept;
        void accept(visitor::IGeometryVisitor& visitor) const override;
    private:
        double x_{};
        double y_{};
    };

    class Skew final : public Component {
    public:
        explicit Skew(double x = 0.0, double y = 0.0) noexcept;
        _NODISCARD double x() const noexcept;
        _NODISCARD double y() const noexcept;
        void x(double x) noexcept;
        void y(double y) noexcept;
        void accept(visitor::IGeometryVisitor& visitor) const override;
    private:
        double x_{};
        double y_{};
    };

    class Geometry final: public Component
    {
    public:
        Geometry();
        void accept(visitor::IGeometryVisitor& visitor) const override;
        const std::unordered_map<std::type_index, std::shared_ptr<Component>>& components() const & {
            return components_;
        }
    private:
        template<typename C, typename... Args>
        void addComponent(Args&&... args) noexcept;
    private:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> components_{};
    };
}
#endif // GEOMETRY_H
