#include "registers.hpp"
#include<iostream>
using namespace std;

registers::registers(){//32 registers
  for(int i = 0; i < 32; i++){
    registers.push_back(0);
  }
  LO_reg = 0;
  HI_reg = 0;
  pc = 0;
}//initialise the cpu

  int registers::get_registers(int i){
    return registers[i];
  }

  void registers::set_registers(int i, int num){
    if((i != 0) && (i < 32)){//$0 is constant value of 0, always return 0
      registers[i] = num;
    }
  }

  uint32_t registers::get_PC(){
    return pc;
  }

  void registers::set_PC(uint32_t num){
    if(num%4 == 0){
      pc = num;
    }//check if address is multiple of 4
  }

  int registers::get_LO(){
    return LO_reg;
  }

  void registers::set_LO(uint32_t num){
    LO_reg = num;
  }

  int registers::get_HI(){
    return HI_reg;
  }

  void registers::set_HI(uint32_t num){
    HI_reg = num;
  }
