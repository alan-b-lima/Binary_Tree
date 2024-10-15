#include "tree.h"

bool Tree::insert(Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   Node* increment_path = *node;
   int64_t parent_height = increment_path ? increment_path->height : -1;

   while (*node) {

      if ((*node)->height + 1 < parent_height)
         increment_path = *node;

      parent_height = (*node)->height;
      node = record->key < (*node)->content->key ?
         &(*node)->left_child : &(*node)->rght_child;

   }

   if (!parent_height) while (increment_path) {
      increment_path->height++;

      increment_path = record->key < increment_path->content->key ?
         increment_path->left_child : increment_path->rght_child;
   }

   *node = new_node;
   return true;
}

void Tree::print(Node* node) {

   if (!node) {
      std::cout.write("{}\n", 2);
      return;
   }

   BitTools::mword* branches = nullptr;
   Node** stack = nullptr;

   if (node->height) {
      branches = Stack::allocate<BitTools::mword>(BitTools::size(node->height));
      if (!branches) {
         std::cerr << "Failed to print tree!\n";
         return;
      }

      stack = Stack::allocate<Node*>(node->height);
      if (!stack) {
         Stack::release(branches);
         std::cerr << "Failed to print tree!\n";
         return;
      }

      BitTools::initialize(branches, node->height);
   }

   int64_t depth = -1;
   int64_t top = -1;

   while (true) {

      if (node->left_child) {
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

         print_record(node->content, "{$0, $1, $2, ");
         std::cout << node->height << '\n';

         if (node->rght_child) {
            node = node->rght_child;

            depth++;
            (void)BitTools::setbit_1(branches, depth);

            break;
         }

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

int64_t height(Tree::Node* node) {
   if (!node) return -1;

   int64_t lheight = height(node->left_child);
   int64_t rheight = height(node->rght_child);

   return 1 + (lheight > rheight ? lheight : rheight);
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

bool Tree::AVL::insert(Tree::Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   Node** balance_path = node;
   Node** increment_path = node;

   int64_t parent_height = *node ? (*node)->height : -1;

   bool balance = false;
   bool side = false;

   while (*node) {

      if ((*node)->height + 1 < parent_height) {
         increment_path = node;
         balance = false;
      }

      parent_height = (*node)->height;
      if (record->key < (*node)->content->key) {

         if (parent_height > 1 + ((*node)->rght_child ? (*node)->rght_child->height : -1)) {
            balance = true;
            balance_path = node;
            side = true;
         }

         node = &(*node)->left_child;

      } else {

         if (parent_height > 1 + ((*node)->left_child ? (*node)->left_child->height : -1)) {
            balance = true;
            balance_path = node;
            side = false;
         }

         node = &(*node)->rght_child;
      }
   }

   if (parent_height) {
      *node = new_node;
      return true;
   }

   if (balance)
      increment_path = balance_path;

   while (*increment_path) {
      (*increment_path)->height++;

      increment_path = record->key < (*increment_path)->content->key ?
         &(*increment_path)->left_child : &(*increment_path)->rght_child;
   }

   *node = new_node;

   if (balance) {

      if (side) {

         if (record->key > (*balance_path)->left_child->content->key)
            left_rght_rotation(balance_path);
         else smpl_rght_rotation(balance_path);

      } else {
         
         if (record->key < (*balance_path)->rght_child->content->key)
            rght_left_rotation(balance_path);
         else smpl_left_rotation(balance_path);
      }
   }

   return true;
}