#include "base.h"
#include "file.h"
#include "tree.h"
#include "linked_list.h"
#include "application.h"
#include "system.h"

/* Planning the interface
 *
 * Some commands:
 *    get/set seed
 *    test speed and stuff (actual shit)
 *    help
 *    about
 *    exit codes
*/

int main(int argc, char** argv) {

   if (!system_specifics_setup()) {
      std::cout.write(FATAL_ERROR_ENTRY, sizeof(FATAL_ERROR_ENTRY) - 1);
      return -1;
   }

   const uint64_t buffer_size = 1024;
   char buffer[buffer_size];
   JAST::init();

   while (true) {
      std::cout.write("> ", 2);
      std::cin.getline(buffer, buffer_size);

      // switch (exit_t::BAD_ALLOCATION) {
      switch (JAST::interpreter(buffer)) {
         case exit_t::SUCCESS:
            continue;
         
         case exit_t::BAD_ALLOCATION:
            
            esc::style(esc::smk::BOLD, esc::clr::WHITE, esc::clr::RED);
            std::cout.write("Erro Fatal:", 12);

            esc::style(esc::smk::NONE, esc::clr::RED, esc::clr::RESET);
            std::cout.write(" Má Alocação\n", 16);
            goto terminate;

         case exit_t::KEY_ALREADY_EXISTS:
            std::cout.write("Chave já existe na estrutura ", 30);
            continue;

         case exit_t::EXIT_APPLICATION: goto terminate;
      }
   }

terminate:
   esc::reset();
   return 0;
}