#include "tree.h"
#include <fstream>

bool Tree::insert(Tree::Node** node, Record* record) {

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

void Tree::print(Tree::Node* node, int64_t height) {

   // std::ostream& ostream = std::cout;
   std::fstream ostream("tree.txt", std::ios::binary | std::ios::out);

   if (!node) {
      ostream.write("{}\n", 2);
      return;
   }

   BitTools::mword* branches = nullptr;
   Node** stack = nullptr;

   if (height == -1)
      height = node->height;

   if (height > 0) {
      branches = Stack::allocate<BitTools::mword>(BitTools::size(height));
      if (!branches) {
         std::cerr << "Failed to print tree!\n";
         return;
      }

      stack = Stack::allocate<Node*>(height);
      if (!stack) {
         Stack::release(branches);
         std::cerr << "Failed to print tree!\n";
         return;
      }

      BitTools::initialize(branches, height);
   }

   int64_t depth = 0;
   int64_t top = -1;

   while (true) {

      if (!depth) ostream.write(BRANCH_ROOT, sizeof(BRANCH_ROOT) - 1);
      else ostream.write(NO_BRANCH, sizeof(NO_BRANCH) - 1);

      for (int64_t i = 0; i < depth - 1; i++) {
         if (BitTools::getbit(branches, i)) ostream.write(BRANCH_DOWN, sizeof(BRANCH_DOWN) - 1);
         else ostream.write(NO_BRANCH, sizeof(NO_BRANCH) - 1);
      }

      if (depth) {
         if (BitTools::getbit(branches, depth - 1)) ostream.write(BRANCH_DOWN_SIDE, sizeof(BRANCH_DOWN_SIDE) - 1);
         else ostream.write(BRANCH_SIDE, sizeof(BRANCH_SIDE) - 1);
      }

      // print_record(node->content, "{$0, $1, $2, ");

      ostream
         << '{' << node->content->key
         << ", " << node->height << "}\n";

      if (node->left_child && node->rght_child) {

         (void)BitTools::setbit_1(branches, depth);
         depth++;

      } else if (node->left_child || node->rght_child) {

         (void)BitTools::setbit_0(branches, depth);
         depth++;

      } else for (int64_t i = depth - 1; i >= 0; i--) {

         if (BitTools::setbit_0(branches, i)) break;
         depth--;

      }

      if (node->rght_child) stack[++top] = node->rght_child;
      if (node->left_child) stack[++top] = node->left_child;

      if (top < 0) break;
      node = stack[top--];
   }

   ostream.close();

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

void Tree::AVL::left_rotation(Node** node) {
   Node* rght_subtree = (*node)->rght_child;

   (*node)->height = 1 + (rght_subtree->rght_child ? rght_subtree->rght_child->height : 0);
   rght_subtree->height = 1 + (*node)->height;

   (*node)->rght_child = rght_subtree->left_child;
   rght_subtree->left_child = *node;
   *node = rght_subtree;
}

void Tree::AVL::rght_rotation(Node** node) {
   Node* left_subtree = (*node)->left_child;

   (*node)->height = 1 + (left_subtree->left_child ? left_subtree->left_child->height : 0);
   left_subtree->height = 1 + (*node)->height;

   (*node)->left_child = left_subtree->rght_child;
   left_subtree->rght_child = *node;
   *node = left_subtree;
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

#define height_s(node) ((node) ? (node)->height : -1)

bool Tree::AVL::insert(Tree::Node** node, Record* record) {

   Node** root = node;

   Node* new_node = new Node{ record, nullptr, nullptr, -1 };
   if (!new_node) return false;

   Node** balance_path = node;
   Node** increment_path = node;

   int64_t parent_height = height_s(*node);

   bool balance = false;
   bool side = false; // Compiler wouldn't shut up, didn't need to be initialized

   print(*root, height(*root));

   while (*node) {

      if ((*node)->height + 1 < parent_height)
         increment_path = node;

      parent_height = (*node)->height;
      if (record->key < (*node)->content->key) {

         if (height_s((*node)->left_child) > height_s((*node)->rght_child)) {
            balance = true;
            balance_path = node;
            side = true;
         }

         // parent = node;
         node = &(*node)->left_child;

      } else {

         if (height_s((*node)->rght_child) > height_s((*node)->left_child)) {
            balance = true;
            balance_path = node;
            side = false;
         }

         // parent = node;
         node = &(*node)->rght_child;
      }
   }

   *node = new_node;

   // if (!parent_height) while (increment_path) {
   //    increment_path->height++;

   //    increment_path = record->key < increment_path->content->key ?
   //       increment_path->left_child : increment_path->rght_child;
   // }

   print(*root, height(*root));

   bool is_not_balanced = !is_balanced(*root);

   if (is_not_balanced != balance) {
      std::cout << (is_not_balanced ? "\nNeeds, " : "\nGood, ");
      std::cout << record->key << ", ";

      std::cout << (!parent_height && height_s(*increment_path) > height_s(*balance_path)) << ", ";

      if (*increment_path) std::cout << (*increment_path)->content->key << ", ";
      else std::cout << "{}, ";

      std::cout << (balance ?
         (side ?
            (record->key > (*balance_path)->left_child->content->key ? "right-left" : "left") :
            (record->key < (*balance_path)->rght_child->content->key ? "left-right" : "right")
            ) : "none") << ", ";

      if (*balance_path) std::cout << (*balance_path)->content->key << "]\n";
      else std::cout << "{}]\n";

      // std::cout.write("*\n", 2);

      std::cin.get();
   }

   if (is_not_balanced) {

      if (side) {
         if (record->key > (*balance_path)->left_child->content->key)
            left_rotation(&(*balance_path)->left_child);
         rght_rotation(balance_path);
      } else {
         if (record->key < (*balance_path)->rght_child->content->key)
            rght_rotation(&(*balance_path)->rght_child);
         left_rotation(balance_path);
      }
   }

   print(*root, height(*root));

   if (!is_balanced(*root)) {
      std::cout.write("**\n", 2);
   }

   calculate_height(*root);
   return true;
}