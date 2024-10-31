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
   Record* search(Node*, Record::key_t);

   void print(Node*, int64_t = -1);

   void destruct(Node**, void(*)(Record*) = nullptr);
}