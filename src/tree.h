#pragma once

#include "base.h"
#include "record.h"

namespace Tree {

   typedef struct Node {
      Record* content;
      Node* left_child;
      Node* rght_child;
      uint64 height;
   } Node;

   bool insert(Node**, Record*);
   Record* Tree::search(Tree::Node*, key_t);

   void print_tree(Tree::Node* node, uint64 depth = 0) {
      if (!node) return;

      for (size_t i = 0; i < depth; i++) {
         std::cout.write("   ", 3);
      }

      print_record(node->content, ":[$0, $1, ");
      std::cout << node->height << "]\n";

      print_tree(node->left_child, depth + 1);
      print_tree(node->rght_child, depth + 1);
   }

   /* Deprecated, not necessary */
   void calculate_height(Node* node) {

      if (!node) return;
      if (!node->left_child && !node->rght_child) {
         node->height = 0;
         return;
      }

      uint64 lheight = 0, rheight = 0;
      if (node->left_child) {
         calculate_height(node->left_child);
         lheight = node->left_child->height;
      }
      if (node->rght_child) {
         calculate_height(node->rght_child);
         rheight = node->rght_child->height;
      }

      node->height = 1 + (lheight >= rheight ? lheight : rheight);
   }
};

namespace Tree::AVL {

   void left_rotation(Node**);
   void rght_rotation(Node**);

   bool insert(Node**, Record*);

};

#include "tree.cpp"