
#define MEMSIZE 0x1000
class Memory 
{
   private:
      //points to the single Memory instance
      static Memory * mem_instance;  
      //the constructor is private since Memory is a singleton
      Memory(); 
      
   public:
      //making this array public for the MemoryTester
      //after this lab, you can make it private
      uint8_t mem[MEMSIZE];

      static Memory * getInstance();      

      uint64_t getLong(int32_t address, bool & imem_error);

      uint8_t getByte(int32_t address, bool & imem_error);

      void putLong(uint64_t value, int32_t address, bool & imem_error);

      void putByte(uint8_t value, int32_t address, bool & imem_error);

      void dump();

}; 
