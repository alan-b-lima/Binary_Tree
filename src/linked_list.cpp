#include "linked_list.h"

bool LinkedList::insert(Node** node, Record* record) {
   Node* new_node = new (std::nothrow) Node{ record, *node };
   if (!new_node) return false;

   *node = new_node;
   return true;
}

Record* LinkedList::search(Node* node, key_t key) {
   for (; node; node = node->next_node) {
      if (node->content->key == key)
         return node->content;
   }
   
   return nullptr;
}

void LinkedList::print(Node* node) {
   if (!node) {
      std::cout.write("{}\n", 3);
      return;
   }

   std::cout.write(BRANCH_ROOT, sizeof(BRANCH_ROOT) - 1);
   print_record(node->content, "{$0, $1, $2\n");

   for (node = node->next_node; node; node = node->next_node) {
      std::cout.write(NO_BRANCH, sizeof(NO_BRANCH) - 1);
      print_record(node->content, "{$0, $1, $2\n");
   }
}

void LinkedList::destruct(Node** node, void(*handler)(Record*)) {
   while (*node) {
      if (handler)
         handler((*node)->content);

      Node* next = (*node)->next_node;
      delete (*node);
      *node = next;
   }

   *node = nullptr;
}