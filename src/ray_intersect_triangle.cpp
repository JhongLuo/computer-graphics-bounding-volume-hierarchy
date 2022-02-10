#include "ray_intersect_triangle.h"
#include <Eigen/Dense>
bool ray_intersect_triangle(
	const Ray& ray,
	const Eigen::RowVector3d& A,
	const Eigen::RowVector3d& B,
	const Eigen::RowVector3d& C,
	const double min_t,
	const double max_t,
	double& t)
{
	////////////////////////////////////////////////////////////////////////////
	const Eigen::RowVector3d& a = A.transpose();
	const Eigen::RowVector3d& b = B.transpose();
	const Eigen::RowVector3d& c = C.transpose();

	Eigen::MatrixXd matrix(3, 3);
	matrix(0, 0) = a[0] - b[0];
	matrix(0, 1) = a[0] - c[0];
	matrix(0, 2) = ray.direction[0];

	matrix(1, 0) = a[1] - b[1];
	matrix(1, 1) = a[1] - c[1];
	matrix(1, 2) = ray.direction[1];

	matrix(2, 0) = a[2] - b[2];
	matrix(2, 1) = a[2] - c[2];
	matrix(2, 2) = ray.direction[2];

	Eigen::MatrixXd jkl(3, 1);
	jkl(0, 0) = a[0] - ray.origin[0];
	jkl(1, 0) = a[1] - ray.origin[1];
	jkl(2, 0) = a[2] - ray.origin[2];

	Eigen::Vector3d ans = matrix.colPivHouseholderQr().solve(jkl);

	double tmp_t = ans[2];
	if (tmp_t < min_t || tmp_t > max_t) {
		return false;
	}

	double gamma = ans[1];
	if (gamma < 0 || gamma >1) {
		return false;
	}

	double beta = ans[0];
	if (beta < 0 || beta >(1 - gamma)) {
		return false;
	}

	t = tmp_t;

	return true;
	////////////////////////////////////////////////////////////////////////////
}

