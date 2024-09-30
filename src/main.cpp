#include "base.h"
#include "tree.h"
#include <random>
// #include "file.h"

void print_tree(Tree::Node* node, uint64 depth = 0) {

   if (!node) return;

   for (size_t i = 0; i < depth; i++) {
      std::cout.write("   ", 3);
   }

   print_record(node->content, ":[$0, $1, $2, ");
   std::cout << node->height << "]\n";

   print_tree(node->left_child, depth + 1);
   print_tree(node->rght_child, depth + 1);
}

int main(int argc, char** argv) {

   srand(time(NULL));

   Record rec[] = {
      0, 0, "Alan",
      1, 0, "Juan",
      2, 0, "Vitor",
      3, 0, "Jo\x84o Pedro",
      4, 0, "Juan",
      5, 0, "Breno",
      6, 0, "Luan",
      7, 0, "Luiz Felipe",
      8, 0, "Juan",
      9, 0, "32313",
   };

   Tree::Node* root = nullptr;

   word helper = 0b11'1111'1111;
   uint64 height = 0;

   for (size_t i = 0; i < 10; i++) {
      word num = rand() % 10;
      word shift = 1 << num;

      if (~helper & shift) { i--; continue; }

      rec[num].data = i;
      (void)Tree::insert(&root, &rec[num]);
      helper ^= shift;
   }

   print_tree(root);

   return 0;
}