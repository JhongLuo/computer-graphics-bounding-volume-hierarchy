#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
	const Eigen::MatrixXd& points,
	const Eigen::RowVector3d& query,
	int& I,
	double& sqrD)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	sqrD = std::numeric_limits<double>::infinity();
	double tmp_x;
	double tmp_y;
	double tmp_z;
	double tmp_D;
	for (int i = 0; i < points.rows(); i++) {
		tmp_x = (points.row(i)[0] - query[0]);
		tmp_y = (points.row(i)[1] - query[1]);
		tmp_z = (points.row(i)[2] - query[2]);
		tmp_D = tmp_x * tmp_x + tmp_y * tmp_y + tmp_z * tmp_z;
		if (tmp_D < sqrD) {
			I = i;
			sqrD = tmp_D;
		}
	}
	////////////////////////////////////////////////////////////////////////////
}
