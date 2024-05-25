#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <memory>
#include <set>
#include <unordered_map>
#include <typeindex>

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

        template<typename... Args>
        void update(Args&&... args);

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
        template<typename... Args>
        void update(Args&&... args);
    private:
        double x_{};
        double y_{};
    };

    class Geometry final: public Component
    {
    public:
        class Builder;
        Geometry();
        void accept(visitor::IGeometryVisitor& visitor) const override;
    private:
        template<typename C, typename... Args>
        void addComponent(Args&&... args) noexcept;

        template<typename C, typename... Args>
        void modifyComponent(Args&&... args) noexcept;

        template<typename C>
        std::shared_ptr<C> getComponent() const;
    private:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> components_{};
    };

    template <typename ... Args>
    void Offset::update(Args&&... args)
    {
        static_assert(sizeof...(Args) == 2, "Offset update requires two arguments (x, y)");
        std::tie(x_, y_) = std::forward_as_tuple(std::forward<Args>(args)...);
    }

    template <typename ... Args>
    void Skew::update(Args&&... args)
    {
        static_assert(sizeof...(Args) == 2, "Update update requires two arguments (x, y)");
        std::tie(x_, y_) = std::forward_as_tuple(std::forward<Args>(args)...);
    }

    template<typename C, typename ...Args>
    void Geometry::addComponent(Args && ...args) noexcept
    {
        using ComponentType = std::decay_t<C>;
        const auto component{ std::make_shared<ComponentType>(std::forward<Args>(args)...) };
        components_.emplace(std::type_index(typeid(ComponentType)), component);
        for (const std::shared_ptr<properties::IProperty>& c : component->properties()) {
            addProperty(c);
        }
    }
    class Geometry::Builder
    {
    public:
        Builder() = default;
        explicit Builder(Geometry geometry) noexcept;
        template<typename C, typename... Args>
        Builder& setComponent(Args&&... args) noexcept;
        Geometry build();
    private:
        Geometry geometry_{};
    };

	template<typename C, typename... Args>
	Geometry::Builder& Geometry::Builder::setComponent(Args&&... args) noexcept {
        // Check if the component already exists
        if (const auto it = geometry_.components_.find(std::type_index(typeid(C))); 
            it != geometry_.components_.end()) {
            // If it exists, modify the existing component
            geometry_.modifyComponent<C>(std::forward<Args>(args)...);
        }
        else {
            // If it doesn't exist, add a new component
            geometry_.addComponent<C>(std::forward<Args>(args)...);
        }
        return *this;
	}

    template <typename C, typename ... Args>
    void Geometry::modifyComponent(Args&&... args) noexcept
    {
        using ComponentType = std::decay_t<C>;
        if (const auto it = components_.find(std::type_index(typeid(ComponentType)));
            it != components_.end()) {
            static_cast<C*>(it->second.get())->update(std::forward<Args>(args)...);
        }
    }

    template <typename C>
    std::shared_ptr<C> Geometry::getComponent() const
    {
        const auto it{ components_.find(typeid(C)) };
        if (it != components_.end()) {
            return std::dynamic_pointer_cast<C>(it->second);
        }
        return nullptr;
    }
}
#endif // GEOMETRY_H
