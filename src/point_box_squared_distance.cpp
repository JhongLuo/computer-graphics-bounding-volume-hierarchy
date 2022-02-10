#include "point_box_squared_distance.h"

double point_box_squared_distance(
	const Eigen::RowVector3d& query,
	const BoundingBox& box)
{
	////////////////////////////////////////////////////////////////////////////
	//return the min distance

	double tmp = box.min_corner[0] - query[0];
	double x_distance;
	x_distance = tmp > 0 ? tmp : (query[0] - box.max_corner[0]);
	x_distance = (x_distance > 0) ? x_distance : 0;

	tmp = box.min_corner[1] - query[1];
	double y_distance;
	y_distance = tmp > 0 ? tmp : (query[1] - box.max_corner[1]);
	y_distance = (y_distance > 0) ? y_distance : 0;

	tmp = box.min_corner[2] - query[2];
	double z_distance;
	z_distance = tmp > 0 ? tmp : (query[2] - box.max_corner[2]);
	z_distance = (z_distance > 0) ? z_distance : 0;

	return (x_distance * x_distance) + (y_distance * y_distance) + (z_distance * z_distance);
	////////////////////////////////////////////////////////////////////////////
}
