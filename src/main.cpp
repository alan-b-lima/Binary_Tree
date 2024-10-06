#include "base.h"
#include "tree.h"

#include <iostream>
#include <random>
// #include "file.h"

int main(int argc, char** argv) {

   time_t seed;
   if (argc > 1) seed = atoi(argv[1]);
   else seed = time(NULL);

   std::cout << seed;
   srand(seed);

   Record rec[] = {
      0, 0, "Alan",
      1, 0, "Ot\xA0vio",
      2, 0, "Vitor",
      3, 0, "Jo\x84o Pedro",
      4, 0, "Miguel",
      5, 0, "Breno",
      6, 0, "Luan",
      7, 0, "Luiz Felipe",
      8, 0, "Juan Pablo",
      9, 0, "Davi",
   };

   Tree::Node* root = nullptr;
   word helper = 0b11'1111'1111;

   for (size_t i = 0; i < 10; i++) {
      word num = rand() % 10;
      word shift = 1 << num;

      if (~helper & shift) { i--; continue; }

      rec[num].data = i;
      (void)Tree::AVL::insert(&root, &rec[num]);
      helper ^= shift;
   }

   std::cout << "\nFinal:\n";
   print_tree(root);
   return 0;
}