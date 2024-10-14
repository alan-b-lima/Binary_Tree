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
   void print_old(Node*);

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

// UTF-8, ASCII extended and pure ascii respectivily
// Assuming Linux terminals will support UTF-8

#if defined(__linux__) || 1

char BRANCH_ROOT[]      = "\u003A\u2500\u2500\u2500"; /* ":───" */
char BRANCH_DOWN[]      = "\u2502\u0020\u0020\u0020"; /* "│   " */
char NO_BRANCH[]        = "\u0020\u0020\u0020\u0020"; /* "    " */
char BRANCH_SIDE[]      = "\u251C\u2500\u2500\u2500"; /* "├───" */
char BRANCH_DOWN_SIDE[] = "\u2514\u2500\u2500\u2500"; /* "└───" */
char BRANCH_UP_SIDE[]   = "\u250C\u2500\u2500\u2500"; /* "┌───" */

#elif (defined(_WIN32) || defined(_WIN64))

char BRANCH_ROOT[]      = "\x3A\xC4\xC4\xC4"; /* ":───" */
char BRANCH_DOWN[]      = "\xB3\x20\x20\x20"; /* "│   " */
char NO_BRANCH[]        = "\x20\x20\x20\x20"; /* "    " */
char BRANCH_SIDE[]      = "\xC3\xC4\xC4\xC4"; /* "├───" */
char BRANCH_DOWN_SIDE[] = "\xC0\xC4\xC4\xC4"; /* "└───" */
char BRANCH_UP_SIDE[]   = "\xDA\xC4\xC4\xC4"; /* "┌───" */

#else 

char BRANCH_ROOT[]      = ":---"; 
char BRANCH_DOWN[]      = "|   ";
char NO_BRANCH[]        = "    ";
char BRANCH_SIDE[]      = "|---";
char BRANCH_DOWN_SIDE[] = "+---";
char BRANCH_UP_SIDE[]   = "+---";

#endif

#include "tree.cpp"