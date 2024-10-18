#pragma once

#include "base.h"
#include "../rc/names.cpp"

typedef int32_t key_t;
static const uint64_t NAME_SIZE = 1000;

typedef struct Record {
   key_t key;
   int   data;
   char  name[NAME_SIZE + 1];
} Record;

void write_record(Record*, int, const char*);
void print_record(Record*, const char* = "{$0, $1, $2}");

void populate_record_randomly(Record*);
void destruct_record(Record*);

#include "record.cpp"