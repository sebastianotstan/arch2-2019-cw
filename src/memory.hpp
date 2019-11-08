#include <vector>
#include <stdint.h>

class memory{
  // std::vector<char> imem;
  // std::vector<char> dmem;
  // char memblock;
  private:
    std::vector<char> imem;
    std::vector<char> dmem;
    // char memblock;
  public:
    memory();
    static const uint32_t addr_NULL = 0x00000000;
    static const uint32_t addr_NULL_length = 0x4;
    static const uint32_t addr_INSTR = 0x10000000;
    static const uint32_t addr_INSTR_length = 0x1000000;
    static const uint32_t addr_DATA = 0x20000000;
    static const uint32_t addr_DATA_length = 0x4000000;
    static const uint32_t addr_GETC = 0x30000000;
    static const uint32_t addr_GETC_length = 0x4;
    static const uint32_t addr_PUTC = 0x30000004;
    static const uint32_t addr_PUTC_length = 0x4;

    // vector<char> imem;
    // imem.resize(0x1000000);
    // vector<char> dmem;
    // dmem.resize(0x4000000);

    // void load_instr(vector<uint8_t> imem, file binStream);

    uint32_t form_instr(int pc);

    // uint32_t get_instr(int pc, std::vector<char> imem);

    bool addr_in_instr(int num_bits, int start);

    bool addr_in_data(int num_bits, int start);

    void set_ivector(int count, char value);

    uint32_t get_instruction(int address);

    uint32_t get_n_bytes(int address, int n);

    uint32_t get_iaddress(int address);

    void set_iaddress(int address, char value);

    // void set_dvector(int count, char value);


};
