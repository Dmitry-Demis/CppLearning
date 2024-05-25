#include "Command.h"

#include <memory>

namespace command
{
	template <typename T>
	PropertyCommand<T>::PropertyCommand(const Getter& getter, const Setter& setter, T&& newValue)
		: getter_{ getter }, setter_{ setter }, newValue_{ std::forward<T>(newValue) }
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
	// ����� ����� ��� ��������� �������� ���������� ����� �������
	template<typename T, typename C>
	void executeCommand(C& component, void (C::* setter)(T), T(C::* getter)() const, T newValue) {
		auto command = std::make_unique<PropertyCommand<T>>(
			std::bind(setter, &component, std::placeholders::_1),
			std::bind(getter, &component),
			newValue
		);
		command->execute();
	}
}
