#include "tree.h"

int64_t height(Tree::Node* node) {
   if (!node) return -1;

   int64_t lheight = height(node->left_child);
   int64_t rheight = height(node->rght_child);

   return 1 + maximum(lheight, rheight);
}

exit_t Tree::insert(Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return BAD_ALLOCATION;

   Node* increment_path = *node;
   int64_t parent_height = safe_access(increment_path, height, -1);

   while (*node) {

      if ((*node)->height + 1 < parent_height)
         increment_path = *node;

      parent_height = (*node)->height;
      
      if (false);

      else if (record->key < (*node)->content->key)
         node = &(*node)->left_child;

      else if (record->key > (*node)->content->key)
         node = &(*node)->rght_child;

      else /* record->key == (*node)->content->key */
         return KEY_ALREADY_EXISTS;
   }

   if (!parent_height) while (increment_path) {
      increment_path->height++;

      increment_path = record->key < increment_path->content->key ?
         increment_path->left_child : increment_path->rght_child;
   }

   *node = new_node;
   return SUCCESS;
}

void Tree::print(Node* node, int64_t level) {

   if (!node) {
      std::cout.write("{}\n", 3);
      return;
   }

   BitTools::mword* branches = nullptr;
   Node** stack = nullptr;

   if (level < 0)
      level = node->height;

   if (node->height) {

      int64_t stack_size = minimum(level + 1, node->height);

      branches = Stack::allocate<BitTools::mword>(BitTools::size(stack_size));
      if (!branches) {
         std::cout.write(FAIL_PRINT_TREE, sizeof(FAIL_PRINT_TREE) - 1);
         return;
      }

      stack = Stack::allocate<Node*>(stack_size);
      if (!stack) {
         Stack::release(branches);
         std::cout.write(FAIL_PRINT_TREE, sizeof(FAIL_PRINT_TREE) - 1);
         return;
      }

      BitTools::initialize(branches, stack_size);
   }

   int64_t depth = -1;
   int64_t top = -1;

   while (true) {

      if (node->left_child && level > depth) {
         stack[++top] = node;
         node = node->left_child;
         depth++;

         continue;
      }

      if (depth > -1)
         (void)BitTools::flipbit(branches, depth);

      while (true) {

         if (depth < 0)
            std::cout.write(BRANCH_ROOT, sizeof(BRANCH_ROOT) - 1);
         else
            std::cout.write(NO_BRANCH, sizeof(NO_BRANCH) - 1);

         for (int64_t i = 0; i < depth; i++) {
            if (BitTools::getbit(branches, i))
               std::cout.write(BRANCH_DOWN, sizeof(BRANCH_DOWN) - 1);
            else
               std::cout.write(NO_BRANCH, sizeof(NO_BRANCH) - 1);
         }

         if (depth > -1) {
            if (BitTools::getbit(branches, depth))
               std::cout.write(BRANCH_UP_SIDE, sizeof(BRANCH_UP_SIDE) - 1);
            else
               std::cout.write(BRANCH_DOWN_SIDE, sizeof(BRANCH_DOWN_SIDE) - 1);
         }

         if (level > depth) {

            print_record(node->content, "{$0, $1, $2, ");
            std::cout << node->height << ", " << depth << '\n';

            if (node->rght_child) {
               node = node->rght_child;

               depth++;
               (void)BitTools::setbit_1(branches, depth);

               break;
            }

         } else std::cout.write("{...}\n", 6);

         if (top < 0) goto exit;
         node = stack[top--];

         for (int64_t i = depth; i >= 0; i--) {
            depth--;
            if (BitTools::setbit_0(branches, i)) break;
         }

         if (depth > -1)
            (void)BitTools::flipbit(branches, depth);
      }
   }

exit:
   Stack::release(stack);
   Stack::release(branches);
}

Record* Tree::search(Tree::Node* node, key_t key) {

   while (node) {

      if (false);

      else if (key < node->content->key)
         node = node->left_child;

      else if (key > node->content->key)
         node = node->rght_child;

      else /* (key == node->content->key) */
         return node->content;
   }

   return nullptr;
}

void Tree::destruct(Node** node, void(*record_handler)(Record*)) {
   if (!*node) return;

   Node** stack = nullptr;
   if ((*node)->height) {
      stack = Stack::allocate<Node*>((*node)->height);
      if (!stack) return;
   }

   Node* current = *node;
   int64_t top = -1;

   while (true) {

      if (current->left_child) stack[++top] = current->left_child;
      if (current->rght_child) stack[++top] = current->rght_child;

      if (record_handler)
         record_handler(current->content);

      delete current;

      if (top < 0) break;
      current = stack[top--];
   }

   *node = nullptr;
   Stack::release(stack);
}

void destructqw1(Tree::Node** node, void(*handler)(Record*)) {
   if (!*node) return;

   byte index = 0;
   Tree::Node* stack[2] = { nullptr, nullptr };

   Tree::Node* root = *node;
   Tree::Node* current;
   *node = nullptr;

loop:
   current = root;

   while (current) {

      Tree::Node* tmp;

      if (current->left_child && current->rght_child) {

         if (index > 1) {
            root = current;

            while (current->height) {
               current = current->left_child ? current->left_child : current->rght_child;
            }

            current->left_child = stack[0];
            current->rght_child = stack[1];
            current->height = 1; // Anything different from zero would've been valid

            stack[0] = nullptr;
            stack[1] = nullptr;
            index = 0;

            goto loop; // Why isn't there a continue(1) for continuing onto the outter loop?
         }

         stack[index++] = current->rght_child;
         tmp = current->left_child;

      } else tmp = current->left_child ? current->left_child : current->rght_child;

      if (handler)
         handler(current->content);

      delete current;
      current = tmp;
   }

   if (!index) return;

   root = stack[--index];
   stack[index] = nullptr;
   goto loop;
}

void Tree::AVL::smpl_left_rotation(Node** node) {
   Node* rght_subtree = (*node)->rght_child;

   // Height adjustment
   (*node)->height = rght_subtree->rght_child->height;
   rght_subtree->height = 1 + (*node)->height;

   // Pointer jugling
   (*node)->rght_child = rght_subtree->left_child;
   rght_subtree->left_child = *node;
   *node = rght_subtree;
}

void Tree::AVL::smpl_rght_rotation(Node** node) {
   Node* left_subtree = (*node)->left_child;

   // Height adjustment
   (*node)->height = left_subtree->left_child->height;
   left_subtree->height = 1 + (*node)->height;

   // Pointer jugling
   (*node)->left_child = left_subtree->rght_child;
   left_subtree->rght_child = *node;
   *node = left_subtree;
}

void Tree::AVL::left_rght_rotation(Node** node) {
   Node* midd_subtree = (*node)->left_child->rght_child;

   // Pointer jugling on the left subtree
   (*node)->left_child->rght_child = midd_subtree->left_child;
   midd_subtree->left_child = (*node)->left_child;

   // Pointer jugling on the origin
   (*node)->left_child = midd_subtree->rght_child;
   midd_subtree->rght_child = *node;

   // Height adjustment
   midd_subtree->left_child->height = midd_subtree->height;
   midd_subtree->rght_child->height = midd_subtree->height;
   midd_subtree->height++;

   *node = midd_subtree;
}

void Tree::AVL::rght_left_rotation(Node** node) {
   Node* midd_subtree = (*node)->rght_child->left_child;

   // Pointer jugling on the right subtree
   (*node)->rght_child->left_child = midd_subtree->rght_child;
   midd_subtree->rght_child = (*node)->rght_child;

   // Pointer jugling on the origin
   (*node)->rght_child = midd_subtree->left_child;
   midd_subtree->left_child = *node;

   // Height adjustment
   midd_subtree->left_child->height = midd_subtree->height;
   midd_subtree->rght_child->height = midd_subtree->height;
   midd_subtree->height++;

   *node = midd_subtree;
}

bool is_balanced(Tree::Node* node) {
   if (!node) return true;

   if (!is_balanced(node->left_child)) return false;
   if (!is_balanced(node->rght_child)) return false;

   int64_t balancing_factor = height(node->rght_child) - height(node->left_child);
   if (balancing_factor < -1) return false;
   if (balancing_factor > 1) return false;

   return true;
}

exit_t Tree::AVL::insert(Tree::Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return BAD_ALLOCATION;

   Node** balance_node = node;
   Node** increment_path = node;

   // height may be highlighted as a function, although it's actually
   // refering to a Node's field height
   int64_t parent_height = safe_access(*node, height, -1);
   bool balance = false;
   bool side = false;

   while (*node) {

      if ((*node)->height + 1 < parent_height) {
         increment_path = node;
         balance = false;
      }

      // Parent height will indeed represent the height of the parent
      // until the end of the loop, not just a holder
      parent_height = (*node)->height;

      // If you're curious (or not), that's for alignment's sake, code-wise, will
      // simply be removed by the compiler as a trivial unreacheable conditinal
      if (false) {

      } else if (record->key < (*node)->content->key) {

         // If the insertion will happen to the left of the current node, is height will be
         // compared against its right child
         if (parent_height > 1 + safe_access((*node)->rght_child, height, -1)) {
            balance_node = node;
            balance = true;
            side = true;
         }

         node = &(*node)->left_child;

      } else if (record->key > (*node)->content->key) {

         // If the insertion will happen to the right of the current node, is height will be
         // compared against its left child
         if (parent_height > 1 + safe_access((*node)->left_child, height, -1)) {
            balance_node = node;
            balance = true;
            side = false;
         }

         node = &(*node)->rght_child;

      } else /* record->key == (*node)->content->key */ {
         return KEY_ALREADY_EXISTS;
      }
   }

   if (parent_height) {
      *node = new_node;
      return SUCCESS;
   }

   if (balance)
      increment_path = balance_node;

   while (*increment_path) {
      (*increment_path)->height++;

      increment_path = record->key < (*increment_path)->content->key ?
         &(*increment_path)->left_child : &(*increment_path)->rght_child;
   }

   *node = new_node;

   if (balance) {

      if (side) {

         if (record->key > (*balance_node)->left_child->content->key)
            left_rght_rotation(balance_node);
         else smpl_rght_rotation(balance_node);

      } else {

         if (record->key < (*balance_node)->rght_child->content->key)
            rght_left_rotation(balance_node);
         else smpl_left_rotation(balance_node);
      }
   }

   return SUCCESS;
}