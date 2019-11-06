#include<iostream>
#include "instructions.hpp"
#include "registers.hpp"
#include "exceptions.hpp"
#include<cstdint>
#include<exception>
using namespace std;

uint32_t bits_place_32(uint32_t instructions, int begin, int size){
  uint32_t shift_num = ((1 << size) - 1) << begin;
  uint32_t found_bits = shift_num & instructions;
  return found_bits >> begin;
}

uint64_t bits_place_64(uint64_t instructions, uint64_t begin, uint64_t size){
  uint64_t shift_num = ((1 << size) - 1) << begin;
  uint64_t found_bits = shift_num & instructions;
  return found_bits >> begin;
}

uint32_t sign_extend(uint32_t num, int size){
  int sign_bit = bits_place_32(num, size-1, 1);
  uint32_t result = num;
  for(int i = size; i < 32; i++){
    result = result | (sign_bit << i);
  }
  return result;
}

char instruction_type(uint32_t instructions){
  char type;
  if(instructions >> 25 == 0){
    type = "R";
  }
  else if((instructions >> 25 == 2) || (instructions >> 25 == 3)){
    type = "J"
  }
  else{
    type = "I";
  }
  return type;
}

void Mips_execution(uint32_t instructions){
  char type = instruction_type(instructions);
  if(type == "R"){
    R_type r_ins;
    r_ins.correspond_bits(instructions);
    r_ins.detect();
  }
  else if(type == "I"){
    I_type i_ins;
    i_ins.correspond_bits(instructions);
    i_ins.detect();
  }
  else if(type == "J"){
    J_type j_ins;
    j_ins.correspond_bits(instructions);
    j_ins.detect();
  }
}

void R_type::correspond_bits(uint32_t instructions){
  for(int i = 0; i < 6; i++){
      funct.push_back(instructions_set[5-i]);
      op.push_back(instructions_set[31-i]);
  }
  for(int i = 0; i < 5; i++){
    shamt.push_back(instructions_set[10-i]);
    rd.push_back(instructions_set[15-i]);
    rt.push_back(instructions_set[20-i]);
    rs.push_back(instructions_set[25-i]);
  }
}

void I_type::correspond_bits(uint32_t instructions){
  for(int i = 0; i < 6; i++){
    op.push_back(instructions_set[31-i]);
  }
  for(int i = 0; i < 5; i++){
    rt.push_back(instructions_set[20-i]);
    rs.push_back(instructions_set[25-i]);
  }
  for(int i = 0; i < 16; i++){
    immediate.push_back(instructions_set[15-i]);
  }
}

void J_type::correspond_bits(uint32_t instructions){
  for(int i = 0; i < 6; i++){
    op.push_back(instructions_set[31-i]);
  }
  for(int i = 0; i < 26; i++){
    memory.push_back(instructions_set[25-i]);
  }
}

void R_type::detect(){
  if(funct == 32){
    int result = register_pointer->get_registers(rs) + register_pointer->get_registers(rt);
    bool overflow1 = ((register_pointer->get_registers(rs) < 0) && (register_pointer->get_registers(rt) < 0) && (result >= 0));
    bool overflow2 = ((register_pointer->get_registers(rs) > 0) && (register_pointer->get_registers(rt) > 0) && (result <= 0));
    if(overflow1 || overflow2){
      throw Exception.arithmetic_exception();
    }

    register_pointer->set_registers(rd, result);
  }//ADD overflow
  else if(funct == 33){
    register_pointer->set_registers(rd, (register_pointer->get_registers(rs) + register_pointer->get_registers(rt)));
  }//ADDU
  else if(funct == 36){
    register_pointer->set_registers(rd, (register_pointer->get_registers(rs) & register_pointer->get_registers(rt)));
  }//AND
  else if(funct == 26){
    int a = register_pointer->get_registers(rs);
    int b = register_pointer->get_registers(rt);
    if(b != 0){
      int quotient = a / b;
      int remainder = a % b;
    }
    register_pointer->set_LO(quotient);
    register_pointer->set_HI(remainder);
  }//DIV
  else if(funct == 27){
    uint32_t a = register_pointer->get_registers(rs);
    uint32_t b = register_pointer->get_registers(rt);
    if(b != 0){
      uint32_t quotient = a / b;
      uint32_t remainder = a % b;
    }
    register_pointer->set_LO(quotient);
    register_pointer->set_HI(remainder);
  }//DIVU
  else if(funct == 9){
    int address = register_pointer->get_registers(rs);

    uint32_t return_link = register_pointer->get_address_counter() + 4;
    register_pointer->set_registers(rd, return_link);
  }//JALR delay slot
  else if(funct == 8){
    int address = register_pointer->get_registers(rs);
  }//JR delay slot
  else if(funct == 16){
    register_pointer->set_registers(rd, register_pointer->get_HI());
  }//MFHI
  else if(funct == 18){
    register_pointer->set_registers(rd, register_pointer->get_LO());
  }//MFLO
  else if(funct == 17){
    register_pointer->set_HI(register_pointer->get_registers(rs));
  }//MTHI
  else if(funct == 19){
    register_pointer->set_LO(register_pointer->get_registers(rs));
  }//MTLO
  else if(funct == 24){
    int64_t result = register_pointer->get_registers(rs) * register_pointer->get_registers(rt);
    int low = used_function::bits_place_64(result, 0, 32);
    int high = used_function::bits_place_64(result, 32, 32);
    register_pointer->set_LO(low);
    register_pointer->set_HI(high);
  }//MULT
  else if(funct == 25){
    uint64_t result = register_pointer->get_registers(rs) * register_pointer->get_registers(rt);
    int low = used_function::bits_place_64(result, 0, 32);
    int high = used_function::bits_place_64(result, 32, 32);
    register_pointer->set_LO(low);
    register_pointer->set_HI(high);
  }//MULTU
  else if(funct == 37){
    register_pointer->set_registers(rd, (register_pointer->get_registers(rs) | register_pointer->get_registers(rt)));
  }//OR
  else if(funct == 0){
    register_pointer->set_registers(rd, (register_pointer->get_registers(rt) << shamt));
  }//SLL
  else if(funct == 4){
    register_pointer->set_registers(rd, (register_pointer->get_registers(rt) << used_function::bits_place_32(register_pointer->get_registers(rs), 0, 5)));
  }//SLLV
  else if(funct == 42){
    bool result = register_pointer->get_registers(rs) < register_pointer->get_registers(rt);
    register_pointer->set_registers(rd, result);
  }//SLT
  else if(funct == 43){
    uint32_t a = register_pointer->get_registers(rs);
    uint32_t b = register_pointer->get_registers(rt);
    bool result = a < b;
    register_pointer->set_registers(rd, result);
  }//SLTU
  else if(funct == 3){
    uint32_t result1 = register_pointer->get_registers(rt) >> shamt;
    int result2 = used_function::sign_extend(result1, 32-shamt);
    register_pointer->set_registers(rd,result2);
  }//SRA
  else if(funct == 7){
    int shift_count = used_function::bits_place_32(register_pointer->get_registers(rs), 0, 5);
    uint32_t result1 = register_pointer->get_registers(rt) >> shift_count;
    int result2 = used_function::sign_extend(result1, 32-shift_count);
    register_pointer->set_registers(rd,result2);
  }//SRAV
  else if(funct == 2){
    register_pointer->set_registers(rd, (register_pointer->get_registers(rt) >> shamt));
  }//SRL
  else if(funct == 6){
    register_pointer->set_registers(rd, (register_pointer->get_registers(rt) >> used_function::bits_place_32(register_pointer->get_registers(rs), 0, 5)));
  }//SRLV
  else if(funct == 34){
    int result = register_pointer->get_registers(rs) - register_pointer->get_registers(rt);
    bool overflow1 = ((register_pointer->get_registers(rs) > 0) && (register_pointer->get_registers(rt) < 0) && (result < 0));
    bool overflow2 = ((register_pointer->get_registers(rs) < 0) && (register_pointer->get_registers(rt) > 0) && (result > 0));
    if(overflow1 || overflow2){
      throw Exception.arithmetic_exception();
    }
    register_pointer->set_registers(rd, result);
  }//SUB overflow
  else if(funct == 35){
    register_pointer->set_registers(rd, (register_pointer->get_registers(rs) - register_pointer->get_registers(rt)));
  }//SUBU
  else if(funct == 38){
    register_pointer->set_registers(rd, (register_pointer->get_registers(rs) ^ register_pointer->get_registers(rt)));
  }//XOR
}

void I_type::Branch(){
  int offset = used_function::sign_extend(immediate << 2, 18);
  uint32_t address = register_pointer->get_address_counter() + offset;

}//not finish

void I_type::detect(){
  if(op == 1){
    if(rt == 1){
      if(register_pointer->get_registers(rs) >= 0){
        Branch();
      }
    }//BGEZ
    else if(rt == 17){
      if(register_pointer->get_registers(rs) >= 0){
        Branch();
      }
      register_pointer->set_registers(31, (register_pointer->get_address_counter() + 4));
    }//BGEZAL
    else if(rt == 0){
      if(register_pointer->get_registers(rs) < 0){
        Branch();
      }
    }//BLTZ
    else if(rt == 16){
      if(register_pointer->get_registers(rs) < 0){
        Branch();
      }
      register_pointer->set_registers(31, (register_pointer->get_address_counter() + 4));
    }//BLTZAL
  }
  else if(op == 8){
    int result = register_pointer->get_registers(rs) + used_function::sign_extend(immediate, 16);
    bool overflow1 = ((register_pointer->get_registers(rs) < 0) && (used_function::sign_extend(immediate, 16) < 0) && (result >= 0));
    bool overflow1 = ((register_pointer->get_registers(rs) > 0) && (used_function::sign_extend(immediate, 16) > 0) && (result <= 0));

    if(overflow1 || overflow2){
      throw Exception.arithmetic_exception();
    }

    register_pointer->set_registers(rt, result);
  }//ADDI overflow
  else if(op == 9){
    register_pointer->set_registers(rt, (register_pointer->get_registers(rs) + used_function::sign_extend(immediate, 16)));
  }//ADDIU
  else if(op == 12){
    register_pointer->set_registers(rt, (register_pointer->get_registers(rs) & immediate));
  }//ANDI
  else if(op == 4){
    if(register_pointer->get_registers(rs) == register_pointer->get_registers(rt)){
      Branch();
    }
  }//BEQ
  else if(op == 7){
    if(register_pointer->get_registers(rs) > 0){
      Branch();
    }
  }//BGTZ
  else if(op == 6){
    if(register_pointer->get_registers(rs) <= 0){
      Branch();
    }
  }//BLEZ
  else if(op == 5){
    if(register_pointer->get_registers(rs) != register_pointer->get_registers(rt)){
      Branch();
    }
  }//BNE
  else if(op == 32){

  }//LB
  else if(op == 36){

  }//LBU
  else if(op == 33){

  }//LH
  else if(op == 37){

  }//LHU
  else if(op == 15){
    register_pointer->set_registers(rt, immediate >> 16);
  }//LUI
  else if(op == 35){

  }//LW
  else if(op == 34){

  }//LWL
  else if(op == 38){

  }//LWR
  else if(op == 13){
    register_pointer->set_registers(rd, register_pointer->get_registers() | immediate);
  }//ORI
  else if(op == 40){

  }//SB
  else if(op == 41){

  }//SH
  else if(op == 10){
    int a = used_function::sign_extend(immediate, 16);
    bool result = register_pointer->get_registers(rs) < a;
    register_pointer->set(rt, result);
  }//SLTI
  else if(op == 11){
    uint32_t a = used_function::sign_extend(immediate, 16);
    bool result = register_pointer->get_registers(rs) < a;
    register_pointer->set(rt, result);
  }//SLTIU
  else if(op == 43){

  }//SW
  else if(op == 14){
    register_pointer->set_registers(rt, register_pointer->get_registers(rs) ^ immediate);
  }//XORI
}

void J_type::detect(){
  if(op == 2){

  }//J
  if(op == 3){

  }//JAL
}
