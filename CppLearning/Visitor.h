#ifndef VISITOR_H
#define VISITOR_H

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
	};

	class GeometryPrinter: public IGeometryVisitor
	{
	public:
		void visit(const geometry::Offset& offset) override;
	};
}

#endif // VISITOR_H
