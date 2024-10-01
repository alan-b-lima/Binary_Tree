#include "tree.h"

bool Tree::insert(Tree::Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   Node* increment_path = *node;
   uint64 height = increment_path ? increment_path->height : 1;

   while (true) {

      if (!*node) {

         if (!height) while (increment_path) {
            increment_path->height++;

            increment_path = record->key < increment_path->content->key ?
               increment_path->left_child : increment_path->rght_child;
         }

         *node = new_node;
         return true;
      }

      if ((*node)->height + 1 != height)
         increment_path = *node;

      height = (*node)->height;
      node = record->key < (*node)->content->key ?
         &(*node)->left_child : &(*node)->rght_child;

   }
}

void Tree::AVL::left_rotation(Tree::Node** node) {
   Node* rght_subtree = (*node)->rght_child;
   Node* midd_subtree = rght_subtree->left_child;

   (*node)->rght_child = midd_subtree;
   rght_subtree->left_child = *node;

   /* height adjustment */
   {
      (*node)->height = midd_subtree ? 1 + midd_subtree->height : 1;

      rght_subtree->height = 1 + (*node)->height;
      if (rght_subtree->rght_child && rght_subtree->height <= rght_subtree->rght_child->height)
         rght_subtree->height = 1 + (*node)->rght_child->height;
   }

   *node = rght_subtree;
}

void Tree::AVL::rght_rotation(Tree::Node** node) {
   Node* left_subtree = (*node)->left_child;
   Node* midd_subtree = left_subtree->rght_child;

   (*node)->left_child = midd_subtree;
   left_subtree->rght_child = *node;

   /* height adjustment */
   {
      (*node)->height = midd_subtree ? 1 + midd_subtree->height : 1;

      left_subtree->height = 1 + (*node)->height;
      if (left_subtree->left_child && left_subtree->height <= left_subtree->left_child->height)
         left_subtree->height = 1 + (*node)->left_child->height;
   }

   *node = left_subtree;
}

/* Simple Left Rotation
 *    Occurs if fb(A) ≥ 2 and fb(B) ≥ 0
 *
 *          A              B
 *         / \            / \
 *       [1]  B    =>    A  [3]
 *           / \        / \
 *         [2] [3]    [1] [2]
 *
 *    Height adjustment
 *       2 ≤ fb(A)
 *       2 ≤ h[1] - h(B)
 *       h(B) + 2 ≤ h[1]
 *       max{h[2], h[3]} + 3 ≤ h[1]
 *       h[3] + 3 ≤ h[1]           , since fb(B) ≥ 0 <=> h[3] - h[2] ≥ 0
 *       h[3] + 2 < h[1]                             <=> h[3] ≥ h[2]
 *
 *    After rotation, the new heights will be
 *       h(A_new) = 1 + max{h[1], h[2]}
 *                = 1 + h[1]               , since h[2] ≤ h[3] and h[3] + 2 < h[1]
 *                                                    => h[2] + 2 ≤ h[3] + 2 and h[3] + 2 < h[1] < h[1] + 2
 *                                                    => h[2] + 2 < h[1] + 2
 *                                                    => h[2] < h[1]
 *
 *       h(B_new) = 1 + max{h(A_new), h[3]}
 *                = 1 + max{1 + h[1], h[3]}
 *                = 1 + 1 + h[1]           , since h[3] + 2 < h[1] < h[1] + 3
 *                = 2 + h[1]                          => h[3] + 2 < h[1] + 3
 *                                                    => h[3] < h[1] + 1
 * 
 * Obs: when invoked by here implemented functions, [1] will always be defined
*/
void Tree::AVL::smpl_left_rotation(Node** node) {
   Node* rght_subtree = (*node)->rght_child;
   Node* midd_subtree = rght_subtree->left_child;

   (*node)->rght_child = midd_subtree;
   rght_subtree->left_child = *node;

   (*node)->height = 1 + (*node)->left_child->height;
   rght_subtree->height = 1 + (*node)->height;

   *node = rght_subtree;
}

/* Simple Right Rotation
 *    Occurs if fb(A) ≤ -2 and fb(B) ≤ 0
 *
 *            A          B
 *           / \        / \
 *          B  [3] => [1]  A
 *         / \            / \
 *       [1] [2]        [2] [3]
 *
 *    Height adjustment happens similarly to previous
 *       h(A_new) = 1 + h[3]
 *       h(B_new) = 2 + h[3]
 * 
 * Obs: when invoked by here implemented functions, [3] will always be defined
*/
void Tree::AVL::smpl_rght_rotation(Node** node) {
   Node* left_subtree = (*node)->left_child;
   Node* midd_subtree = left_subtree->rght_child;

   (*node)->left_child = midd_subtree;
   left_subtree->rght_child = *node;

   (*node)->height = 1 + (*node)->rght_child->height;
   left_subtree->height = 1 + (*node)->height;

   *node = left_subtree;
}

void Tree::AVL::rght_left_rotation(Node** node) {}
void Tree::AVL::left_rght_rotation(Node** node) {}

bool Tree::AVL::insert(Tree::Node** node, Record* record) {

   Node* root = *node;

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   Node* increment_path = *node;
   uint64 height = increment_path ? increment_path->height : 0;
   Node** balance_node = nullptr;
   bool side = 0;

   while (*node) {

      if ((*node)->height + 1 < height)
         increment_path = *node;
      else {

      }

      height = (*node)->height;
      side = record->key < (*node)->content->key;
      node = side ? &(*node)->left_child : &(*node)->rght_child;

   }

   if (!height) while (increment_path) {
      increment_path->height++;

      int64 balancing_factor = 0;
      if (increment_path->rght_child)
         balancing_factor += increment_path->rght_child->height;
      if (increment_path->left_child)
         balancing_factor -= increment_path->left_child->height;

      if (record->key < increment_path->content->key) {

         if (balancing_factor < 1) /* balancing_factor - 2 < -1 */ {
            balance_node = &increment_path;
            side = false;
         }

         increment_path = increment_path->left_child;
      }
      else {
         if (balancing_factor > -1) /* balancing_factor + 2 < 1 */ {
            balance_node = &increment_path;
            side = true;
         }

         increment_path = increment_path->rght_child;
      }
   }

   *node = new_node;
   return true;

   if (*balance_node) {
      if (side) {
         if (record->key < (*balance_node)->content->key)
            rght_rotation(&(*balance_node)->left_child);
         left_rotation(balance_node);
      }
      else {
         if (record->key > (*balance_node)->content->key)
            left_rotation(&(*balance_node)->rght_child);
         rght_rotation(balance_node);
      }
   }
}