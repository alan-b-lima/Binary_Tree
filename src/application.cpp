#include "application.h"

void JAST::__cmd_help(uint64_t argc, char* prompt) {

   byte command = command_t::_help;
   if (argc) command = access_map(COMMANDS, COMMAND_LIST_SIZE, prompt);

   switch (command) {

      case command_t::_help: {
         std::cout.write(
            "Lista de todos os comando:\n\n"
            "   chfocus Muda a estrutura em foco\n"
            "   create  Cria um registro e o insere na estrutura em foco\n"
            "   exit    Mesmo que `quit`\n"
            "   help    Mostra essa tela\n"
            "   init    Mostra a tela de entrada\n"
            "   load    Carrega dados de um arquivo para alguma estrutura\n"
            "   new     Cria uma nova estrutura\n"
            "   print   Imprime estruturas\n"
            "   quit    Encerra a aplicação\n"
            "   save    Salva os dados de uma estrutura para algum arquivo\n"
            "   search  Procura por uma chave na estrutura em foco\n"
            "   test    Realisa testes de busca na estrutura em foco\n\n"
            "Digite `help <comando>` para obter mais informações sobre um comando\n"
            , 619);
      } break;

      case command_t::_chfocus: 
         std::cout.write(
            "chfocus $<id> - Foca a estrutura de id <id>\n"
            "chfocus       - Remove o foco de estrutrura\n"
            , 88);
         break;

      case command_t::_create: {
         std::cout.write(
            "create $<id>... <key> <data> <name> - Cria um registro e insere nas estruturas de id <id>...\n"
            "create <id> <data> <name>           - Cria um registro e insere na estrutrura em foco\n"
            , 179);
      } break;

      case command_t::_init: {
         std::cout.write(
            "init - Mostra a tela de entrada\n"
            , 0);
      } break;

      case command_t::_load: std::cout << "load WIP\n"; break;

      case command_t::_new: {
         std::cout.write(
            "new <estrutura> - Cria uma nova estrutura\n\n"
            "Parametros:\n"
            "   <estrutura>: tree; avl ou avl_tree; linked_list ou ll\n"
            , 112);
      } break;

      case command_t::_print: {
         std::cout.write(
            "print       - Imprime a estrutura em foco, se nenhuma estrutura em foco,\n"
            "              imprime o primeiro registro de todas estruturas e seus id's\n"
            "print $<id> - Imprime a estrutura de id <id>, se existir\n"
            "print all   - imprime o primeiro registro de todas estruturas e seus id's\n\n"
            , 279);
      } break;

      case command_t::_quit: {
         std::cout.write(
            "exit - Encerra a aplicação\n"
            "quit - Encerra a aplicação\n"
            , 58);
      } break;

      case command_t::_save: std::cout << "save WIP\n"; break;
      case command_t::_search: std::cout << "search WIP\n"; break;
      case command_t::_test: std::cout << "test WIP\n"; break;

      default:
         std::cout.write(COMMAND_NOT_FOUND, sizeof(COMMAND_NOT_FOUND) - 1);
         break;
   }
}

void JAST::init() {
   get_terminal_dimensions(state.width, state.height);

   esc::clear();
   esc::move_to(0, 0);

   for (uint64_t i = 0; i < state.width; i++)
      std::cout.put('-');
   std::cout.put('\n');

   esc::color(esc::FOREGROUND, 0xF1E6B8);
   std::cout.write(LITTLE_CHICK, sizeof(LITTLE_CHICK) - 1);
   const uint64_t little_chick_width = 31;

   esc::move_to(1, 0);
   esc::reset();

   uint64_t lines = 0;

   lines += print_in_column(ABOUT, little_chick_width, state.width - little_chick_width);
   lines += print_in_column(AUTHORS, little_chick_width, state.width - little_chick_width);

   esc::italic();
   lines += print_in_column(AUTHORS_NAMES, little_chick_width, state.width - little_chick_width);

   esc::reset();
   esc::move_to(2 + maximum(lines, 14 /* little_chick_height */), 0);
}

exit_t JAST::interpreter(char* prompt) {

   uint64_t argc = process_args(prompt);
   std::cout << argc << std::endl;

   if (!argc) return exit_t::SUCCESS;

   switch (access_map(COMMANDS, COMMAND_LIST_SIZE, prompt)) {

      case command_t::_create: return __cmd_create(argc - 1, prompt);

      case command_t::_init: init(); break;

      case command_t::_help: __cmd_help(argc - 1, prompt); break;
      case command_t::_new: return __cmd_new(argc - 1, prompt);

      case command_t::_print: __cmd_print(argc - 1, prompt); break;

      case command_t::_quit:

         while (true) {
            std::cout.write(CONFIRM_EXIT, sizeof(CONFIRM_EXIT) - 1);

            char answer = std::cin.get();
            std::cin.ignore(64, '\n');

            if (answer == 's') return exit_t::EXIT_APPLICATION;
            if (answer == 'n') break;
         }

         break;

      case NOT_FOUND:
         esc::color(esc::YELLOW, esc::FOREGROUND);
         std::cout.write(COMMAND_NOT_FOUND, sizeof(COMMAND_NOT_FOUND) - 1);
         esc::reset();
         break;

      default:
         std::cout.write("WIP\n", 4);
         break;
   }

   return exit_t::SUCCESS;
}

void JAST::__cmd_chfocus(uint64_t argc, char* prompt) {
   if (!argc) {
      state.focused = nullptr;
      return;
   }

   if (prompt[0] == '$') {
      state.focused = find_structure(string_to_int_consume(++prompt));
      if (!state.focused) {
            esc::color(esc::FOREGROUND, esc::BRIGHT_RED);
            std::cout.write(STRUCT_NOT_FOUND, sizeof(STRUCT_NOT_FOUND) - 1);
            esc::reset();
      }
   }

}

exit_t JAST::__cmd_create(uint64_t argc, char* prompt) {

   uint64_t id_count = 0;
   for (uint64_t i = 0; id_count < argc; i++) {
      if (prompt[i] != '$') break;
      id_count++;

      while (prompt[i++]);
   }

   std::cout << id_count << '\n';
   return exit_t::SUCCESS;
}

exit_t JAST::__cmd_new(uint64_t argc, char* prompt) {

   byte structure;

   if (
      !argc ||
      (structure = access_map(STRUCTURES, STRUCTURE_LIST_SIZE, prompt)) == NOT_FOUND)
   {
      esc::color(esc::RED, esc::FOREGROUND);
      std::cout.write(INVALID_INPUT, sizeof(INVALID_INPUT) - 1);
      esc::reset();

      return exit_t::SUCCESS;
   }

   StructStack* temp = state.stack;
   id_t next_id = state.stack ? state.stack->id + 1 : 0;

   state.stack = new (std::nothrow) StructStack{ next_id, kind_t(structure), nullptr, temp };
   if (!state.stack) {
      state.stack = temp;
      return exit_t::BAD_ALLOCATION;
   }

   return exit_t::SUCCESS;
}

void JAST::__cmd_print(uint64_t argc, char* prompt) {

   StructStack* strc;

   if (!argc) {
      
      if (state.focused) {
         
         strc = state.focused;
         goto print_specific;

      } else goto print_all;

   } else switch (prompt[0]) {

      case '$':
         strc = find_structure(string_to_int_consume(++prompt));
         if (!strc) {
            esc::color(esc::FOREGROUND, esc::BRIGHT_RED);
            std::cout.write(STRUCT_NOT_FOUND, sizeof(STRUCT_NOT_FOUND) - 1);
            esc::reset();

            return;
         } else goto print_specific;

      case 'a':
         if (match_consume_word("all", prompt)) goto print_all;

      default:
         std::cout.write(INVALID_INPUT, sizeof(INVALID_INPUT) - 1);
         return;
   }

print_specific:
   if (strc->kind == kind_t::LINKED_LIST) {
      std::cout.write(LL_IDENTIFIER, sizeof(LL_IDENTIFIER) - 1);
      std::cout.put('\n');

      LinkedList::print(strc->node.linked_list);

   } else {
      std::cout.write(TREE_IDENTIFIER, sizeof(TREE_IDENTIFIER) - 1);
      std::cout.put('\n');

      Tree::print(strc->node.tree);
   }

   return;

print_all:
   for (StructStack* s = state.stack; s; s = s->next_node) {

      Record* record;
      if (s->kind == kind_t::LINKED_LIST) {
         std::cout.write(LL_IDENTIFIER, sizeof(LL_IDENTIFIER) - 1);
         record = safe_access(s->node.linked_list, content, nullptr);
      } else {
         std::cout.write(TREE_IDENTIFIER, sizeof(TREE_IDENTIFIER) - 1);
         record = safe_access(s->node.tree, content, nullptr);
      }

      std::cout << '$' << s->id << ": ";
      print_record(record, "{$0: $1, $2\n");
   }
}

bool JAST::match_consume_word(const char* compare, char*& consume) {

   for (uint64_t i = 0; compare[i] == consume[i]; i++) {
      if (compare[i]) continue;

      consume += i + 1;
      return true;
   }

   return false;
}

uint64_t JAST::string_to_int_consume(char*& consume) {
   uint64_t num = 0;
   bool sign = false;

   if (*consume == '-') {
      sign = true;
      consume++;
   }

   while (*consume) {
      if ('0' <= *consume && *consume <= '9')
         num = 10 * num + *consume - '0';
      consume++;
   }

   if (sign) num = -num;
   return num;
}

template <uint64_t str_size>
byte JAST::access_map(Map<str_size>* map, uint64_t length, char*& prompt) {
   uint64_t index;

   for (index = 0; index < length && map[index].alias[0] <= prompt[0]; index++)
      if (match_consume_word(map[index].alias, prompt)) return map[index].command;

   return NOT_FOUND;
}

uint64_t JAST::print_in_column(const char* text, word start, word width) {
   esc::move_to(start);

   uint64_t lines = 0, index = 0, length = 0;
   while (true) {

      if (text[index] == '\0') {
         if (index > 0) {
            std::cout.write(text, index);
            lines++;
         }

         return lines;
      }

      if (text[index] == '\n') {
         if (index > 0) {
            std::cout.write(text, ++index);
            text += index;

            length = 0;
            index = 0;
         }

         esc::move_to(start);
         lines++;

         continue;
      }

      if (text[index] == ' ') {
         length = index;
      }

      if (index >= width) {

         uint8_t inc = 0;

         if (!length) {
            length = width;
            index = 0;
         } else {
            index -= length;
            inc = 1;
         }

         std::cout.write(text, length);
         text += length + inc;
         length = 0;

         std::cout.put('\n');
         esc::move_to(start);
         lines++;

         continue;
      }

      index++;
   }
}