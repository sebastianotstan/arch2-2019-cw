#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <istream>
#include "instructions.hpp"
#include "registers.hpp"
#include "memory.hpp"
using namespace std;

int main(int argc, char *argv[]){
  string binName = argv[1];

  // first input is the name of the binary file

  cerr << binName // see if the correct file is opened

  ifstream binName(binName, ios::in|ios::binary); // initially point at the beginning

  // begin = binStream.tellg();
  binStream.seekg(0, ios::end); // point to the end of the file

  // binStream.seek(seek_end);
  sizeBin = binStream.tellg();

  // create the memory by default constructor
  memory::memory();
  // vector<uint32_t> imem; // create instruction memory
  // imem.resize(0x1000000); // size of imem
  //
  // vector<uint32_t> dmem; // create data memory
  // dmem.resize(0x4000000); // size of dmem
  //
  // imem_offset = 0x10000000;
  // imem_length = 0x1000000;
  //
  // dmem_offset = 0x20000000;
  // dmem_length = 0x1000000;

  binStream.read(&imem[0], sizeBin); // load the bits into imem vector

  int index = 0;
  // while(index != binStream.eof()){
  //
  //   index++;//traverse through the binary file
  // } //adding the bits in the binary file bits by bits

  uint32_t registers[32] = {0}; // create register memory

  uint32_t pc = addr_INSTR; // set the programme counter to imem-offset

  while(1){ // implement the decoding
    char type;
    char instr;
    uint32_t instruction;
    bool validity = addr_in_instr(32, pc)
    if(pc < addr_INSTR){ // invalid address
        // throw exception
    }
    else if(validity){
      instr = memory::form_instr(imem, pc);
      instruction = get_instr(instr);
      //implememnt the decoding after the instruction is found
      // op = (instruction & 0xFC000000) >> 26;
      // if(op == 0x000000){
      //   type = "R_type";
      //   cout type; // confirming instruction type
      //
      //   R_type::correspond_bits();
      //   R_type::detect();
      //
      // }
      // else if(op == 0x000010 || op == 0x000011){
      //   type = "J_type";
      //   cout type;
      //
      //   J_type::correspond_bits();
      //   J_type::detect();
      //
      // }else{
      //   type = "I_type";
      //   cout type;
      //
      //   I_type::correspond_bits();
      //   I_type::detect();
      //
      // }
      type = instruction_type(instruction);
      cout << type << "instruction\n" ;
      cout << "word =" << std::hex << instruction << endl;
      pc += 4;
      Mips_execution(instruction);
    }
    else{
      exit(-1); // If there are no more characters (EOF), the memory read should return -1.
    }
  }



}
