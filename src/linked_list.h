#pragma once

#include "base.h"
#include "record.h"
#include "system.h"

namespace LinkedList {

   typedef struct Node {
      Record* content;
      Node* next_node;
   } Node;

   bool insert(Node**, Record*);
   Record* search(Node*, key_t);

   void print(Node*);

   void destruct(Node**, void(*)(Record*) = nullptr);
}