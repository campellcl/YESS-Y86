/**
 * Names: Jon Hebert && Chris Campell
 * Team: #2
 */
#include <iostream>
#include <iomanip>

using namespace std;

#include "Memory.h"
#include "Tools.h"

//mem_instance will be initialized to the single instance
//of the Memory class
Memory * Memory::mem_instance = NULL;

/** 
 * Memory constructor
 * initializes the mem array to 0
 */
Memory::Memory()
{
    for(int i = 0; i < MEMSIZE; i++) {
        mem[i] = 0;
    }
}

/**
 * getInstance
 * if mem_instance is NULL then creates a Memory object
 * and sets mem_instance to point it; returns mem_instance
 */
Memory * Memory::getInstance()
{
    if (mem_instance == NULL) {
       mem_instance = new Memory();
       return mem_instance;
    } else {
       return mem_instance; 
    }
}

/**
 * getLong
 * returns the 64-bit word at the indicated address; sets imem_error
 * to false if the access is aligned and the address is within range;
 * otherwise sets imem_error to true
 *
 * @param address of 64-bit word; access must be aligned
 * @return imem_error is set to true or false
 * @return returns 64-bit word at the specified address or 0 if the
 *         access is not aligned or out of range
 */
uint64_t Memory::getLong(int32_t address, bool & imem_error)
{
    //TODO: Finish writing this method. 
    if ((address % 8) == 0) {
       if ((address + 7) < MEMSIZE && address >= 0) {
          imem_error = false;
          uint64_t currValue = Tools::buildLong(&mem[address]); 
          return currValue;
       } else {
           imem_error = true;
           return 0;
       }
    } else {
        imem_error = true;
       return 0;
    }
}

/**
 * getByte
 * returns the byte (8-bits) at the indicated address; sets imem_error
 * to false if the address is within range; otherwise sets imem_error to
 * true
 *
 * @param address of byte
 * @return imem_error is set to true or false
 * @return byte at specified address or 0 if the address is out of range
 */
uint8_t Memory::getByte(int32_t address, bool & imem_error)
{
    //A single byte doesn't run the risk of being mis-aligned.
    if (address < MEMSIZE && address >= 0) {
        imem_error = false;
        return mem[address];
    } else {
        imem_error = true;
        return 0;
    }
}

/**
 * putLong
 * sets the 64-bit word in memory at the indicated address to the
 * value that is provided; sets imem_error to false if the access
 * is aligned and the address is within range; otherwise sets 
 * imem_error to true
 *
 * @param 64-bit value to be stored in memory (mem array)
 * @param address of 64-bit word; access must be aligned
 * @return imem_error is set to true or false
 */
void Memory::putLong(uint64_t value, int32_t address, bool & imem_error)
{
    if ((address % 8) == 0) {
        if ((address + 7) < MEMSIZE && address >= 0) {
            imem_error = false;
            //grab one byte at a time from value and store in mem.
            for (int i = 0; i < 8; i++) {
                mem[address+i] = Tools::getByte(value, i);
            }
        } else {
            imem_error = true;
        }
    } else {
        imem_error = true;
    }
}

/**
 * putByte
 * sets the byte (8-bits) in memory at the indicated address to the value
 * provided; sets imem_error to false if the address is within range; 
 * otherwise sets imem_error to true
 *
 * @param 8-bit value to be stored in memory (mem array)
 * @param address of byte
 * @return imem_error is set to true or false
 */

void Memory::putByte(uint8_t value, int32_t address, bool & imem_error)
{
    //a single byte doesn't run the risk of mis-alignment
    if (address < MEMSIZE && address >= 0)
    {
        imem_error = false;
        mem[address] = value;
    } else {
        imem_error = true;
    }
}


/**
 * dump
 * Output the contents of memory (mem array), four 64-bit words per line.
 * Rather than output memory that contains a lot of 0s, it outputs
 * a * after a line to indicate that the values in memory up to the next
 * line displayed are identical.
 */
void Memory::dump()
{
   uint64_t prevLine[4] = {0, 0, 0, 0};
   uint64_t currLine[4] = {0, 0, 0, 0};
   int32_t i;
   bool star = false;
   bool mem_error;

   //32 bytes per line (four 8-byte words)
   for (i = 0; i < MEMSIZE; i+=32)
   {
      //get the values for the current line
      for (int32_t j = 0; j < 4; j++) currLine[j] = getLong(i+j*8, mem_error);

      //if they are the same as the values in the previous line then
      //don't display them, but always display the first line
      if (i == 0 || currLine[0] != prevLine[0] || currLine[1] != prevLine[1] 
          || currLine[2] != prevLine[2] || currLine[3] != prevLine[3])
      {
         cout << endl << hex << setw(3) << i << ": "; 
         for (int32_t j = 0; j < 4; j++) 
             cout << setw(16) << setfill('0') << currLine[j] << " ";
         star = false;
      } else
      {
         //if this line is exactly like the previous line then
         //just print a * if one hasn't been printed already
         if (star == false)
         {
            cout << "*";
         } 
         star = true;
      }
      for (int32_t j = 0; j < 4; j++) prevLine[j] = currLine[j];
   }
   cout << endl;
}
