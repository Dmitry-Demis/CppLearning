#ifndef PROPERTIES_H
#define PROPERTIES_H
#include <memory>
#include <ratio>
#include <set>
#include <string>
#include <utility>

namespace properties
{
    class IProperty
    {
    public:
        virtual ~IProperty() noexcept = default;
        _NODISCARD virtual std::string name() const = 0;
        _NODISCARD virtual std::string toString() const = 0;
        _NODISCARD virtual bool operator<(const IProperty& other) const = 0;
    };

    template<typename T>
    class Property : public IProperty
    {
    public:
        Property(std::string name, T&& value);
        ~Property() noexcept override = default;
        _NODISCARD std::string name() const override;
        _NODISCARD std::string toString() const override;
    private:
        std::string name_{};
        T value_{};
    };

    template <typename T>
    Property<T>::Property(std::string name, T&& value)
        : name_{ std::move(name) }, value_{ std::forward<T>(value) }
    {
    }

    template <typename T>
    std::string Property<T>::name() const
    {
        return name_;
    }

    template <typename T>
    std::string Property<T>::toString() const
    {
        if constexpr (std::is_same_v<T, std::string>)
            return value_;
        else
            return std::to_string(value_);
    }        
#if 1
    template<typename T>
    std::shared_ptr<IProperty> makeProperty(const std::string& name, T&& value)
    {
        using ValueType = std::conditional_t<std::is_const_v<std::remove_reference_t<T>>, const T&, T&&>;
        return std::make_shared<Property<ValueType>>(name, std::forward<T>(value));
    }

    template<std::size_t Index = 0, typename... Types>
    void addProperties(const std::tuple<Types...>& properties, std::set<std::shared_ptr<IProperty>>& set)
    {
        if constexpr (Index < sizeof...(Types))
        {
            set.insert(std::get<Index>(properties));
            addProperties<Index + 1>(properties, set);
        }
    }
#endif
}
#endif // PROPERTIES_H
