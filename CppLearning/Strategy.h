#include <string>
#include <iostream>
#ifndef STRATEGY_H
#define STRATEGY_H

namespace strategy
{
	class IOutputStrategy
	{
	public:
		virtual ~IOutputStrategy() = default;
		virtual void print(const _STD string& message) const = 0;
	};

	class ConsoleOutputStrategy : public IOutputStrategy
	{
	public:
		void print(const _STD string& message) const override;
	};

	class Printer
	{
	public:
		explicit Printer(_STD shared_ptr<IOutputStrategy> outputStrategy)
			: outputStrategy_{ _STD move(outputStrategy) }
		{}
		void setOutputStrategy(_STD shared_ptr<IOutputStrategy> outputStrategy) {
			outputStrategy_ = _STD move(outputStrategy);
		}
		void print(const _STD string& message) const {
			outputStrategy_->print(message);
		}
	private:
		_STD shared_ptr<IOutputStrategy> outputStrategy_{};
	};

}

#endif
