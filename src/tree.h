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