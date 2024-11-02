#include "linked_list.h"

exit_t LinkedList::insert(Node** node, Record* record) {
   Node* new_node = new (std::nothrow) Node{ record, *node };
   if (!new_node) return BAD_ALLOCATION;

   *node = new_node;
   return SUCCESS;
}

Record* LinkedList::search(Node* node, Record::key_t key) {
   while (node) {
      if (node->content->key == key)
         return node->content;

      node = node->next_node;
   }

   return nullptr;
}

Record* LinkedList::search_c(Node* node, Record::key_t key, uint64_t& comparisons) {
   
   comparisons++;
   while (node) {
      
      comparisons++;
      if (node->content->key == key)
         return node->content;

      node = node->next_node;
   }

   return nullptr;
}

void LinkedList::print(Node* node, int64_t level) {
   if (!node) {
      std::cout.write("{}\n", 3);
      return;
   }

   if (level < 0) level = 0x7FFF'FFFF'FFFF'FFFF;

   std::cout.write(BRANCH_ROOT, sizeof(BRANCH_ROOT) - 1);
   if (level-- <= 0) { std::cout.write("{...}\n", 6); return; }
   
   print_record(node->content, "{$0, $1, $2\n");

   for (node = node->next_node; node; node = node->next_node, level--) {

      std::cout.write(NO_BRANCH, sizeof(NO_BRANCH) - 1);
      if (level <= 0) { std::cout.write("{...}\n", 6); return; }
      
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