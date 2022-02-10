#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
	const Ray& ray,
	const BoundingBox& box,
	const double min_t,
	const double max_t)
{
	////////////////////////////////////////////////////////////////////////////
	double max_min_t;
	double min_max_t;


	double x_e = ray.origin[0];
	double x_d = ray.direction[0];
	double x_min = box.min_corner[0];
	double x_max = box.max_corner[0];
	if (x_d >= 0) {
		max_min_t = (x_min - x_e) / x_d;
		min_max_t = (x_max - x_e) / x_d;
	}
	else {
		max_min_t = (x_max - x_e) / x_d;
		min_max_t = (x_min - x_e) / x_d;
	}


	double y_e = ray.origin[1];
	double y_d = ray.direction[1];
	double y_min = box.min_corner[1];
	double y_max = box.max_corner[1];
	double y_min_t;
	double y_max_t;
	if (y_d >= 0) {
		y_min_t = (y_min - y_e) / y_d;
		y_max_t = (y_max - y_e) / y_d;
		if (y_min_t > max_min_t) {
			max_min_t = y_min_t;
		}
		if (y_max_t < min_max_t) {
			min_max_t = y_max_t;
		}
	}
	else {
		y_min_t = (y_max - y_e) / y_d;
		y_max_t = (y_min - y_e) / y_d;
		if (y_min_t > max_min_t) {
			max_min_t = y_min_t;
		}
		if (y_max_t < min_max_t) {
			min_max_t = y_max_t;
		}
	}

	if (min_max_t < max_min_t) {
		return false;
	}

	double z_e = ray.origin[2];
	double z_d = ray.direction[2];
	double z_min = box.min_corner[2];
	double z_max = box.max_corner[2];
	double z_min_t;
	double z_max_t;
	if (z_d >= 0) {
		z_min_t = (z_min - z_e) / z_d;
		z_max_t = (z_max - z_e) / z_d;
		if (z_min_t > max_min_t) {
			max_min_t = z_min_t;
		}
		if (z_max_t < min_max_t) {
			min_max_t = z_max_t;
		}
	}
	else {
		z_min_t = (z_max - z_e) / z_d;
		z_max_t = (z_min - z_e) / z_d;
		if (z_min_t > max_min_t) {
			max_min_t = z_min_t;
		}
		if (z_max_t < min_max_t) {
			min_max_t = z_max_t;
		}
	}

	if (min_max_t < max_min_t) {
		return false;
	}
	else {
		return true;
	}



	////////////////////////////////////////////////////////////////////////////
}
