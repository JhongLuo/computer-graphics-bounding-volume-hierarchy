#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
	const std::vector<std::shared_ptr<Object> >& objects,
	int a_depth) :
	depth(std::move(a_depth)),
	num_leaves(objects.size())
{
	////////////////////////////////////////////////////////////////////////////
	unsigned int n = objects.size();
	//printf("leaves %d depth %d\n", this->num_leaves, this->depth);
	//printf("depth: %d n: %d\n", a_depth, n);
	if (n == 0) {
		this->left = NULL;
		this->right = NULL;
		return;
	}
	else if (n == 1) {
		this->left = objects[0];
		insert_box_into_box(objects[0]->box, this->box);
		this->right = NULL;//TODO
		return;
	}
	else if (n == 2) {
		this->left = objects[0];
		this->right = objects[1];
		insert_box_into_box(objects[0]->box, this->box);
		insert_box_into_box(objects[1]->box, this->box);
		return;
	}
	else {
		// midpoint along the longest axis of the box containing the given objects to determine the left-right split.
		for (int i = 0;i < n;i++) {
			insert_box_into_box(objects[i]->box, this->box);
		}
		short axis_choosed = 0;
		double max_distance = this->box.max_corner[0] - this->box.min_corner[0];
		for (short i = 1;i < 3;i++) {
			double distance = this->box.max_corner[i] - this->box.min_corner[i];
			if (distance > max_distance) {
				max_distance = distance;
				axis_choosed = i;
			}
		}
		double midaxis = (this->box.max_corner[axis_choosed] + this->box.min_corner[axis_choosed]) / 2.0;
		//printf("%lf  %lf  %lf\n", this->box.max_corner[axis_choosed], this->box.min_corner[axis_choosed], midaxis);


		std::vector<std::shared_ptr<Object>> left_list;
		std::vector<std::shared_ptr<Object>> right_list;
		for (int i = 0;i < n;i++) {

			if (objects[i]->box.center()[axis_choosed] < midaxis) {
				left_list.emplace_back(objects[i]);
			}
			else {
				right_list.emplace_back(objects[i]);
			}
		}

		if (left_list.empty()) {//have to re-locate the lef and right list
			left_list.push_back(right_list.back());
			right_list.pop_back();
		}

		if (right_list.empty()) {
			right_list.push_back(left_list.back());
			left_list.pop_back();
		}

		this->left = std::make_shared<AABBTree>(left_list, a_depth + 1);
		this->right = std::make_shared<AABBTree>(right_list, a_depth + 1);
		return;
	}
	////////////////////////////////////////////////////////////////////////////
}
