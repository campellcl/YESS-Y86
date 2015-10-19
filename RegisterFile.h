#define REGSIZE 15
#define RAX 0
#define RCX 1
#define RDX 2
#define RBX 3
#define RSP 4
#define RBP 5
#define RSI 6
#define RDI 7
#define R8  8
#define R9  9
#define R10 0xa
#define R11 0xb
#define R12 0xc
#define R13 0xd
#define R14 0xe
#define RNONE 0xf

class RegisterFile 
{
   private:
      //points to the single RegisterFile instance 
      static RegisterFile * reg_instance;
      //constructor is private since RegisterFile is a singleton
      RegisterFile();
      
   public:
      //making this array public for the RegisterFileTester
      //after this lab, you can make it private
      uint64_t reg[REGSIZE];

      static RegisterFile * getInstance();      

      uint64_t readRegister(int32_t regNumber);

      void writeRegister(uint64_t value, int32_t regNumber);

      void dump();

}; 
