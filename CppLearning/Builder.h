#ifndef BUILDER_H
#define BUILDER_H
#include <functional>
#include <memory>

namespace builder
{
	template<typename T>
	class Builder
	{
	public:
		Builder() = default;
		explicit Builder(_STD shared_ptr<T> object) noexcept;
		template<typename C, typename... Args>
		Builder& setComponent(Args&&... args) noexcept;
		_STD shared_ptr<T> build();
		Builder& operator=(_STD shared_ptr<T> object);
	private:
		_STD shared_ptr<T> object_{_STD make_shared<T>()};
	};

	template <typename T>
	Builder<T>::Builder(_STD shared_ptr<T> object) noexcept
		: object_{ _STD move(object) }
	{
	}

	template <typename T>
	template <typename C, typename ... Args>
	Builder<T>& Builder<T>::setComponent(Args&&... args) noexcept
	{
		object_->template setComponent<C>(_STD forward<Args>(args)...);
		return *this;
	}

	template <typename T>
	_STD shared_ptr<T> Builder<T>::build()
	{
		return _STD move(object_);
	}

	template <typename T>
	Builder<T>& Builder<T>::operator=(_STD shared_ptr<T> object)
	{
		object_ = _STD move(object);
		return *this;
	}
}


#endif // BUILDER_H
