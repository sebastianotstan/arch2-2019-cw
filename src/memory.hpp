#include <vector>

class memory{
  private:

  public:
    static const int addr_NULL = 0x00000000;
    static const int addr_NULL_length = 0x4;
    static const int addr_INSTR = 0x10000000;
    static const int addr_INSTR_length = 0x1000000;
    static const int addr_DATA = 0x20000000;
    static const int addr_DATA_length = 0x4000000;
    static const int addr_GETC = 0x30000000;
    static const int addr_GETC_length = 0x4;
    static const int addr_PUTC = 0x 30000004;
    static const int addr_PUTC_length = 0x4;

    vector<char> imem;
    imem.resize(0x1000000);
    vector<char> dmem;
    dmem.resize(0x4000000);

    // void load_instr(vector<uint8_t> imem, file binStream);

    char form_instr(vector<char> imem, int pc);

    uint32_t get_instr(int pc, vector<uint8_t> imem);

    bool addr_in_instr(int num_bits, int start);

    bool addr_in_data(int num_bits, int start);



}
