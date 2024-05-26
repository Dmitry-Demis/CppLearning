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
        _NODISCARD virtual _STD string name() const = 0;
        _NODISCARD virtual _STD string toString() const = 0;
    };

    template<typename T>
    class Property : public IProperty
    {
    public:
        Property(_STD string name, T&& value);
        ~Property() noexcept override = default;
        _NODISCARD _STD string name() const override;
        _NODISCARD _STD string toString() const override;
    private:
        _STD string name_{};
        T value_{};
    };

    template <typename T>
    Property<T>::Property(_STD string name, T&& value)
        : name_{ _STD move(name) }, value_{ _STD forward<T>(value) }
    {
    }

    template <typename T>
    _STD string Property<T>::name() const
    {
        return name_;
    }

    template <typename T>
    _STD string Property<T>::toString() const
    {
        if constexpr (_STD is_same_v<T, _STD string>)
            return value_;
        else
            return _STD to_string(value_);
    }
    template<typename T>
    _STD shared_ptr<IProperty> makeProperty(const _STD string& name, T&& value)
    {
        using ValueType = _STD conditional_t<_STD is_const_v<_STD remove_reference_t<T>>, const T&, T&&>;
        return _STD make_shared<Property<ValueType>>(name, _STD forward<T>(value));
    }

    template<_STD size_t Index = 0, typename... Types>
    void addProperties(const _STD tuple<Types...>& properties, _STD set<_STD shared_ptr<IProperty>>& set)
    {
        if constexpr (Index < sizeof...(Types))
        {
            set.insert(_STD get<Index>(properties));
            addProperties<Index + 1>(properties, set);
        }
    }
}
#endif // PROPERTIES_H
