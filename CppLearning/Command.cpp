#include "Command.h"

#include <memory>

namespace command
{
	template <typename T>
	PropertyCommand<T>::PropertyCommand(const Getter& getter, const Setter& setter, T&& newValue)
		: getter_{ getter }, setter_{ setter }, newValue_{ _STD forward<T>(newValue) }
	{
	}

	template <typename T>
	void PropertyCommand<T>::execute()
	{
		setter_(newValue_);
	}

	template <typename T>
	void PropertyCommand<T>::undo()
	{
		setter_(oldValue_);
	}
	// Общий метод для изменения свойства компонента через команду
	template<typename T, typename C>
	void executeCommand(C& component, void (C::* setter)(T), T(C::* getter)() const, T newValue) {
		auto command = _STD make_unique<PropertyCommand<T>>(
			_STD bind(setter, &component, _STD placeholders::_1),
			_STD bind(getter, &component),
			newValue
		);
		command->execute();
	}
}
