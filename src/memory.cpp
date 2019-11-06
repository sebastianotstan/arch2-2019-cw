#include "memory.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <exceptions.hpp>

using namespace std;

memory::memory(){

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

char form_instr(vector<char> imem, int pc){
  char bits_7_0 = imem[pc + 3];
  char bits_15_8 = (imem[pc + 2] << 8);
  char bits_23_16 = (imem[pc + 2] << 16);
  char bits_31_24 = (imem[pc] << 24);
  char instruction = (bits_31_24 | bits_23_16 | bits_15_8 | bits_7_0);
  return instruction;
}

bool addr_in_instr(int num_bits, int start){
  bool result = true;
  if((num_bits + start) > (memory::addr_INSTR + memory::addr_INSTR_length)){
    result = false;
    return result;
  }
  return result;
}

bool addr_in_data(int num_bits, int start){
  bool result = true;
  if((num_bits + start) > (memory::addr_DATA + memory::addr_DATA_length)){
    result = false;
    return result;
  }
  return result;
}

uint32_t get_instr(char instruction){
  uint32_t instr;
  instr = (uint32_t) instruction;
  return instr;
}


int main(){
  memory::memory();
  cout << "memory is created." << endl;

}
