#include "base.h"
#include "tree.h"
#include "generator.h"
// #include "file.h"

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
   if (argc == 1) seed = atoi(argv[1]);
   else seed = time(NULL);

   // std::cout << seed << std::endl;
   srand(seed);

   Record rec;

   for (size_t i = 0; i < (size_t)atoi(argv[2]); i++) {
      Generator::populate_record_randomly(rec);
      print_record(&rec, "$2\n");
   }

   return 0;
}