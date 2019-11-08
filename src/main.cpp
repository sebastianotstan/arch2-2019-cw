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
#include "exceptions.hpp"
using namespace std;

int main(){
  memory mem;

  cout << "memory is created." << endl;

  string binName = "assebly.mips.bin";
  // first input is the name of the binary file

  cout << binName << endl; // see if the correct file is opened

  ifstream binStream(binName, ios::in | ios::binary | ios::ate); // initially point at the beginning

  // begin = binStream.tellg();
  // binStream.seek(seek_end);
  streampos sizeBin;


  // char* memblock;

  char value;

  int count = 0;

  if(binStream.is_open()){

    sizeBin = binStream.tellg();
    // memblock = new char[sizeBin];

    binStream.seekg(0, ios::beg);

    // binStream.read(memblock, sizeBin);
    //
    // cout << sizeBin << endl;

    while(!binStream.eof()){
      binStream.get(value);
      cout << hex << value << endl;
      mem.set_ivector(count, value);
      count++;
    }

    binStream.close();
  }else{
    cout << "unable to open" << endl;
    return(-1);
  }
  // char byte;

  // vector<uint8_t> bin_in;
  // bin_in.resize(sizeBin, 0);
  //
  // binStream.read((char*) (&bin_in[0], sizeBin);
  //
  // cout << "size of imem is " << bin_in.size() << endl;
  //
  // for(int i = 0; i < bin_in.size() << i++){
  //   cout << bitset<8> (bin_in[i]) << endl;
  // }

  // while(!binStream.eof()){
  //   value = binStream.get();
  //
  //   count++;
  // }

  // cout << &memblock << endl;

  // int count = 0;

  // memory::set_ivector(memblock, int(sizeBin));



  // while(!binStream.eof()){
  //   value = binStream.get();
  //   cout << value << endl;
  //   memory::set_ivector(count, value);
  //   count++;
  // }

  //
  uint32_t pc = mem.addr_INSTR; // set the programme counter to imem-offset
  cout << pc << endl;
  //
  // // cout << mem.imem[0] << endl;
  //
  while(pc < (0x10000000 + 12)){ // implement the decoding
    // char type;
    char instr;
    uint32_t instruction;
    bool validity = mem.addr_in_instr(32, pc);
    if(pc < mem.addr_INSTR){ // invalid address
        // throw exception
    }
    else if(validity){
      // cout << validity << endl;
      // instruction = mem.form_instr(pc);
      // cout << instruction << endl;
      // // instruction = get_instr(instr);
      // //implememnt the decoding after the instruction is found
      // uint32_t op = (instruction) >> 26;
      // if(op == 0x000000){
      //   cout << "R_type" << endl;
      //
      // }
      // else if(op == 0x000010 || op == 0x000011){
      //   cout << "J_type" << endl;
      //
      // }else{
      //   cout << "I_type" << endl;
      //
      // }
      cout << "instruction is" << instruction << endl;
      pc += 4;
      // Mips_execution(instruction);
    }
    else{
      exit(-1); // If there are no more characters (EOF), the memory read should return -1.
    }
  }
  return 0;



}
