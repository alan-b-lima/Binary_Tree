#include "base.h"
#include "tree.h"
#include "generator.h"

/* Planning the interface
 *
 * Some commands:
 *    generate records
 *    get/set seed
 *    print tree
 *    test speed and stuff (actual shit)
 *    help
 *    about
 *    exit codes
*/

int main(int argc, char** argv) {

   time_t seed;
   size_t n_of_records = 100;
   switch (argc) {
      case 3:
         n_of_records = atoi(argv[2]);

      case 2:
         seed = atoi(argv[1]);
         if (seed) break;

      case 1:
         seed = time(NULL);
         break;

      default:
         return 1;
   }

   std::cout << seed << std::endl;
   srand(seed);

   Record* rec = new Record[n_of_records];

   Tree::Node* root = nullptr;
   byte* helper = Stack::allocate<byte>((n_of_records + 7) >> 3);
   BitTools::initialize(helper, n_of_records);

   for (size_t i = 0; i < n_of_records; i++) {
      // uint32_t num = rand() % n_of_records;

      // if (BitTools::getbit(helper, num)) { i--; continue; }
      
      // (void)BitTools::flipbit(helper, num);
      Generator::populate_record_randomly(rec[i]);
      rec[i].key = rec[i].data;
      rec[i].data = i;

      //rec[i].key = i;

      (void)Tree::insert(&root, &rec[i]);
   }

   //Stack::release(helper);
   
   std::cout << "\nFinal:\n";
   Tree::print_tree(root);

   Tree::destruct(&root);
   delete[] rec;

   return 0;
}