#ifndef COMMAND_H
#define COMMAND_H
#include <functional>

namespace command
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void execute() = 0;
		virtual void undo() = 0;
	};
	template<typename T>
	class PropertyCommand : public Command
	{
	public:
		using Getter = std::function<T() const>;
		using Setter = std::function<void(T)>;

		PropertyCommand(const Getter& getter, const Setter& setter, T&& newValue);
		void execute() override;
		void undo() override;
	private:
		Getter getter_{};
		Setter setter_{};
		T newValue_{};
		T oldValue_{};
	};


}


#endif // COMMAND_H
