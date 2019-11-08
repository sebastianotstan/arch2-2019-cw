#include "memory.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <stdint.h>
// #include <exceptions.hpp>

// #include "instruction.hpp"

using namespace std;

memory::memory(){
   imem.resize(0x1000000, 0);
   dmem.resize(0x4000000, 0);
}

//size_t fread(void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);
//reading the binary file byte by byte

//loading bytes into the vector(now done in the main)

// void load_instr(vector<char> imem, file  binStream){
//   binStream.seekg(0, ios::end);
//   size = binStream.tellg();
//   char* memblock = new char();
//   binStream.read(memblock, size)
//   int* memaddr = reinterpret_cast<vector<uint32_t>*>(memblock);
//
// }


uint32_t memory::form_instr(uint32_t pc){
  uint32_t bits_7_0 = imem[pc - 0x10000000 + 3];
  uint32_t bits_15_8 = (imem[pc - 0x10000000 + 2] << 8);
  uint32_t bits_23_16 = (imem[pc - 0x10000000 + 1] << 16);
  uint32_t bits_31_24 = (imem[pc - 0x10000000] << 24);
  uint32_t instruction = (bits_31_24 | bits_23_16 | bits_15_8 | bits_7_0);
  return instruction;
}

bool memory::addr_in_instr(int num_bits, int start){
  bool result = true;
  if((num_bits + start) > (memory::addr_INSTR + memory::addr_INSTR_length)){
    result = false;
    return result;
  }
  return result;
}

bool memory::addr_in_data(int num_bits, int start){
  bool result = true;
  if((num_bits + start) > (memory::addr_DATA + memory::addr_DATA_length)){
    result = false;
    return result;
  }
  return result;
}

// uint32_t get_instr(char instruction){
//   uint32_t instr;
//   instr = (uint32_t) instruction;
//   return instr;
// }

// void memory::set_ivector(char* memblock, int size){
//   uint32_t temp;
//   for(int i = 0; i < size/4; i ++){
//     temp = 0;
//     for(int j = 0; j < 4; j++){
//       temp += (unsigned char)memblock[i*4 + 3 - j] << 8*j;
//     }
//     imem[i] = temp;
//   }
// }

uint32_t get_iaddress(int address){
  return imem[address - 0x10000000];
}

void set_iaddress(int address, char value){
   imem[address - 0x10000000] = value;
}

uint32_t get_n_bytes(int address, int n){
  uint32_t result;
  for(int i = 0; i < n; i++){
    result += (imem[address - 0x10000000 - i + n] << (8*i));
  }
  return result;
}

// uint32_t get_instruction(int address){
//   uint32_t instruction;
//   instruction = imem[address -]
// }

void memory::set_ivector(int count, char value){
  imem[count] = value;
  // std::cout << std::hex << imem[count] << endl;
}

// void memory::set_dvector(int count, char value){
//   dmem[count] = value;
// }
