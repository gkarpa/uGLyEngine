#include "AABB.h"

namespace uGLy
{

	AABB::AABB()
	{

	}

	void AABB::construct(std::vector<Vertex> & vertices)
	{
		auto minmax_x = std::minmax_element(vertices.begin(), vertices.end(),
			[](Vertex const & left, Vertex const & right) {return left.position.x < right.position.x; });
		auto minmax_y = std::minmax_element(vertices.begin(), vertices.end(),
			[](Vertex const & left, Vertex const & right) {return left.position.y < right.position.y; });
		auto minmax_z = std::minmax_element(vertices.begin(), vertices.end(),
			[](Vertex const & left, Vertex const & right) {return left.position.z < right.position.z; });

		xmin = minmax_x.first->position.x;
		xmax = minmax_x.second->position.x;

		ymin = minmax_y.first->position.y;
		ymax = minmax_y.second->position.y;

		zmin = minmax_z.first->position.z;
		zmax = minmax_z.second->position.z;
	}

}
