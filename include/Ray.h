#ifndef RAY_H
#define RAY_H

#include <Eigen/Core>
#include <utility>

struct Ray
{
	Ray(Eigen::Vector3d a_origin, Eigen::Vector3d a_direction) :
		origin(std::move(a_origin)), direction(std::move(a_direction))
	{ }
	Eigen::Vector3d origin;
	// Not necessarily unit-length direction vector. (It is often useful to have
	// non-unit length so that origin+t*direction lands on a special point when
	// t=1.)
	Eigen::Vector3d direction;
};

#endif
