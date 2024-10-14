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
   // int main() { int argc = 3; char argv[][11] = { "", "0", "14" };

   time_t seed;
   size_t n_of_records = 16;
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

   Tree::Node* root = nullptr;
   BitTools::mword* helper = BitTools::initialize(
      Stack::allocate<BitTools::mword>(BitTools::size(n_of_records)),
      n_of_records
   );

   for (uint64_t i = 0; i < n_of_records; i++) {
      uint64_t num = rand() % n_of_records;

      while (BitTools::getbit(helper, num))
         if (++num >= n_of_records) num = 0;

      (void)BitTools::flipbit(helper, num);
      Record* record = new Record{ key_t(num & 0xFFFF) };
      Generator::populate_record_randomly(record);
      record->data = i;

      (void)Tree::AVL::insert(&root, record);
   }

   Stack::release(helper);

   std::cout << "\nFinal:\n";
   Tree::print(root);

   Tree::destruct(&root, destruct_record);
   return 0;
}