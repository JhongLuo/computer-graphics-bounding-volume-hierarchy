#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
#include "triangle_triangle_intersection.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
	const std::shared_ptr<AABBTree>& rootA,
	const std::shared_ptr<AABBTree>& rootB,
	std::vector<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > >&
	leaf_pairs)
{
	////////////////////////////////////////////////////////////////////////////
	std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> q;
	q.emplace_back(rootA, rootB);
	while (!q.empty()) {
		std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> p = q.front();
		q.pop_front();
		std::shared_ptr<AABBTree>& tree_lef = std::dynamic_pointer_cast<AABBTree>(p.first);
		std::shared_ptr<AABBTree>& tree_rig = std::dynamic_pointer_cast<AABBTree>(p.second);
		if (tree_lef == NULL && tree_rig == NULL) {
			//if (triangle_triangle_intersection()) {
			//printf("leaves size %d\n", leaf_pairs.size());
			leaf_pairs.emplace_back(p.first, p.second);
			continue;
			/*}
			else {

			}*/
		}
		else if (tree_lef == NULL) {
			//printf("a");
			if (tree_rig->left && box_box_intersect(p.first->box, tree_rig->left->box)) {
				q.emplace_back(p.first, tree_rig->left);
			}
			if (tree_rig->right && box_box_intersect(p.first->box, tree_rig->right->box)) {
				q.emplace_back(p.first, tree_rig->right);
			}
			continue;
		}
		else if (tree_rig == NULL) {
			//printf("b");
			if (tree_lef->left && box_box_intersect(p.second->box, tree_lef->left->box)) {
				q.emplace_back(p.second, tree_lef->left);
			}
			if (tree_lef->right && box_box_intersect(p.second->box, tree_lef->right->box)) {
				q.emplace_back(p.second, tree_lef->right);
			}
			continue;
		}
		else {
			//printf("c");
			if (tree_lef->left && tree_rig->left && box_box_intersect(tree_lef->left->box, tree_rig->left->box)) {
				q.emplace_back(tree_lef->left, tree_rig->left);
			}
			if (tree_lef->left && tree_rig->right && box_box_intersect(tree_lef->left->box, tree_rig->right->box)) {
				q.emplace_back(tree_lef->left, tree_rig->right);
			}
			if (tree_lef->right && tree_rig->left && box_box_intersect(tree_lef->right->box, tree_rig->left->box)) {
				q.emplace_back(tree_lef->right, tree_rig->left);
			}
			if (tree_lef->right && tree_rig->right && box_box_intersect(tree_lef->right->box, tree_rig->right->box)) {
				q.emplace_back(tree_lef->right, tree_rig->right);
			}
			continue;
		}
	}
	printf("finish! %d\n", leaf_pairs.size());
	////////////////////////////////////////////////////////////////////////////
}
