#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

class MyPair {
public:
	double sqrd;
	std::shared_ptr<AABBTree> tp;
	MyPair(double d, std::shared_ptr<AABBTree> p) :sqrd(d), tp(p) {}
	bool operator < (const MyPair& right) const
	{
		return this->sqrd > right.sqrd;
	}
};

//double point_box_max_squared_distance(
//	const Eigen::RowVector3d& query,
//	const BoundingBox& box)
//{
//	////////////////////////////////////////////////////////////////////////////
//	//return the max distance
//	return 0;
//	////////////////////////////////////////////////////////////////////////////
//}

bool point_AABBTree_squared_distance(
	const Eigen::RowVector3d& query,
	const std::shared_ptr<AABBTree>& root,
	const double min_sqrd,
	const double max_sqrd,
	double& sqrd,
	std::shared_ptr<Object>& descendant)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here
	//printf("query %lf %lf %lf\n", query[0], query[1], query[2]);
	std::priority_queue<MyPair> q;
	q.push(MyPair(point_box_squared_distance(query, root->box), root));
	sqrd = std::numeric_limits<double>::infinity();
	while (!q.empty()) {
		MyPair t = q.top();
		q.pop();
		if (t.sqrd < sqrd) {
			std::shared_ptr<Object>& left = t.tp->left;
			std::shared_ptr<Object>& right = t.tp->right;
			//printf("top dis: %lf leaves: %d depth: %d\n", t.sqrd, t.tp->num_leaves, t.tp->num_leaves);
			if (t.tp->num_leaves <= 2) {
				bool pick_lef = false;
				bool pick_rig = false;

				double lef_sqrd;
				double rig_sqrd;
				left->point_squared_distance(query, min_sqrd, max_sqrd, lef_sqrd, descendant);
				//printf("%lf, %lf, %lf, %lf, %lf %lf\n", left->box.min_corner[0], left->box.min_corner[1], left->box.min_corner[2], left->box.max_corner[0], left->box.max_corner[1], left->box.max_corner[2]);
				if (right != NULL) {
					right->point_squared_distance(query, min_sqrd, max_sqrd, rig_sqrd, descendant);
					//printf("lef, right: %lf %lf\n", lef_sqrd, rig_sqrd);
					if (lef_sqrd < rig_sqrd) {
						if (lef_sqrd >= min_sqrd && lef_sqrd <= max_sqrd) {
							pick_lef = true;
						}
					}
					if (!pick_lef && rig_sqrd >= min_sqrd && rig_sqrd <= max_sqrd) {
						pick_rig = true;
					}
				}
				else if (lef_sqrd >= min_sqrd && lef_sqrd <= max_sqrd) {
					pick_lef = true;
				}

				//printf("return %d %d\n", return_lef, return_rig);
				if (pick_lef && (lef_sqrd < sqrd)) {
					sqrd = lef_sqrd;
					descendant = left;
					if (sqrd == t.sqrd) {//sqrd is already the smallest
						return true;
					}
				}
				else if (pick_rig && (rig_sqrd < sqrd)) {
					sqrd = rig_sqrd;
					descendant = right;
					if (sqrd == t.sqrd) {//sqrd is already the smallest
						return true;
					}
				}
			}
			else {
				std::shared_ptr<AABBTree>& left_tree = std::dynamic_pointer_cast<AABBTree>(left);
				std::shared_ptr<AABBTree>& right_tree = std::dynamic_pointer_cast<AABBTree>(right);
				//printf("left leaves: %d depth: %d\n",left_tree->num_leaves, left_tree->depth);
				//printf("right leaves: %d depth: %d\n", right_tree->num_leaves, right_tree->depth);
				//printf("pushed lef, pushed right: %lf %lf\n", point_box_squared_distance(query, left_tree->box), point_box_squared_distance(query, right_tree->box));
				q.push(MyPair(point_box_squared_distance(query, left_tree->box), left_tree));
				q.push(MyPair(point_box_squared_distance(query, right_tree->box), right_tree));
			}
		}

	}
	return sqrd != std::numeric_limits<double>::infinity();
	////////////////////////////////////////////////////////////////////////////
}
