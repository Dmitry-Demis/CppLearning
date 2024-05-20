#ifndef GEOMETRY_H
#define GEOMETRY_H


namespace geometry
{


	class Geometry
	{
	};
}


class Component
{
public:
	virtual ~Component() = default;
	virtual void accept(const class IGeometryVisitor& visitor) const = 0;
};


#endif // GEOMETRY_H
