#include<cstdint>
#include<string>
#include "registers.hpp"

uint32_t bits_place_32(uint32_t instructions, int begin, int size);
uint64_t bits_place_64(uint64_t instructions, uint64_t begin, uint64_t size);
uint32_t sign_extend(uint32_t num, int size);
char instruction_type(uint32_t instructions);
void Mips_execution(uint32_t instructions)


struct R_type{
  uint32_t op;//6 bits
  uint32_t rs;//5 bits
  uint32_t rt;//5 bits
  uint32_t rd;//5 bits
  uint32_t shamt;//5 bits
  uint32_t funct;//6 bits
  registers *register_pointer;

  void detect();
  void correspond_bits(uint32_t instructions);
};

struct I_type{
  uint32_t op;//6 bits
  uint32_t rs;//5 bits
  uint32_t rt;//5 bits
  uint32_t immediate;//16 bits
  registers *register_pointer;

  void detect();
  void Branch();
  void correspond_bits(uint32_t instructions);
};

struct J_type{
  uint32_t op;//6 bits
  uint32_t memory;//26 bits
  registers *register_pointer;

  void detect();
  void correspond_bits(uint32_t instructions);
};
