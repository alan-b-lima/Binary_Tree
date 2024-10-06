#include "tree.h"

bool Tree::insert(Tree::Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   Node* increment_path = *node;
   int64_t height = increment_path ? increment_path->height : -1;

   while (*node) {

      if ((*node)->height + 1 < height)
         increment_path = *node;

      height = (*node)->height;
      node = record->key < (*node)->content->key ?
         &(*node)->left_child : &(*node)->rght_child;

   }

   if (!height) while (increment_path) {
      increment_path->height++;

      increment_path = record->key < increment_path->content->key ?
         increment_path->left_child : increment_path->rght_child;
   }

   *node = new_node;
   return true;
}

void Tree::print_tree(Tree::Node* node) {

   if (!node) {
      std::cout.write("{}", 2);
      return;
   }

   Node** stack = (Node**)_malloca(node->height * sizeof(Node*));
   int64_t top = 0;

   stack[0] = node;

   bool* branches = new bool[node->height];
   for (int64_t i = 0; i < node->height; i++)
      branches[i] = false;

   int64_t depth = 0;

   while (stack[0]) {

      node = stack[top];
      stack[top--] = nullptr;

      if (!depth) std::cout.write(":\xC4\xC4\xC4", 4);
      else std::cout.write("    ", 4);

      for (int64_t i = 0; i < depth - 1; i++) {
         std::cout.put(branches[i] ? '\xB3' : '\x20');
         std::cout.write("   ", 3);
      }

      if (depth - 1 >= 0) {
         std::cout.put(branches[depth - 1] ? '\xC3' : '\xC0');
         std::cout.write("\xC4\xC4\xC4", 3);
      }

      print_record(node->content, "{$0, $1, $2, ");
      std::cout << node->height << "\n";

      if (node->left_child || node->rght_child) {
         branches[depth] = node->left_child && node->rght_child;
         depth++;
      } else for (int64_t i = depth - 1; i >= 0; i--) {
         if (branches[i]) { branches[i] = false; break; }
         depth--;
      }

      if (node->rght_child) stack[++top] = node->rght_child;
      if (node->left_child) stack[++top] = node->left_child;
   }

   delete branches;
   _freea(stack);
}

Record* Tree::search(Tree::Node* node, key_t key) {

   while (node) {

      if (key < node->content->key)
         node = node->left_child;

      if (key > node->content->key)
         node = node->rght_child;

      else /* key == node->content->key */
         return node->content;
   }

   return nullptr;
}

void Tree::AVL::left_rotation(Node** node) {
   Node* rght_subtree = (*node)->rght_child;

   (*node)->height = rght_subtree->rght_child->height;
   rght_subtree->height = 1 + (*node)->height;

   (*node)->rght_child = rght_subtree->left_child;
   rght_subtree->left_child = *node;
   *node = rght_subtree;
}

void Tree::AVL::rght_rotation(Node** node) {
   Node* left_subtree = (*node)->left_child;

   (*node)->height = left_subtree->left_child->height;
   left_subtree->height = 1 + (*node)->height;

   (*node)->left_child = left_subtree->rght_child;
   left_subtree->rght_child = *node;
   *node = left_subtree;
}

bool Tree::AVL::insert(Tree::Node** node, Record* record) {

   Node** root = node;

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   Node** increment_path = node;
   bool balance = false;
   bool side;

   while (*node) {

      if (record->key < (*node)->content->key) {

         int64_t balancing_factor = (*node)->height - ((*node)->rght_child ? (*node)->rght_child->height : -1);
         
         if (!(balance || balancing_factor) || balancing_factor > 1) {
            balance = balancing_factor > 1;
            increment_path = node;
            side = true;
         }

         node = &(*node)->left_child;

      } else {

         int64_t balancing_factor = (*node)->height - ((*node)->left_child ? (*node)->left_child->height : -1);

         if (!(balance || balancing_factor) || balancing_factor > 1) {
            balance = balancing_factor > 1;
            (*increment_path) = *node;
            side = false;
         }

         node = &(*node)->rght_child;
      }
   }

   print_record(record, "\n$0, ");
   std::cout << balance << side;

   if (*increment_path) print_record((*increment_path)->content, ", $0]\n");
   else std::cout << ", {}]\n";

   print_tree(*root);

   *node = new_node;

   if (balance) {
      if (side) {
         if (record->key < (*increment_path)->left_child->content->key)
            rght_rotation(&(*increment_path)->left_child);
         left_rotation(increment_path);
      } else {
         if (record->key > (*increment_path)->rght_child->content->key)
            left_rotation(&(*increment_path)->rght_child);
         rght_rotation(increment_path);
      }
   }

   calculate_height(*root);

   return true;
}