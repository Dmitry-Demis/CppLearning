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
		virtual void print(const std::string& message) const = 0;
	};

	class ConsoleOutputStrategy : public IOutputStrategy
	{
	public:
		void print(const std::string& message) const override;
	};

	class Printer
	{
	public:
		explicit Printer(std::shared_ptr<IOutputStrategy> outputStrategy)
			: outputStrategy_{ std::move(outputStrategy) }
		{}
		void setOutputStrategy(std::shared_ptr<IOutputStrategy> outputStrategy) {
			outputStrategy_ = std::move(outputStrategy);
		}
		void print(const std::string& message) const {
			outputStrategy_->print(message);
		}
	private:
		std::shared_ptr<IOutputStrategy> outputStrategy_{};
	};

}

#endif
