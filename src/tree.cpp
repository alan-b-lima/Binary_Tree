#include "tree.h"

bool Tree::insert(Tree::Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   Node* increment_path = *node;
   uint64 height = increment_path ? increment_path->height : 1;

   while (true) {

      if (!*node) {

         if (!height) while (increment_path) {
            increment_path->height++;

            increment_path = record->key < increment_path->content->key ?
               increment_path->left_child : increment_path->rght_child;
         }

         *node = new_node;
         return true;
      }

      if ((*node)->height + 1 != height)
         increment_path = *node;

      height = (*node)->height;
      node = record->key < (*node)->content->key ?
         &(*node)->left_child : &(*node)->rght_child;

   }
}

void Tree::AVL::left_rotation(Tree::Node** node) {
   Node* rght_subtree = (*node)->rght_child;
   Node* midd_subtree = rght_subtree->left_child;

   (*node)->rght_child = midd_subtree;
   rght_subtree->left_child = *node;

   *node = rght_subtree;
}

void Tree::AVL::rght_rotation(Tree::Node** node) {
   Node* left_subtree = (*node)->left_child;
   Node* midd_subtree = left_subtree->rght_child;

   (*node)->left_child = midd_subtree;
   left_subtree->rght_child = *node;

   *node = left_subtree;
}

bool Tree::AVL::insert(Tree::Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   Node* increment_path = *node;
   uint64 height = increment_path ? increment_path->height : 0;

   while (true) {

      if (!*node) {

         if (!height) while (increment_path) {
            increment_path->height++;

            increment_path = record->key < increment_path->content->key ?
               increment_path->left_child : increment_path->rght_child;
         }

         *node = new_node;
         return true;
      }

      if ((*node)->height + 1 != height)
         increment_path = *node;

      height = (*node)->height;
      node = record->key < (*node)->content->key ?
         &(*node)->left_child : &(*node)->rght_child;

   }
}