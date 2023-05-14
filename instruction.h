#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "./types.h"
#include "util.h"

typedef struct Instruction {
  u8 encoding;
  u8 mcycle;
  void (*execute)(EmulationState *);
} Instruction;

#define GB_INSTRUCTIONS_LENGTH 116

extern Instruction GB_INSTRUCTIONS[GB_INSTRUCTIONS_LENGTH];

#endif // INSTRUCTION_H
