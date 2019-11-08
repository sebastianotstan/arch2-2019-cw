#include<vector>
#include<cstdint>

class registers{
private:
  std::vector<int> registers;
  uint32_t LO_reg;
  uint32_t HI_reg;
  uint32_t pc;//increment of 4, each store 4 bytes

public:
  registers();//default
  int get_registers(int i);
  void set_registers(int i, int num);
  uint32_t get_PC();
  void set_PC(uint32_t num);
  int get_LO();
  void set_LO(uint32_t num);
  int get_HI();
  void set_HI(uint32_t num);
};
