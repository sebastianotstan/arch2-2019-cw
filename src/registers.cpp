#include "registers.hpp"
#include<iostream>
using namespace std;

registers::registers(){//32 registers
  for(int i = 0; i < 32; i++){
    registers.push_back(0);
  }//initialise
  LO = 0;
  HI = 0;
}

  int registers::get_registers(int i){
    return registers[i];
  }

  void registers::set_registers(int i, int num){
    if((i != 0) && (i < 32)){//$0 is constant value of 0, always return 0
      registers[i] = num;
    }
  }

  int registers::get_address(){
    return address_counter;
  }

  void registers::set_address(uint32_t num){
    address_counter = num;
  }

  int registers::get_LO(){
    return LO;
  }

  void registers::set_LO(int num){
    LO = num;
  }

  int registers::get_HI(){
    return HI;
  }

  void registers::set_HI(int num){
    HI = num;
  }
