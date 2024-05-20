#ifndef VISITOR_H
#define VISITOR_H

#include <memory>
#include <string>
#include <sstream>

namespace geometry
{
	class Offset;
	class Skew;
	class Geometry;
}
namespace strategy
{
	class IOutputStrategy;
}

namespace visitor
{
	class IGeometryVisitor
	{
	public:
		explicit IGeometryVisitor(std::shared_ptr<strategy::IOutputStrategy> strategy);
		virtual ~IGeometryVisitor() = default;
		virtual void visit(const geometry::Offset& offset) = 0;
		virtual void visit(const geometry::Skew& skew) = 0;
		virtual void visit(const geometry::Geometry& geometry) = 0;
	protected:
		void print(const std::stringstream& stream) const;
	private:
		std::shared_ptr<strategy::IOutputStrategy> outputStrategy_{};
	};

	class GeometryPrinter: public IGeometryVisitor
	{
		using inherited = IGeometryVisitor;
	public:
		explicit GeometryPrinter(std::shared_ptr<strategy::IOutputStrategy> strategy);
		void visit(const geometry::Offset& offset) override;
		void visit(const geometry::Skew& skew) override;
		void visit(const geometry::Geometry& geometry) override;
	private:
		template<typename T>
		void print(const std::string& name, const T& component) const;
	};
	
}

#endif // VISITOR_H
