#pragma once

#include "base.h"
#include "record.h"

#include "../lib/bittools.h"
#include "../lib/stack.h"

#include "../rc/strings.cpp"

namespace Tree {

   typedef struct Node {
      Record* content;
      Node* left_child;
      Node* rght_child;
      int64_t height;
   } Node;

   enum exit_t : byte {
      SUCCESS,
      BAD_ALLOCATION,
      KEY_ALREADY_EXISTS,
   };

   exit_t insert(Node**, Record*);
   Record* search(Node*, key_t);

   void print(Node*, int64_t = -1);

   /* Deprecated, not necessary */
   int64_t calculate_height(Node* node) {
      if (!node) return -1;

      int64_t lheight = calculate_height(node->left_child);
      int64_t rheight = calculate_height(node->rght_child);

      node->height = 1 + maximum(lheight, rheight);
      return node->height;
   }

   void destruct(Node**, void(*)(Record*) = nullptr);
};

namespace Tree::AVL {
   void smpl_left_rotation(Node**);
   void smpl_rght_rotation(Node**);
   void left_rght_rotation(Node**);
   void rght_left_rotation(Node**);

   exit_t insert(Node**, Record*);
};