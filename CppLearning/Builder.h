#ifndef BUILDER_H
#define BUILDER_H
#include <functional>

namespace builder
{
	template<typename T>
	class Builder
	{
	public:
		Builder() = default;
		explicit Builder(T& object) noexcept;
		template<typename C, typename... Args>
		Builder& setComponent(Args&&... args) noexcept;
		T build();
	private:
		std::reference_wrapper<T> object_{};
	};

	template <typename T>
	Builder<T>::Builder(T& object) noexcept
		: object_{ object_ }
	{
	}

	template <typename T>
	template <typename C, typename ... Args>
	Builder<T>& Builder<T>::setComponent(Args&&... args) noexcept
	{
		return *this;
	}
}


#endif // BUILDER_H
