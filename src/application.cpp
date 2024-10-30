#include "application.h"

void JAST::__cmd_help(uint64_t argc, char* prompt) {

   byte command = command_t::_help;
   if (argc) command = access_map(COMMANDS, COMMAND_LIST_SIZE, prompt);

   switch (command) {

      case command_t::_help: {
         std::cout.write(
            "Lista de todos os comandos:\n\n"
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
            , 620);
      } break;

      case command_t::_chfocus: {
         std::cout.write(
            "chfocus $<id>  - Foca a estrutura de id <id>\n"
            "chfocus remove - Remove o foco de estrutrura\n"
            "chfocus        - Mostra a estrutrura em foco\n"
            , 135);
         break;
      }

      case command_t::_create: {
         std::cout.write(
            "create $<id> <key> <data> <name> - Cria um registro e insere na estrutura de id <id>\n"
            "create $<id> random              - Cria um registro aleatório e insere na estrutura de id <id>\n"
            "create <key> <data> <name>       - Cria um registro e insere na estrutrura em foco\n"
            "create random <count>            - Cria <count> registros aleatórios e insere-os na estrutura em foco\n"
            "create random                    - Cria um registro aleatório e insere na estrutura em foco\n"
            , 480);
         break;
      }

      case command_t::_init: {
         std::cout.write(
            "init - Mostra a tela de entrada\n"
            , 0);
         break;
      }

      case command_t::_load: std::cout << "load WIP\n"; break;

      case command_t::_new: {
         std::cout.write(
            "new <struct>                        - Cria uma nova estrutura vazia\n"
            "new <struct> <count> <rule>         - Cria uma nova estrutura com <count> registros aleatórios\n"
            "new <struct> <count> <rule> <order> - Cria uma nova estrutura com <count> registros aleatórios,\n"
            "                                      seguindo uma regra <rule> e chaves em [0, <count> * <order>)\n"
            "   <struct>: tree; avl ou avl_tree; linked_list ou ll\n"
            "   <rule>: ordered, random, inversed\n"
            , 451);
         break;
      }

      case command_t::_print: {
         std::cout.write(
            "print       - Imprime a estrutura em foco, se nenhuma estrutura em foco,\n"
            "              imprime o primeiro registro de todas estruturas e seus id's\n"
            "print $<id> - Imprime a estrutura de id <id>, se existir\n"
            "print all   - imprime o primeiro registro de todas estruturas e seus id's\n\n"
            , 279);
         break;
      }

      case command_t::_quit: {
         std::cout.write(
            "exit - Encerra a aplicação\n"
            "quit - Encerra a aplicação\n"
            , 58);
         break;
      }

      case command_t::_save: std::cout << "save WIP\n"; break;
      case command_t::_search: std::cout << "search WIP\n"; break;
      case command_t::_test: std::cout << "test WIP\n"; break;

      default: {
         esc::color(esc::YELLOW, esc::FOREGROUND);
         std::cout.write(COMMAND_NOT_FOUND, sizeof(COMMAND_NOT_FOUND) - 1);
         esc::reset();

         break;
      }
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
   // std::cout << argc << std::endl;

   if (!argc) return exit_t::SUCCESS;

   // char* c = prompt;
   // for (uint64_t i = 0; i < argc; c++) {
   //    if (!*c) { std::cout.put('#'); i++; }
   //    else std::cout.put(*c);
   // }

   // std::cout.put('\n');

   switch (access_map(COMMANDS, COMMAND_LIST_SIZE, prompt)) {

      case command_t::_chfocus: __cmd_chfocus(argc - 1, prompt); break;
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

      if (!state.focused) {
         std::cout.write("Nenhuma estrutura está em foco!\n", 33);
         return;
      }

      if (state.focused->kind == kind_t::LINKED_LIST) {
         std::cout.write(LL_IDENTIFIER, sizeof(LL_IDENTIFIER) - 1);
         std::cout.put('\n');

         LinkedList::print(state.focused->node.linked_list);

      } else {
         if (state.focused->kind == kind_t::TREE) std::cout.write(TREE_IDENTIFIER, sizeof(TREE_IDENTIFIER) - 1);
         else std::cout.write(AVL_TREE_IDENTIFIER, sizeof(AVL_TREE_IDENTIFIER) - 1);
         std::cout.put('\n');

         Tree::print(state.focused->node.tree);
      }

      return;
   }

   if (prompt[0] == '$') {
      state.focused = find_structure(string_to_int_consume(++prompt));
      if (!state.focused) {
         esc::color(esc::FOREGROUND, esc::BRIGHT_RED);
         std::cout.write(STRUCT_NOT_FOUND, sizeof(STRUCT_NOT_FOUND) - 1);
         esc::reset();
      }

      return;
   }

   if (match_consume_word("remove", prompt)) {
      state.focused = nullptr;
      return;
   }

   esc::color(esc::RED, esc::FOREGROUND);
   std::cout.write(INVALID_INPUT, sizeof(INVALID_INPUT) - 1);
   esc::reset();
}

exit_t JAST::__cmd_create(uint64_t argc, char* prompt) {
   return exit_t::BAD_ALLOCATION;
}
// exit_t JAST::__cmd_create(uint64_t argc, char* prompt) {

//    // Count how many id's have been given
//    uint64_t id_count = 0, i;
//    for (i = 0; id_count < argc; i++) {
//       if (prompt[i] != '$') break;
//       id_count++;

//       while (prompt[i++]);
//    }

//    char* ids_start = prompt;
//    prompt += i + 1;

//    uint64_t random_struct_count = 0;
//    Record* record = new (std::nothrow) Record;
//    if (!record) return exit_t::BAD_ALLOCATION;

//    if (argc - id_count >= 1) {

//       if (match_consume_word("randomly", prompt)) {

//          if (id_count > 1) {
//             esc::color(esc::YELLOW, esc::FOREGROUND);
//             std::cout.write("Inserir aleatóriamente em multíplas estruturas não é permitido!\n", 68);
//             esc::reset();

//             return exit_t::SUCCESS;
//          }

//          if (argc - id_count >= 2) {
//             uint64_t random_struct_count = string_to_int_consume(prompt);
//             if (!random_struct_count) return exit_t::SUCCESS;
//          }

//          if (random_struct_count <= 1) {
//             populate_record_randomly(record);
//             random_struct_count = 0;
//          }

//       } else if (argc - id_count >= 3) {

//          record->key = string_to_int_consume(prompt);
//          int data = string_to_int_consume(prompt);
//          write_record(record, data, prompt);

//       } else {
//          esc::color(esc::RED, esc::FOREGROUND);
//          std::cout.write(INVALID_INPUT, sizeof(INVALID_INPUT) - 1);
//          esc::reset();

//          return exit_t::SUCCESS;
//       }

//    } else goto not_enough_args;

//    StructStack** id_stack;
//    bool found_ids = false;

//    if (!id_count) {

//       // If no id's have been given and there's no state to focus,
//       // then quit the function saying "not enough args"
//       if (!state.focused) goto not_enough_args;

//       // its access is equivalent to accessing the 0-th position of
//       // an array, so, no worries
//       id_stack = &state.focused;
//       id_count = 1;

//    } else {
//       id_stack = Stack::allocate<StructStack*>(id_count);

//       for (uint64_t i = 0; i < id_count; i++) {
//          id_t id = string_to_int_consume(++ids_start);
//          id_stack[i] = find_structure(id);

//          if (!id_stack[i]) {
//             id_count--;
//             i--;

//             esc::color(esc::YELLOW, esc::FOREGROUND);
//             std::cout << '$' << id << " - ";
//             std::cout.write(STRUCT_NOT_FOUND, sizeof(STRUCT_NOT_FOUND) - 1);

//             esc::reset();
//             continue;
//          }

//          found_ids = true;
//       }

//       if (!found_ids) {
//          Stack::release(id_stack);
//          goto no_structure_found;
//       }
//    }

//    for (uint64_t i = 0; i < id_count; i++) {
//       if (random_struct_count) {

//          for (uint64_t j = 0; j < random_struct_count; j++) {

//             record = new (std::nothrow) Record;
//             if (!record) {
//                if (found_ids) Stack::release(id_stack);
//                return exit_t::BAD_ALLOCATION;
//             }

//             bool inserted = false;
//             populate_record_randomly(record);
//             exit_t response;
//             uint64_t k = 0;

//             for (k = 0; response == exit_t::KEY_ALREADY_EXISTS; k++) {

//                if (k >= ITERATION_LIMIT) {
//                   esc::color(esc::BLUE, esc::FOREGROUND);
//                   std::cout.write("Uma nova chave única não foi encontrada!\n", 43);
//                   esc::reset();

//                   if (found_ids) Stack::release(id_stack);
//                   return exit_t::SUCCESS;
//                }

//                record->key = key_t(Random::rand());

//                switch (state.focused->kind) {
//                   case LINKED_LIST: response = LinkedList::insert(&id_stack[i]->node.linked_list, record); break;
//                   case AVL_TREE: response = Tree::AVL::insert(&id_stack[i]->node.tree, record); break;
//                   case TREE: response = Tree::insert(&id_stack[i]->node.tree, record); break;
//                }

//                if (response == exit_t::BAD_ALLOCATION) goto bad_allocation;
//             }
//          }

//       } else {

//          exit_t response;

//          switch (state.focused->kind) {
//             case LINKED_LIST: response = LinkedList::insert(&id_stack[i]->node.linked_list, record); break;
//             case AVL_TREE: response = Tree::AVL::insert(&id_stack[i]->node.tree, record); break;
//             case TREE: response = Tree::insert(&id_stack[i]->node.tree, record); break;
//          }

//          if (response == exit_t::BAD_ALLOCATION) goto bad_allocation;
//          if (response == exit_t::KEY_ALREADY_EXISTS) {
//             esc::color(esc::YELLOW, esc::FOREGROUND);
//             std::cout << "A chave " << record->key << " já existe na estrutura de id $" << id_stack[i]->id << '\n';
//             esc::reset();
//          }
//       }
//    }

//    if (found_ids) Stack::release(id_stack);
//    return exit_t::SUCCESS;

// bad_allocation:
//    if (found_ids) Stack::release(id_stack);
//    return exit_t::SUCCESS;

// no_structure_found:
//    esc::color(esc::RED, esc::FOREGROUND);
//    std::cout.write(NO_STRUCT_FOUND, sizeof(NO_STRUCT_FOUND) - 1);
//    esc::reset();

//    return exit_t::SUCCESS;

// not_enough_args:
//    esc::color(esc::BRIGHT_RED, esc::FOREGROUND);
//    std::cout.write("Argumentos Insuficientes\n", 25);
//    esc::reset();

//    return exit_t::SUCCESS;
// }

exit_t JAST::__cmd_new(uint64_t argc, char* prompt) {

   if (argc) {

      kind_t structure = (kind_t)access_map(STRUCTURES, STRUCTURE_LIST_SIZE, prompt);
      if (structure == NOT_FOUND) goto invalid_input;

      StructStack* temp = state.stack;
      id_t next_id = state.stack ? state.stack->id + 1 : 0;

      state.stack = new (std::nothrow) StructStack{ next_id, structure, nullptr, temp };
      if (!state.stack) {
         state.stack = temp;
         return exit_t::BAD_ALLOCATION;
      }

      if (argc < 3) return exit_t::SUCCESS;

      uint64_t n_of_records = string_to_int_consume(prompt);
      if (!n_of_records) return exit_t::SUCCESS;

      rule_t rule = (rule_t)access_map(RULES, RULE_LIST_SIZE, prompt);

      uint64_t order = (argc >= 4) ? string_to_int_consume(prompt) : 1;
      if (order < 1) order = 1;

      uint64_t max_key = order * n_of_records;

      BitTools::mword* helper = BitTools::initialize(
         Stack::allocate<BitTools::mword>(BitTools::size(max_key)),
         max_key
      );

      uint64_t key = (rule == _inversed) ? max_key : 0;

      for (uint64_t i = 0; i < n_of_records; i++) {

         switch (rule) {

            case _random:
               key = uint64_t(Random::rand() % max_key);

               while (BitTools::getbit(helper, key))
                  if (++key >= n_of_records) key = 0;

               BitTools::flipbit(helper, key);
               break;

            case _ordered: key += order; break;
            case _inversed: key -= order; break;
         }

         Record* record = new (std::nothrow) Record{ key_t(key) };
         if (!record) {
            Stack::release(helper);
            return exit_t::BAD_ALLOCATION;
         }

         populate_record_randomly(record);

         exit_t response;
         switch (state.stack->kind) {

            case LINKED_LIST:
               response = LinkedList::insert(&state.stack->node.linked_list, record);
               break;

            case AVL_TREE:
               response = Tree::AVL::insert(&state.stack->node.tree, record);
               break;

            case TREE:
               response = Tree::insert(&state.stack->node.tree, record);
               break;
         }

         if (response == exit_t::BAD_ALLOCATION) {
            Stack::release(helper);
            return exit_t::BAD_ALLOCATION;
         }
      }

      return exit_t::SUCCESS;
   }

invalid_input:
   esc::color(esc::RED, esc::FOREGROUND);
   std::cout.write(INVALID_INPUT, sizeof(INVALID_INPUT) - 1);
   esc::reset();

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
            esc::color(esc::BRIGHT_RED, esc::FOREGROUND);
            std::cout.write(STRUCT_NOT_FOUND, sizeof(STRUCT_NOT_FOUND) - 1);
            esc::reset();

            return;
         } else goto print_specific;

      case 'a':
         if (match_consume_word("all", prompt)) goto print_all;

      default:
         esc::color(esc::RED, esc::FOREGROUND);
         std::cout.write(INVALID_INPUT, sizeof(INVALID_INPUT) - 1);
         esc::reset();
         return;
   }

print_specific:
   if (strc->kind == kind_t::LINKED_LIST) {
      std::cout.write(LL_IDENTIFIER, sizeof(LL_IDENTIFIER) - 1);
      std::cout.put('\n');

      LinkedList::print(strc->node.linked_list);

   } else {
      if (strc->kind == kind_t::TREE) std::cout.write(TREE_IDENTIFIER, sizeof(TREE_IDENTIFIER) - 1);
      else std::cout.write(AVL_TREE_IDENTIFIER, sizeof(AVL_TREE_IDENTIFIER) - 1);
      std::cout.put('\n');

      Tree::print(strc->node.tree);
   }

   return;

print_all:
   for (StructStack* s = state.stack; s; s = s->next_node) {

      Record* record;
      std::cout << '$' << s->id << " - ";

      if (s->kind == kind_t::LINKED_LIST) {
         std::cout.write(LL_IDENTIFIER, sizeof(LL_IDENTIFIER) - 1);
         record = safe_access(s->node.linked_list, content, nullptr);
      } else {
         if (s->kind == kind_t::TREE) std::cout.write(TREE_IDENTIFIER, sizeof(TREE_IDENTIFIER) - 1);
         else std::cout.write(AVL_TREE_IDENTIFIER, sizeof(AVL_TREE_IDENTIFIER) - 1);
         record = safe_access(s->node.tree, content, nullptr);
      }

      print_record(record, "{$0: $1, $2\n");
   }
}

// match two strings (case sensitevely) and consume the second
// word if it matches
bool JAST::match_consume_word(const char* compare, char*& consume) {

   for (uint64_t i = 0; compare[i] == consume[i]; i++) {
      if (compare[i]) continue;

      consume += i + 1;
      return true;
   }

   return false;
}

// parse a string containing a decimal integer representation
// while consuming the word
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

   consume++;

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