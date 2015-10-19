
#define OF 0   //overflow condition code is bit 0 of codes
#define SF 1   //signflag condition code is bit 1 of codes
#define ZF 2   //zeroflag condition code is bit 2 of codes

class ConditionCodes 
{
   private:
      //cc_instance points to the single ConditionCodes instance
      static ConditionCodes * cc_instance;
      //constructor is private since ConditionCodes is a singleton
      ConditionCodes();
      
   public:
      //codes is public for testing purposes
      //after this lab, you can make it private
      uint64_t codes; //used to simulate the register that stores the condition codes

      static ConditionCodes * getInstance();      

      bool getConditionCode(int32_t ccNum);

      void setConditionCode(bool value, int32_t ccNum);

      void dump();

}; 
