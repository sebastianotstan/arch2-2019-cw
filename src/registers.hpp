#include<vector>
#include<cstdint>

class registers{
private:
  std::vector<int> registers;
  int LO;
  int HI;
  uint32_t address_counter;//increment of 4, each store 4 bytes

public:
  registers();//default
  int get_registers(int i);
  void set_registers(int i, int num);
  uint32_t get_address_counter();
  void set_address_counter(uint32_t num);
  int get_LO();
  void set_LO(int num);
  int get_HI();
  void set_HI(int num);
};
