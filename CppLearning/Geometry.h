#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <memory>
#include <set>
#include <unordered_map>
#include <typeindex>

#include "Builder.h"

namespace visitor
{
    class IGeometryVisitor;
}
namespace properties
{
    class IProperty;
}

namespace geometry
{
        
    class Component
    {
    public:
        virtual ~Component() = default;
        virtual void accept(visitor::IGeometryVisitor& visitor) const = 0;
        _NODISCARD _STD set<_STD shared_ptr<properties::IProperty>> properties() const;
    protected:
        void addProperty(_STD shared_ptr<properties::IProperty> property);
    private:
        _STD set<_STD shared_ptr<properties::IProperty>> properties_{};
    };


    class Offset final : public Component {
    public:
        explicit Offset(double x = 0.0, double y = 0.0) noexcept;
        _NODISCARD double x() const noexcept;
        _NODISCARD double y() const noexcept;
        void x(double x) noexcept;
        void y(double y) noexcept;
        void accept(visitor::IGeometryVisitor& visitor) const override;

        template<typename... Args>
        void update(Args&&... args);

    private:
        double x_{};
        double y_{};
    };
    template <typename ... Args>
    void Offset::update(Args&&... args)
    {
        static_assert(sizeof...(Args) == 2, "Offset update requires two arguments (x, y)");
        _STD tie(x_, y_) = _STD forward_as_tuple(_STD forward<Args>(args)...);
    }



    class Skew final : public Component {
    public:
        explicit Skew(double x = 0.0, double y = 0.0) noexcept;
        _NODISCARD double x() const noexcept;
        _NODISCARD double y() const noexcept;
        void x(double x) noexcept;
        void y(double y) noexcept;
        void accept(visitor::IGeometryVisitor& visitor) const override;
        template<typename... Args>
        void update(Args&&... args);
    private:
        double x_{};
        double y_{};
    };
    template <typename ... Args>
    void Skew::update(Args&&... args)
    {
        static_assert(sizeof...(Args) == 2, "Update update requires two arguments (x, y)");
        _STD tie(x_, y_) = _STD forward_as_tuple(_STD forward<Args>(args)...);
    }


    class Geometry final : public Component
    {
    public:
        Geometry();
        void accept(visitor::IGeometryVisitor& visitor) const override;
        template<typename C, typename... Args>
        void setComponent(Args&&... args) noexcept;
    private:
        template<typename C, typename... Args>
        void addComponent(Args&&... args) noexcept;

        template<typename C, typename... Args>
        void modifyComponent(Args&&... args) noexcept;

        template<typename C>
        _STD shared_ptr<C> getComponent() const;
    private:
        _STD unordered_map<_STD type_index, _STD shared_ptr<Component>> components_{};
    };


    template <typename C, typename ... Args>
    void Geometry::setComponent(Args&&... args) noexcept
    {
        if (const auto it = components_.find(_STD type_index(typeid(C)));
            it != components_.end()) {
            modifyComponent<C>(_STD forward<Args>(args)...);
        }
    }

    template<typename C, typename ...Args>
    void Geometry::addComponent(Args && ...args) noexcept
    {
        using ComponentType = _STD decay_t<C>;
        const auto component{ _STD make_shared<ComponentType>(_STD forward<Args>(args)...) };
        components_.emplace(_STD type_index(typeid(ComponentType)), component);
        for (const _STD shared_ptr<properties::IProperty>& c : component->properties()) {
            addProperty(c);
        }
    }

    template <typename C, typename ... Args>
    void Geometry::modifyComponent(Args&&... args) noexcept
    {
        using ComponentType = _STD decay_t<C>;
        if (const auto it = components_.find(_STD type_index(typeid(ComponentType)));
            it != components_.end()) {
            static_cast<C*>(it->second.get())->update(_STD forward<Args>(args)...);
        }
    }

    template <typename C>
    _STD shared_ptr<C> Geometry::getComponent() const
    {
        if (const auto it{ components_.find(typeid(C)) };
            it != components_.end()) {
            return _STD dynamic_pointer_cast<C>(it->second);
        }
        return nullptr;
    }
}
#endif // GEOMETRY_H
