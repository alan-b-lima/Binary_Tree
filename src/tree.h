#pragma once

#include "base.h"
#include "record.h"

namespace Tree {

   typedef struct Node {
      Record* content;
      Node* left_child;
      Node* rght_child;
      int64_t height;
   } Node;

   bool insert(Node**, Record*);
   Record* search(Node*, key_t);

   void print(Node*);

   /* Deprecated, not necessary */
   int64_t calculate_height(Node* node) {
      if (!node) return -1;
      
      int64_t lheight = calculate_height(node->left_child);
      int64_t rheight = calculate_height(node->rght_child);

      node->height = 1 + (lheight > rheight ? lheight : rheight);
      return node->height;
   }

   void destruct(Node**, void(*)(Record*) = nullptr);
};

namespace Tree::AVL {

   void smpl_left_rotation(Node**);
   void smpl_rght_rotation(Node**);
   void left_rght_rotation(Node**);
   void rght_left_rotation(Node**);

   bool insert(Node**, Record*);
};

#include "tree.cpp"