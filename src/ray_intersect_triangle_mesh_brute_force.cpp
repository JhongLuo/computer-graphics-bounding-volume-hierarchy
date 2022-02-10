#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
	const Ray& ray,
	const Eigen::MatrixXd& V,
	const Eigen::MatrixXi& F,
	const double min_t,
	const double max_t,
	double& hit_t,
	int& hit_f)
{
	////////////////////////////////////////////////////////////////////////////
	bool hitted = false;
	double min_hit_t = std::numeric_limits<double>::infinity();
	for (int i = 0;i < F.rows();i++) {
		double tmp_hit_t;
		if (ray_intersect_triangle(ray, V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)), min_t, max_t, tmp_hit_t)) {
			if (tmp_hit_t < min_hit_t) {
				min_hit_t = tmp_hit_t;
				hit_f = i;
				hitted = true;
			}
		}
	}
	if (hitted) {
		hit_t = min_hit_t;
		return true;
	}
	else {
		return false;
	}
	////////////////////////////////////////////////////////////////////////////
}
