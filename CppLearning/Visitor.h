#ifndef VISITOR_H
#define VISITOR_H
#include <memory>

namespace geometry
{
	class Offset;
	
}

namespace visitor
{
	class IGeometryVisitor
	{
	public:
		virtual ~IGeometryVisitor() = default;
		virtual void visit(const geometry::Offset& offset) = 0;
	protected:
		std::shared_ptr<IOutputStrategy> outputStrategy_{};
	};

	class GeometryPrinter: public IGeometryVisitor
	{
	public:
		void visit(const geometry::Offset& offset) override;
	};
}

#endif // VISITOR_H
