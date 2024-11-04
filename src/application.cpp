#include "application.h"

void JAST::cmd_help(uint64_t argc, char* prompt) {

   get_terminal_dimensions(state.width, state.height);

   byte command = command_t::_help;
   if (argc) command = access_map(COMMANDS, COMMAND_LIST_SIZE, prompt);

   switch (command) {

      case command_t::_help: {
         uint64_t start = 11;

         print_in_column("Lista de todos os comandos:\n\n", 0, state.width);

         print_in_column("chfocus", 3, start);
         print_in_column("Muda a estrutura em foco\n", start, state.width - start);

         print_in_column("create", 3, start);
         print_in_column("Cria um registro e o insere numa estrutura\n", start, state.width - start);

         print_in_column("exit", 3, start);
         print_in_column("Mesmo que `quit`\n", start, state.width - start);

         print_in_column("help", 3, start);
         print_in_column("Mostra essa tela\n", start, state.width - start);

         print_in_column("init", 3, start);
         print_in_column("Mostra a tela de entrada\n", start, state.width - start);

         print_in_column("load", 3, start);
         print_in_column("Carrega dados de um arquivo para alguma estrutura\n", start, state.width - start);

         print_in_column("new", 3, start);
         print_in_column("Cria uma nova estrutura\n", start, state.width - start);

         print_in_column("print", 3, start);
         print_in_column("Imprime estruturas\n", start, state.width - start);

         print_in_column("quit", 3, start);
         print_in_column("Encerra a aplicação\n", start, state.width - start);

         print_in_column("save", 3, start);
         print_in_column("Salva os dados de uma estrutura para algum arquivo\n", start, state.width - start);

         print_in_column("test", 3, start);
         print_in_column("Realisa testes de busca em estruturas\n", start, state.width - start);

         print_in_column("\nDigite `help <comando>` para obter mais informações sobre um comando\n", 0, state.width);
         break;
      }

      case command_t::_chfocus: {
         uint64_t start = 15;

         print_in_column("chfocus $<id>", 0, start);
         print_in_column("Foca a estrutura de id <id>\n", start, state.width - start);

         print_in_column("chfocus remove", 0, start);
         print_in_column("Remove o foco de estrutrura\n", start, state.width - start);

         print_in_column("chfocus", 0, start);
         print_in_column("Mostra a estrutrura em foco\n", start, state.width - start);

         esc::move_to(0);
         break;
      }

      case command_t::_create: {
         uint64_t start = 33;

         print_in_column("create $<id> <key> <data> <name>", 0, start);
         print_in_column("Cria um registro e insere na estrutura de id <id>\n", 0, state.width - start);

         print_in_column("create $<id> random", 0, start);
         print_in_column("Cria um registro aleatório e insere na estrutura de id <id>\n", 0, state.width - start);

         print_in_column("create <key> <data> <name>", 0, start);
         print_in_column("Cria um registro e insere na estrutrura em foco\n", 0, state.width - start);

         print_in_column("create random", 0, start);
         print_in_column("Cria um registro aleatório e insere na estrutura em foco\n", 0, state.width - start);

         esc::move_to(0);
         break;
      }

      case command_t::_init: {
         uint64_t start = 5;

         print_in_column("init", 0, start);
         print_in_column("Mostra a tela de entrada\n", start, state.width - start);

         esc::move_to(0);
         break;
      }

      case command_t::_load: {
         uint64_t start = 25;

         print_in_column("load <struct> <filename>", 0, start);
         print_in_column("Carrega os registros de <filename> para a estrutura em foco\n", start, state.width - start);

         print_in_column("<struct>: tree; avl ou avl_tree; linked_list ou ll\n", 3, state.width - 3);

         esc::move_to(0);
         break;
      }

      case command_t::_new: {
         uint64_t start = 36;

         print_in_column("new <struct>", 0, start);
         print_in_column("Cria uma nova estrutura vazia\n", start, state.width - start);

         print_in_column("new <struct> <count> <rule>", 0, start);
         print_in_column("Cria uma nova estrutura com <count> registros aleatórios\n", start, state.width - start);

         print_in_column("new <struct> <count> <rule> <order>", 0, start);
         print_in_column("Cria uma nova estrutura com <count> registros aleatórios, seguindo uma regra <rule> e chaves em [0, <count> * <order>)\n", start, state.width - start);

         print_in_column("<struct>: tree; avl ou avl_tree; linked_list ou ll\n<rule>: ordered, random, inversed\n", 3, state.width - 3);

         esc::move_to(0);
         break;
      }

      case command_t::_print: {
         uint64_t start = 20;

         print_in_column("print", 0, start);
         print_in_column("Imprime a estrutura em foco, se nenhuma estrutura em foco, imprime o primeiro registro de todas estruturas e seus id's\n", start, state.width - start);

         print_in_column("print <limit>", 0, start);
         print_in_column("Imprime a estrutura em foco, se existir, limitando a profundidade em <limit>\n", start, state.width - start);

         print_in_column("print $<id>", 0, start);
         print_in_column("Imprime a estrutura de id <id>, se existir\n", start, state.width - start);

         print_in_column("print $<id> <limit>", 0, start);
         print_in_column("Imprime a estrutura de id <id>, se existir, limitando a profundidade em <limit>\n", start, state.width - start);

         print_in_column("print all", 0, start);
         print_in_column("imprime o primeiro registro de todas estruturas e seus id's\n", start, state.width - start);

         esc::move_to(0);
         break;
      }

      case command_t::_quit: {
         uint64_t start = 5;

         print_in_column("exit", 0, start);
         print_in_column("Encerra a aplicação\n", start, state.width - start);

         print_in_column("quit", 0, start);
         print_in_column("Encerra a aplicação\n", start, state.width - start);

         esc::move_to(0);
         break;
      }

      case command_t::_save: {
         uint64_t start = 22;

         print_in_column("save <filename>", 0, start);
         print_in_column("Salva os registros da estrutura em foco no arquivo <filename>\n", start, state.width - start);

         print_in_column("save $<id> <filename>", 0, start);
         print_in_column("Salva os registros da estrutura de id <id> no arquivo <filename>\n", start, state.width - start);

         esc::move_to(0);
         break;
      }

      case command_t::_test: {
         uint64_t start = 25;

         print_in_column("test $<id> <sample_size>", 0, start);
         print_in_column("Realiza testes <sample_size> de busca na estrutura de id <id>\n", start, state.width - start);

         print_in_column("test <sample_size>", 0, start);
         print_in_column("Realiza testes <sample_size> de busca na estrutura em foco\n", start, state.width - start);

         esc::move_to(0);
         break;
      }

      default: {
         print_in_column(COMMAND_NOT_FOUND, 0, state.width);
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
   lines += print_in_column(AUTHORS_NAMES, little_chick_width + 3, state.width - (little_chick_width + 3));

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

      case command_t::_chfocus: cmd_chfocus(argc - 1, prompt); break;
      case command_t::_create: return cmd_create(argc - 1, prompt);

      case command_t::_init: init(); break;

      case command_t::_help: cmd_help(argc - 1, prompt); break;
      case command_t::_new: return cmd_new(argc - 1, prompt);
      case command_t::_load: return cmd_load(argc - 1, prompt);

      case command_t::_print: cmd_print(argc - 1, prompt); break;

      case command_t::_quit:

         while (true) {
            std::cout.write(CONFIRM_EXIT, sizeof(CONFIRM_EXIT) - 1);

            char answer = std::cin.get();
            std::cin.ignore(64, '\n');

            if (answer == 's') return exit_t::EXIT_APPLICATION;
            if (answer == 'n') break;
         }

         break;

      case command_t::_save: return cmd_save(argc - 1, prompt);
      case command_t::_test: cmd_test(argc - 1, prompt); break;

      case NOT_FOUND:
         std::cout.write(COMMAND_NOT_FOUND, sizeof(COMMAND_NOT_FOUND) - 1);
         break;
   }

   return exit_t::SUCCESS;
}

exit_t JAST::cmd_test(uint64_t argc, char* prompt) {

   get_terminal_dimensions(state.width, state.height);

   // Identifies whether the supplied args are enough
   if (!argc || (prompt[0] == '$' && argc == 1)) {
      print_in_column(NOT_ENOUGH_ARGS, 0, state.width);
      return exit_t::SUCCESS;
   }

   StructStack* structure;

   if (prompt[0] == '$') {

      // Tries to load an id and find its structure
      structure = find_structure(__aut_str_to_int(++prompt));

      // If not found, quits
      if (!structure) {
         std::cout.write(STRUCT_NOT_FOUND, sizeof(STRUCT_NOT_FOUND) - 1);
         return exit_t::SUCCESS;
      }

   // If an id was not supplies verifies whether there's a focused structure
   } else if (!state.focused) {

      std::cout.write(NO_STRUCT_FOCUS, sizeof(NO_STRUCT_FOCUS) - 1);
      return exit_t::SUCCESS;

   } else structure = state.focused;

   // Load the sample size
   uint64_t sample_size = __aut_str_to_int(prompt);
   if (sample_size < 2) {
      esc::color(esc::CYAN, esc::FOREGROUND);
      print_in_column("Amostra muito pequena!\n", 0, state.width);
      esc::reset();

      return exit_t::SUCCESS;
   }

   struct {
      struct {
         // The mean and variance won't actually be calculated
         // in this variables, they're just helpers
         uint64_t mean, variance;
         uint64_t comparisons;
         uint64_t count;
      } in, out;
   } sample = {
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 }
   };

   // Store the min and max keys, will use them to generate key in the range of the tree
   Record::key_t min_key = 0, max_key = 1; // No need for initalization, compiler's being mean

   Record::key_t* sample_keys = Stack::allocate<Record::key_t>(2 * sample_size);
   if (!sample_keys) return exit_t::BAD_ALLOCATION;

   std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

   switch (structure->kind) {

      case kind_t::LINKED_LIST: {

         if (!structure->node.linked_list) {
            print_in_column(WARNING_EMPTY_STRUCT, 0, state.width);

            Stack::release(sample_keys);
            return exit_t::SUCCESS;
         }

         min_key = structure->node.linked_list->content->key;
         max_key = structure->node.linked_list->content->key;

         LinkedList::Node* current = structure->node.linked_list->next_node;
         while (current) {

            if (false);
            else if (current->content->key < min_key)
               min_key = current->content->key;
            else if (current->content->key > max_key)
               max_key = current->content->key;

            current = current->next_node;
         }

         // The ranged random function is upper exclusive
         max_key++;

      } break;

      case kind_t::AVL_TREE:
      case kind_t::TREE: {

         Tree::Node* current = structure->node.tree;

         if (current) {
            while (current->left_child)
               current = current->left_child;
            min_key = current->content->key;

            current = structure->node.tree;

            while (current->rght_child)
               current = current->rght_child;

            // The ranged random function is upper exclusive
            max_key = current->content->key + 1;
         } else {
            print_in_column(WARNING_EMPTY_STRUCT, 0, state.width);

            Stack::release(sample_keys);
            return exit_t::SUCCESS;
         }

      } break;
   }

   // Execute a limited hard-fixed amount of times, to avoid undecidability
   for (
      uint64_t iteration_limit = ITERATION_LIMIT * sample_size;
      sample.in.count < sample_size || sample.out.count < sample_size;
      iteration_limit--) {

   loop_again:
      if (iteration_limit <= 0) {
         print_in_column(NOT_ENOUGH_KEYS, 0, state.width);

         Stack::release(sample_keys);
         return exit_t::SUCCESS;
      }

      // Generates a random key in range, doesn't actully check if it
      // hasn't already been generated
      Record::key_t key = Random::rand(min_key, max_key);
      Record* record = nullptr;

      uint64_t comparisons = 0;

      // Checks whether the key has already been generated
      uint64_t i = 0;
      for (; i < sample.in.count + sample.out.count; i++) {
         if (key != sample_keys[i]) continue;

         iteration_limit--;
         goto loop_again;
      }

      sample_keys[i] = key;

      // The time marking operation is common to both and could be put in
      // evidence, however, since we're marking, every (micro)second counts
      switch (structure->kind) {

         case kind_t::LINKED_LIST: {

            // Mark the start
            start = std::chrono::high_resolution_clock::now();

            // Search for the key
            record = LinkedList::search(structure->node.linked_list, key);

            // Mark the end
            end = std::chrono::high_resolution_clock::now();
            
            // Search again, this time counting comparisons
            LinkedList::search_c(structure->node.linked_list, key, comparisons);

         } break;

         case kind_t::AVL_TREE:
         case kind_t::TREE: {

            // Mark the start
            start = std::chrono::high_resolution_clock::now();

            // Search for the key
            record = Tree::search(structure->node.tree, key);

            // Mark the end
            end = std::chrono::high_resolution_clock::now();

            // Search again, this time counting comparisons
            Tree::search_c(structure->node.tree, key, comparisons);

         } break;
      }

      using time_order = std::chrono::microseconds;
      uint64_t span = std::chrono::duration_cast<time_order>(end - start).count();

      // If the key has been found, count as in, if not, count as out
      if (record) {
         if (sample.in.count < sample_size) {
            sample.in.comparisons += comparisons;
            sample.in.variance += span * span;
            sample.in.mean += span;
            sample.in.count++;
         }
      } else {
         if (sample.out.count < sample_size) {
            sample.out.comparisons += comparisons;
            sample.out.variance += span * span;
            sample.out.mean += span;
            sample.out.count++;
         }
      }
   }

   double mean_out = (double)sample.out.mean / (double)sample_size;
   double mean_in = (double)sample.in.mean / (double)sample_size;

   double sd_out = sqrt(((double)sample.out.variance - mean_out * mean_out) / (double)(sample_size - 1));
   double sd_in = sqrt(((double)sample.in.variance - mean_in * mean_in) / (double)(sample_size - 1));

   std::cout << "Teste de " << sample_size << " chaves\n";

   // std::cout.put('\n');
   // std::cout << sample_keys[0];
   // for (uint64_t i = 0; i < 2 * sample_size; i++)
   //    std::cout << ", " << sample_keys[i];

   // Present keys
   std::cout.write("\nChaves presentes:\n", 19);
   std::cout << "   Número médio de comparações: " << ((double)sample.in.comparisons / (double)sample_size) << '\n';
   std::cout << "   Tempo médio: " << mean_in << " microssegundos\n";
   std::cout << "   Desvio padrão: " << sd_in << " microssegundos\n";

   // Non-existing keys
   std::cout.write("\nChaves inexistentes:\n", 22);
   std::cout << "   Número médio de comparações: " << ((double)sample.out.comparisons / (double)sample_size) << '\n';
   std::cout << "   Tempo médio: " << mean_out << " microssegundos\n";
   std::cout << "   Desvio padrão: " << sd_out << " microssegundos\n";

   Stack::release(sample_keys);
   return exit_t::SUCCESS;
}

void JAST::cmd_chfocus(uint64_t argc, char* prompt) {
   if (!argc) {

      if (!state.focused) {
         std::cout.write(NO_STRUCT_FOCUS, sizeof(NO_STRUCT_FOCUS) - 1);
         return;
      }

      Record* record;
      std::cout << '$' << state.focused->id << " - ";

      if (state.focused->kind == kind_t::LINKED_LIST) {
         std::cout.write(LL_IDENTIFIER, sizeof(LL_IDENTIFIER) - 1);
         record = safe_access(state.focused->node.linked_list, content, nullptr);
      } else {
         if (state.focused->kind == kind_t::TREE) std::cout.write(TREE_IDENTIFIER, sizeof(TREE_IDENTIFIER) - 1);
         else std::cout.write(AVL_TREE_IDENTIFIER, sizeof(AVL_TREE_IDENTIFIER) - 1);
         record = safe_access(state.focused->node.tree, content, nullptr);
      }

      print_record(record, "{$0: $1, $2\n");
      return;
   }

   if (prompt[0] == '$') {
      state.focused = find_structure(__aut_str_to_int(++prompt));
      if (!state.focused) {
         std::cout.write(STRUCT_NOT_FOUND, sizeof(STRUCT_NOT_FOUND) - 1);
      }

      return;
   }

   if (__aut_match_word("remove", prompt)) {
      state.focused = nullptr;
      return;
   }

   std::cout.write(INVALID_INPUT, sizeof(INVALID_INPUT) - 1);
}

exit_t JAST::cmd_create(uint64_t argc, char* prompt) {

   if (argc) {

      StructStack* structure;

      if (prompt[0] == '$') {
         structure = find_structure(__aut_str_to_int(++prompt));
         argc--;

         if (!structure) {
            std::cout.write(STRUCT_NOT_FOUND, sizeof(STRUCT_NOT_FOUND) - 1);
            return exit_t::SUCCESS;
         }

      } else if (!state.focused) {

         std::cout.write(NO_STRUCT_FOCUS, sizeof(NO_STRUCT_FOCUS) - 1);
         return exit_t::SUCCESS;

      } else structure = state.focused;

      Record* record = new (std::nothrow) Record;
      if (!record) return exit_t::BAD_ALLOCATION;

      // Check whether the record should be random
      if (!__aut_match_word("random", prompt)) {

         if (argc < 3) goto invalid_input;

         record->key = __aut_str_to_int(prompt);
         int data = __aut_str_to_int(prompt);
         write_record(record, data, prompt);

         exit_t response = exit_t::SUCCESS;

         switch (structure->kind) {
            case LINKED_LIST: response = LinkedList::insert(&structure->node.linked_list, record); break;
            case AVL_TREE: response = Tree::AVL::insert(&structure->node.tree, record); break;
            case TREE: response = Tree::insert(&structure->node.tree, record); break;
         }

         if (response == exit_t::BAD_ALLOCATION) {
            delete record;
            return exit_t::BAD_ALLOCATION;
         }

         if (response == exit_t::KEY_ALREADY_EXISTS) {
            esc::color(esc::BRIGHT_RED, esc::FOREGROUND);
            std::cout << "A chave " << record->key << " já existe!\n";
            esc::reset();

            delete record;
         }

         return exit_t::SUCCESS;
      }

      // Populate randomly and search for a valid key up to 64 times
      populate_record_randomly(record);

      // The loop must execute at least once
      exit_t response = exit_t::KEY_ALREADY_EXISTS;

      for (uint64_t i = 0; response == exit_t::KEY_ALREADY_EXISTS; i++) {

         if (i >= ITERATION_LIMIT) {
            esc::color(esc::BLUE, esc::FOREGROUND);
            std::cout.write("Uma nova chave única não foi encontrada!\n", 43);
            esc::reset();

            return exit_t::SUCCESS;
         }

         record->key = Record::key_t(Random::rand() & 0xFFFFF);

         switch (structure->kind) {
            case LINKED_LIST: response = LinkedList::insert(&structure->node.linked_list, record); break;
            case AVL_TREE: response = Tree::AVL::insert(&structure->node.tree, record); break;
            case TREE: response = Tree::insert(&structure->node.tree, record); break;
         }

         if (response == exit_t::BAD_ALLOCATION) {
            delete record;
            return exit_t::BAD_ALLOCATION;
         }
      }

      return exit_t::SUCCESS;
   }

invalid_input:
   std::cout.write(INVALID_INPUT, sizeof(INVALID_INPUT) - 1);
   return exit_t::SUCCESS;
}

exit_t JAST::cmd_load(uint64_t argc, char* prompt) {

   if (argc >= 2) {

      RecordFile::File rc_file;
      byte kind = access_map(STRUCTURES, STRUCTURE_LIST_SIZE, prompt);
      if (kind == NOT_FOUND) goto invalid_input;

      // Try to load the file
      RecordFile::exit_t response = RecordFile::open(prompt, &rc_file, RecordFile::READ);

      if (response == RecordFile::BAD) {
         std::cout.write(FILE_OPENING_ERROR, sizeof(FILE_OPENING_ERROR) - 1);
         return exit_t::SUCCESS;
      }

      if (response == RecordFile::EMPTY) {
         esc::color(esc::BLUE, esc::FOREGROUND);
         std::cout.write("O arquivo fornecido está vazio\n", 32);
         esc::reset();

         RecordFile::close(&rc_file);
         return exit_t::SUCCESS;
      }

      id_t next_id = state.stack ? state.stack->id + 1 : 0;
      StructStack* structure = new (std::nothrow) StructStack{ next_id, kind_t(kind), nullptr, state.stack };
      if (!structure) {
         RecordFile::close(&rc_file);
         return exit_t::BAD_ALLOCATION;
      }

      state.stack = structure;
      bool not_complete = true;

      while (not_complete) {
         Record* record = new (std::nothrow) Record;
         if (!record) {
            RecordFile::close(&rc_file);
            return exit_t::BAD_ALLOCATION;
         }

         not_complete = RecordFile::read(&rc_file, record);
         exit_t response = exit_t::SUCCESS;

         switch (structure->kind) {
            case LINKED_LIST: response = LinkedList::insert(&structure->node.linked_list, record); break;
            case AVL_TREE: response = Tree::AVL::insert(&structure->node.tree, record); break;
            case TREE: response = Tree::insert(&structure->node.tree, record); break;
         }

         if (response == exit_t::BAD_ALLOCATION) {
            delete record;
            return exit_t::BAD_ALLOCATION;
         }

         if (response == exit_t::KEY_ALREADY_EXISTS) {
            delete record;
         }
      }

      RecordFile::close(&rc_file);
      return exit_t::SUCCESS;
   }

invalid_input:
   std::cout.write(INVALID_INPUT, sizeof(INVALID_INPUT) - 1);
   return exit_t::SUCCESS;
}

exit_t JAST::cmd_new(uint64_t argc, char* prompt) {

   if (argc) {

      kind_t structure = (kind_t)access_map(STRUCTURES, STRUCTURE_LIST_SIZE, prompt);
      if (structure == NOT_FOUND) goto not_enough_args;

      id_t next_id = state.stack ? state.stack->id + 1 : 0;

      StructStack* new_structure = new (std::nothrow) StructStack{ next_id, structure, nullptr, state.stack };
      if (!new_structure) return exit_t::BAD_ALLOCATION;
      state.stack = new_structure;

      if (argc < 3) return exit_t::SUCCESS;

      uint64_t n_of_records = __aut_str_to_int(prompt);
      if (!n_of_records) return exit_t::SUCCESS;

      rule_t rule = (rule_t)access_map(RULES, RULE_LIST_SIZE, prompt);

      uint64_t order = (argc >= 4) ? __aut_str_to_int(prompt) : 1;
      if (order < 1) order = 1;

      uint64_t max_key = order * n_of_records;

      BitTools::mword* helper = BitTools::initialize(
         Stack::allocate<BitTools::mword>(BitTools::size(max_key)),
         max_key
      );

      if (!helper) return exit_t::BAD_ALLOCATION;

      uint64_t key = (rule == _inversed) ? max_key - order : 0;

      for (uint64_t i = 0; i < n_of_records; i++) {

         Record* record = new (std::nothrow) Record;
         if (!record) {
            Stack::release(helper);
            return exit_t::BAD_ALLOCATION;
         }

         switch (rule) {

            case _random:
               key = uint64_t(Random::rand() % max_key);

               while (BitTools::getbit(helper, key))
                  if (++key >= max_key) key = 0;

               BitTools::flipbit(helper, key);
               record->key = key;
               break;

            case _ordered:
               record->key = key - uint64_t(Random::rand() % order);
               key += order;
               break;

            case _inversed:
               record->key = key + uint64_t(Random::rand() % order);
               key -= order;
               break;
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

      Stack::release(helper);
      return exit_t::SUCCESS;
   }

not_enough_args:
   std::cout.write(NOT_ENOUGH_ARGS, sizeof(NOT_ENOUGH_ARGS) - 1);
   return exit_t::SUCCESS;
}

void JAST::cmd_print(uint64_t argc, char* prompt) {

   StructStack* structure;
   int64_t level = -1;

   if (!argc) {

      if (!state.focused) goto print_all;

      structure = state.focused;
      goto print_specific;

   } else switch (prompt[0]) {

      case '$':
         structure = find_structure(__aut_str_to_int(++prompt));
         if (!structure) {
            std::cout.write(STRUCT_NOT_FOUND, sizeof(STRUCT_NOT_FOUND) - 1);
            return;
         } else {
            if (argc > 1) level = __aut_str_to_int(prompt);
            goto print_specific;
         }

      case 'a':
         if (__aut_match_word("all", prompt)) goto print_all;

      default:
         level = __aut_str_to_int(prompt);
         if (!state.focused) {
            std::cout.write(INVALID_INPUT, sizeof(INVALID_INPUT) - 1);
            return;
         }

         structure = state.focused;
         goto print_specific;
   }

print_specific:
   if (structure->kind == kind_t::LINKED_LIST) {
      std::cout.write(LL_IDENTIFIER, sizeof(LL_IDENTIFIER) - 1);
      std::cout.put('\n');

      LinkedList::print(structure->node.linked_list, level);

   } else {
      if (structure->kind == kind_t::TREE) std::cout.write(TREE_IDENTIFIER, sizeof(TREE_IDENTIFIER) - 1);
      else std::cout.write(AVL_TREE_IDENTIFIER, sizeof(AVL_TREE_IDENTIFIER) - 1);
      std::cout.put('\n');

      Tree::print(structure->node.tree, level);
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

exit_t JAST::cmd_save(uint64_t argc, char* prompt) {

   if (!argc && argc > 2) goto not_enough_args;

   RecordFile::File rc_file;
   StructStack* structure;

   // One args, so it's gonna be just a filename, verifies whether there's
   // a focused structure
   if (argc == 1) {

      if (!state.focused) {
         std::cout.write(NO_STRUCT_FOCUS, sizeof(NO_STRUCT_FOCUS) - 1);
         return exit_t::SUCCESS;
      }

      structure = state.focused;

   // Has two args, first one must be an id, second a filename
   } else if (prompt[0] == '$') {

      structure = find_structure(__aut_str_to_int(++prompt));
      if (!structure) {
         std::cout.write(STRUCT_NOT_FOUND, sizeof(STRUCT_NOT_FOUND) - 1);
         return exit_t::SUCCESS;
      }

   } else goto not_enough_args;

   // Try to load the file
   if (RecordFile::open(prompt, &rc_file, RecordFile::WRITE) == RecordFile::BAD) {
      std::cout.write(FILE_OPENING_ERROR, sizeof(FILE_OPENING_ERROR) - 1);
      return exit_t::SUCCESS;
   }

   switch (structure->kind) {

      case kind_t::TREE:
      case kind_t::AVL_TREE: {

         Tree::Node* node = structure->node.tree;

         if (!node) break;

         Tree::Node** stack = nullptr;
         if (node->height) {
            stack = Stack::allocate<Tree::Node*>(node->height);
            if (!stack) return exit_t::BAD_ALLOCATION;
         }

         int64_t top = -1;

         while (true) {

            if (node->left_child) stack[++top] = node->left_child;
            if (node->rght_child) stack[++top] = node->rght_child;

            RecordFile::write(&rc_file, node->content, top >= 0);

            if (top < 0) break;
            node = stack[top--];
         }

         Stack::release(stack);
      } break;

      case kind_t::LINKED_LIST: {

         LinkedList::Node* node = structure->node.linked_list;

         while (node) {
            RecordFile::write(&rc_file, node->content, bool(node->next_node));
            node = node->next_node;
         }

      } break;
   }

   RecordFile::close(&rc_file);
   return exit_t::SUCCESS;

not_enough_args:
   std::cout.write(NOT_ENOUGH_ARGS, sizeof(NOT_ENOUGH_ARGS) - 1);
   return exit_t::SUCCESS;
}

// match two strings (case sensitevely) and consume the second word if it matches
bool JAST::__aut_match_word(const char* compare, char*& consume) {

   for (uint64_t i = 0; compare[i] == consume[i]; i++) {
      if (compare[i]) continue;

      consume += i + 1;
      return true;
   }

   return false;
}

// parse a string containing a decimal integer representation while consuming the word
uint64_t JAST::__aut_str_to_int(char*& consume) {
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
      if (__aut_match_word(map[index].alias, prompt)) return map[index].command;

   return NOT_FOUND;
}

uint64_t JAST::print_in_column(const char* text, word start, word width) {
   esc::move_to(start);

   uint64_t lines = 0, index = 0, length = 0;
   while (true) {

      switch (text[index]) {
         case '\0':
            if (index > 0) {
               std::cout.write(text, index);
               lines++;
            }

            return lines;

         case '\n':
            if (index > 0) {
               std::cout.write(text, ++index);
               text += index;

               length = 0;
               index = 0;
            } else {
               std::cout.put('\n');
               text++;
            }

            esc::move_to(start);
            lines++;

            continue;

         case ' ':
            length = index;
            break;
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