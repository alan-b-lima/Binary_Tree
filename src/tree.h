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

   void print_tree(Tree::Node*);

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

   void left_rotation(Node**);
   void rght_rotation(Node**);

   bool insert(Node**, Record*);

};

// UTF-8, ASCII extended and pure ascii respectivily
// Assuming Linux terminals will support UTF-8

#if defined(__linux__)

char TREE_BRANCHES[][13] = { 
   "\u003A\u2500\u2500\u2500", /* ":───" */
   "\u2502\u0020\u0020\u0020", "\u0020\u0020\u0020\u0020", /* "│   ", "    " */
   "\u251C\u2500\u2500\u2500", "\u2514\u2500\u2500\u2500", /* "├───", "└───" */
};

#elif defined(_WIN32) || defined(_WIN64)

char TREE_BRANCHES[][5] = { 
   "\x3A\xC4\xC4\xC4", /* ":───" */
   "\xB3\x20\x20\x20", "\x20\x20\x20\x20", /* "│   ", "    " */
   "\xC3\xC4\xC4\xC4", "\xC0\xC4\xC4\xC4", /* "├───", "└───" */
};

#else 

char TREE_BRANCHES[][5] = {
   ":---", 
   "|   ", "    ",
   "|---", "'---",
};

#endif

#include "tree.cpp"