/**
 * Names: Jon Hebert && Chris Campell
 * Team: #2
 */
#include <iostream>
#include <iomanip>

using namespace std;

#include "ConditionCodes.h"
#include "Tools.h"

//cc_instance will be initialized to reference the single instance of ConditionCodes
ConditionCodes * ConditionCodes::cc_instance = NULL;

/**
 * ConditionCodes constructor
 * initialize the codes field to 0
 */
ConditionCodes::ConditionCodes()
{
    codes = 0;
}

/**
 * getInstance
 * if cc_instance is NULL then getInstance initializes it to 
 * reference the ConditionCodes singleton. Otherwise, it
 * returns cc_instance
 *
 * @return cc_instance
 */
ConditionCodes * ConditionCodes::getInstance()
{
    if (cc_instance == NULL) {
       cc_instance = new ConditionCodes(); 
       return cc_instance;
    } else {
        return cc_instance;
    }
}

/*
 * getConditionCode
 * accepts a condition code number (OF, SF, or ZF) and returns 
 * the value of the condition code 
 *
 * @param ccNum equal to either OF, SF, or ZF
 * @return the value of bit ccNum out of codes. if ccNum is 
 *         out of range then returns false
 */
bool ConditionCodes::getConditionCode(int32_t ccNum)
{
    if (ccNum != OF && ccNum != SF && ccNum != ZF) {
        return false;
    } else {
        return Tools::getBits(codes,ccNum,ccNum);
    }
}

/*
 * setConditionCode
 * accepts a condition code number (OF, SF, or ZF) and value
 * (true or false) and sets the condition code bit to that
 * value (1 or 0). if the ccNum value is out of range then
 * codes does not get modified. 
 *
 * @param value to set the condition code bit (true/1 or false/0)
 * @param ccNum equal to either OF, SF, or ZF
 */
void ConditionCodes::setConditionCode(bool value, int32_t ccNum)
{
    if (ccNum != OF && ccNum != SF && ccNum != ZF) {
        // do nothing
        return;
    } else {
        if (value == 1) {
            codes = Tools::setBits(codes, ccNum, ccNum);
        } else {
            codes = Tools::clearBits(codes, ccNum, ccNum); 
        }
    }
}

/*
 * dump
 * outputs the values of the condition codes
 */
void ConditionCodes::dump()
{
   int32_t zf = Tools::getBits(codes, ZF, ZF);
   int32_t sf = Tools::getBits(codes, SF, SF);
   int32_t of = Tools::getBits(codes, OF, OF);
   cout << endl;
   cout << "ZF: " << hex << setw(1) << zf << " ";
   cout << "SF: " << hex << setw(1) << sf << " ";
   cout << "OF: " << hex << setw(1) << of << endl;
}
