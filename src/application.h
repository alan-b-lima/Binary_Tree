#pragma once

#include "base.h"
#include "system.h"

#include "../rc/strings.cpp"

#include "../lib/terminal.h"
#include "../lib/color.h"
#include "../lib/stack.h"

#include "linked_list.h"
#include "tree.h"
#include "file.h"

// Just Another Shell for testing sTructures
namespace JAST {

   enum kind_t : byte { LINKED_LIST, TREE, AVL_TREE };
   enum command_t : byte { _chfocus, _create, _help, _init, _load, _new, _print, _quit, _save, _test };
   enum rule_t : byte { _random, _ordered, _inversed };

   const byte NOT_FOUND = -1;

   typedef long id_t;

   typedef struct StructStack {
      id_t id;
      kind_t kind;

      union {
         LinkedList::Node* linked_list;
         Tree::Node* tree;
      } node;

      StructStack* next_node;
   } StructStack;

   template <uint64_t str_size>
   struct Map {
      const char alias[str_size];
      byte command;
   };

   static struct State {
      StructStack* stack;
      StructStack* focused;
      word width, height;
   } state = { nullptr, nullptr, 0, 0 };

   Map<8> COMMANDS[] = {
      "chfocus", _chfocus,
      "create",  _create,
      "exit",    _quit,
      "help",    _help,
      "init",    _init,
      "load",    _load,
      "new",     _new,
      "print",   _print,
      "quit",    _quit,
      "save",    _save,
      "test",    _test,
   };

   Map<12> STRUCTURES[] = {
      "avl",         AVL_TREE,
      "avl_tree",    AVL_TREE,
      "linked_list", LINKED_LIST,
      "ll",          LINKED_LIST,
      "tree",        TREE,
   };

   Map<9> RULES[] = {
      "i",        _inversed,
      "inv",      _inversed,
      "inversed", _inversed,
      "o",        _ordered,
      "ord",      _ordered,
      "ordered",  _ordered,
      "r",        _random,
      "rand",     _random,
      "random",   _random,
   };

   const uint64_t COMMAND_LIST_SIZE = sizeof(COMMANDS) / sizeof(COMMANDS[0]);
   const uint64_t STRUCTURE_LIST_SIZE = sizeof(STRUCTURES) / sizeof(STRUCTURES[0]);
   const uint64_t RULE_LIST_SIZE = sizeof(RULES) / sizeof(RULES[0]);

   const uint64_t ITERATION_LIMIT = 64;
   
   // Functionalities

   uint64_t process_args(char* prompt) {

      char* cursor = prompt;
      bool read = false;

      uint64_t argc = 0;
      uint64_t i;

      for (i = 0; prompt[i] == ' '; i++)
         if (!prompt[i]) return 0;

   normal:
      switch (prompt[i]) {
         case '\0': *cursor = '\0'; if (read) argc++; return argc;
         case '"': read = false; i++; goto quoted;
         case ' ': if (read) argc++; read = false; *cursor++ = '\0'; i++; goto space;
         default: read = true; *cursor++ = prompt[i++]; goto normal;
      }

   space:
      switch (prompt[i]) {
         case '\0': return argc;
         case ' ': i++; goto space;
         default: goto normal;
      }

   quoted:
      switch (prompt[i]) {
         case '\0': *cursor = '\0'; if (read) argc++; return argc;
         case '"': if (!read) cursor--; i++; goto normal;
         default: read = true; *cursor++ = prompt[i++]; goto quoted;
      }
   }

   StructStack* find_structure(id_t id) {
      for (StructStack* s = state.stack; s; s = s->next_node)
         if (id == s->id) return s;

      return nullptr;
   }

   template <uint64_t str_size>
   byte access_map(Map<str_size>*, uint64_t, char*&);
   
   // __aut for finite automaton, they will consume the prompt
   bool __aut_match_word(const char*, char*&);
   uint64_t __aut_str_to_int(char*&);

   uint64_t print_in_column(const char*, word, word);

   // Commands

   void init();
   void cmd_help(uint64_t, char*);

   exit_t cmd_create(uint64_t, char*);
   exit_t cmd_load(uint64_t, char*);
   exit_t cmd_new(uint64_t, char*);
   exit_t cmd_save(uint64_t, char*);
   exit_t cmd_test(uint64_t, char*);
   
   void cmd_chfocus(uint64_t, char*);
   void cmd_print(uint64_t, char*);

   // The interpreter
   exit_t interpreter(char* prompt);

   void finish() {
      while (state.stack) {
         switch (state.stack->kind) {
            case kind_t::LINKED_LIST:
               LinkedList::destruct(&state.stack->node.linked_list, destruct_record);
               break;

            case kind_t::AVL_TREE:
            case kind_t::TREE:
               Tree::destruct(&state.stack->node.tree, destruct_record);
               break;
         }

         StructStack* next_node = state.stack->next_node;
         delete state.stack;
         
         state.stack = next_node;
      }
   }
};