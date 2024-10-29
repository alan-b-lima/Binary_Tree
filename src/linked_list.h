#pragma once

#include "base.h"
#include "record.h"
#include "../rc/strings.cpp"

namespace LinkedList {

   typedef struct Node {
      Record* content;
      Node* next_node;
   } Node;

   exit_t insert(Node**, Record*);
   Record* search(Node*, key_t);

   void print(Node*);

   void destruct(Node**, void(*)(Record*) = nullptr);
}