#include<cstdint>
#include<string>
#include "registers.hpp"

uint32_t bits_place_32(uint32_t instructions, int begin, int size);
uint64_t bits_place_64(uint64_t instructions, uint64_t begin, uint64_t size);
uint32_t sign_extend(uint32_t num, int size);
char instruction_type(uint32_t instructions);

class Mips_execution{
  registers *register_pointer;
  memory *memory_pointer;
  branch_delay *branch_pointer;
public:
  void execution(uint32_t instructions);
  int instr_num;
  branch_delay Delay;
  Mips_execution(registers *register_pointer, memory *memory_pointer, branch_delay *branch_pointer);
};

struct branch_delay{
  int if_branch = 0;
  uint32_t address;
};

struct R_type{
  uint32_t op;//6 bits
  uint32_t rs;//5 bits
  uint32_t rt;//5 bits
  uint32_t rd;//5 bits
  uint32_t shamt;//5 bits
  uint32_t funct;//6 bits
  registers *register_pointer;
  memory *memory_pointer;
  Mips_execution *execute_pointer;

  void detect();
  void correspond_bits(uint32_t instructions, registers *register_pointer, memory *memory_pointer, Mips_execution *execute_pointer);
};

struct I_type{
  uint32_t op;//6 bits
  uint32_t rs;//5 bits
  uint32_t rt;//5 bits
  uint32_t immediate;//16 bits
  registers *register_pointer;
  memory *memory_pointer;
  Mips_execution *execute_pointer;

  void detect();
  void Branch();
  void correspond_bits(uint32_t instructions, registers *register_pointer, memory *memory_pointer, Mips_execution *execute_pointer);
};

struct J_type{
  uint32_t op;//6 bits
  uint32_t memory;//26 bits
  registers *register_pointer;
  memory *memory_pointer;
  Mips_execution *execute_pointer;

  void detect();
  void correspond_bits(uint32_t instructions, registers *register_pointer, memory *memory_pointer, Mips_execution *execute_pointer);
};
