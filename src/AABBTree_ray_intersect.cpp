#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
	const Ray& ray,
	const double min_t,
	const double max_t,
	double& t,
	std::shared_ptr<Object>& descendant) const
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	if (!ray_intersect_box(ray, this->box, min_t, max_t)) {
		return false;
	}

	double t_left;
	bool hit_left = false;
	std::shared_ptr<Object> descendant_left = this->left;
	if (this->left != NULL) {
		hit_left = this->left->ray_intersect(ray, min_t, max_t, t_left, descendant_left);
	}

	double t_right;
	bool hit_right = false;
	std::shared_ptr<Object> descendant_right = this->right;
	if (this->right != NULL) {
		hit_right = this->right->ray_intersect(ray, min_t, max_t, t_right, descendant_right);
	}

	if (!hit_left) {
		if (!hit_right) {
			return false;
		}
		else {
			t = t_right;
			descendant = descendant_right;
			return true;
		}
	}
	else {
		if (!hit_right) {
			t = t_left;
			descendant = descendant_left;
			return true;
		}
		else {
			if (t_left < t_right) {
				t = t_left;
				descendant = descendant_left;
				return true;
			}
			else {
				t = t_right;
				descendant = descendant_right;
				return true;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////
}

