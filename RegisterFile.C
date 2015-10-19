/**
 * Names: Jon Hebert && Chris Campell
 * Team: #2
 */
#include <iostream>
#include <iomanip>

using namespace std;

#include "RegisterFile.h"
#include "Tools.h"

//reg_instance will be initialized to the single RegisterFile
//object that is created
RegisterFile * RegisterFile::reg_instance = NULL;

/**
 * RegisterFile constructor
 * initialize the contents of the reg array to 0
 */
RegisterFile::RegisterFile()
{
    for(int i = 0; i < REGSIZE; i++) {
        reg[i] = 0; 
    }
}

/**
 * getInstance
 * if reg_instance is NULL then creates a Register object
 * and sets reg_instance to point it; returns reg_instance
 */
RegisterFile * RegisterFile::getInstance()
{
    if (reg_instance == NULL)
    {
      reg_instance = new RegisterFile();
      return reg_instance;  
    }
    else
    {
      return reg_instance;
    }
}

/**
 * readRegister
 * returns a register value from the reg array.
 * if regNumber is a valid register number then returns
 * the register value; otherwise returns 0
 *
 * @param register number
 * @returns uses regNum to index into reg array; returns
 *          reg array value if index is valid; otherwise,
 *          returns 0
 */
uint64_t RegisterFile::readRegister(int32_t regNumber)
{
    if (regNumber <= REGSIZE && regNumber >= 0) {
        return reg[regNumber];
    } else {
       return 0; 
    }
}

/**
 * writeRegister
 * sets a register to a specified value if the regNumber is
 * within range; otherwise, does nothing
 *
 * @param value to be stored in register (reg array)
 * @param number of register to be modified (index into reg array)
 */
void RegisterFile::writeRegister(uint64_t value, int32_t regNumber)
{
    if (regNumber <= REGSIZE && regNumber >= 0) {
        reg[regNumber] = value;
    }
    else
       {
        //   cout << "writeregister else statement triggered" << endl;
       }
}

/**
 * dump
 * output the contents of the reg array
 */
void RegisterFile::dump()
{
   string rnames[15] = {"%rax: ", "%rcx: ", "%rdx: ",  "%rbx: ",
                        "%rsp: ", "%rbp: ", "%rsi: ",  "%rdi: ", 
                        "% r8: ", "% r9: ", "%r10: ",  "%r11: ",
                        "%r12: ", "%r13: ", "%r14: "};  
   for (int32_t i = 0; i < REGSIZE; i+=4)
   {
      for (int32_t j = 0; j < 3; j++)
         cout << rnames[i + j] << hex << setw(16) << setfill('0') << reg[i + j] << ' ';
      if (i + 3 < REGSIZE) 
         cout << rnames[i + 3] << hex << setw(16) << setfill('0') << reg[i + 3] << endl;
      else
         cout << endl;
   }
}
