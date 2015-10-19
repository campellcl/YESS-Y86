/**
 * Names: Chris Campell, Jon Hebert
 * Team: Team2
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>

using namespace std;

#include "Loader.h"
#include "Memory.h"

//first column in file is assumed to be 0
#define ADDRBEGIN 2   //starting column of 3 digit hex address 
#define ADDREND 4     //ending column of 3 digit hext address
#define DATABEGIN 7   //starting column of data bytes
#define DATAEND 26    //ending column of data bytes
#define COMMENT 28    //location of the '|' character 

/**
 * Loader constructor
 * Opens the .yo file named in the command line arguments, reads the contents of the file
 * line by line and loads the program into memory.  If no file is given or the file doesn't
 * exist or the file doesn't end with a .yo extension or the .yo file contains errors then
 * loaded is set to false.  Otherwise loaded is set to true.
 *
 * @param argc is the number of command line arguments passed to the main; should
 *        be 2
 * @param argv[0] is the name of the executable
 *        argv[1] is the name of the .yo file
 */
Loader::Loader(int argc, char * argv[])
{
   string line;
   //start by writing a method that opens the file (checks whether it ends with a .yo and
   //whether the file successfully opens; if not, return without loading)
   if (argc == 2) {
       //attempt to open specified file: 
       if(openFile(argc, argv)) {
           //file opened successfully.
           while (std::getline(inf, line)) {
               //print the input line to the console.
               cout << line << endl;  
               //validate the input line to ensure it's error free.
               if (!hasError(line)) {
                   //load the error free input line into memory.
                   loadLine(line);
               } else{
                    //error in input line.
                    //TODO: write fallback for an input line with errors.
               }
           }
           loaded = true;
       } else {
           loaded = false;
       }
   } else {
       loaded = false;
       return;
   }
   //next write a simple loop that reads the file line by line and prints it out
    
   //next, add a method that will write the data in the line to memory (call that from within
   //your loop)

   //Finally, add code to check for errors in the input line.
   //When your code finds an error, you need to print an error message and return.
   //Since your output has to be identical to your instructor's, use this cout to print the
   //error message.  Change the variable names if you use different ones.
   //  cout << "Error on line " << dec << lineNumber
   //       << ": " << line << endl;
}

/**
 * openFile()
 * Opens the specified file while ensuring two things:
 *      The specified file ends with a .yo
 *      The file was successfully opened
 * @param numArgs -The number of command line arguments passed to main.
 * @param argv[0] - The name of the executable passed to main. 
 *        argv[1] - The name of the .yo file passed to main. 
 * @return bool -true if file was successfully opened and ends in a .yo,
 *  false otherwise.
**/
bool Loader::openFile(int numArgs, char * argv[]) {
    //check the last three characters of the file name and make sure it is a .yo
    //get the size of the character array comprising the file name. 
    int size = strlen(argv[1]);
    string fileName = argv[1];
    //if file extension matches
    if (fileName.compare(size-3,size,".yo") == 0) {
       inf.open(argv[1],std::ifstream::in);
       if (inf.is_open()) {
        return true;
       } else {
        return false;
       }
    } else {
        return false;
    }
}

/**
 * isLoaded
 * returns the value of the loaded data member; loaded is set by the constructor
 *
 * @return value of loaded (true or false)
 */
bool Loader::isLoaded()
{
   return loaded;
}

/**
 * TODO: Verify this method is correct in both execution and intent.
 *  Reference instructions on ASULEARN.
 * convert
 * Converts a string to a hex.
 * @param line -the string to be converted.
 * @param start -the starting column for the conversion.
 * @param end -the ending column for the conversion.
**/
int32_t Loader::convert(string line, int start, int end) {
    //TODO: write check bounds method, to verify return type doesnt overflow.
    string data = "";
    for (int i = start; i <= end; i++) {
        data += line.c_str()[i];
    }
    return strtol(line.c_str(), NULL, 16);
}

/**
 * hasAddress
 * returns true if the input line has an address, false otherwise
 * @param s -the string
**/
bool Loader::hasAddress(string s) {
   //make sure that the string is a hex value.
   if (s.c_str()[0] == '0' && s.c_str()[1] == 'x') {
        //if 0x_ _ _ : all blanks (_) are valid hex digits, line has address.
        if (isxdigit(s.c_str()[ADDRBEGIN]) && isxdigit(s.c_str()[3])
            && isxdigit(s.c_str()[ADDREND])) {
            return true;
        } else {
            return false;
        }
   } else {
        return false;
   }
}

/**
 * getAddress
 * Returns the address of the instruction as a string.
 * @param line -The syntactically correct and error free input line.
 * @return addy -The string representation of the address.
*/
string Loader::getAddress(string line) {
    if (hasAddress(line))
     {
        string addy = "";
        addy += line.c_str()[2];
        addy += line.c_str()[3];
        addy += line.c_str()[4];
        //uint32_t ttAddy = strtol(addy.c_str(), NULL, 16);
        //cout << "ttAddy: %x" << ttAddy << endl;
        return addy;
     }
     else
     {
        return NULL;
     }
}

/**
 * hasData
 * returns true if the input line has data. 
 * @param line -The sytnactically correct input line.
 * @return bool -true if TODO:fill this out. false otherwise.
**/
bool Loader::hasData(string line) {
   if (!isblank(line.c_str()[DATABEGIN])) {
       return true;
   } else {
       return false;
   }
}

/**
 * isHexData
 * Returns true if the string is comprised of valid hex characters.
 * @param s -the string of hex characters.
 * @return bool -true if valid hex chars, false otherwise.
**/
bool Loader::isHexData(string s) {
    char hex1 = s.c_str()[DATABEGIN];
    char hex2 = s.c_str()[DATABEGIN+1];
    bool valid = 1;
    //loop to check two hex charcters at a time until space.
    while(valid){
        if (!isxdigit(hex1) && !isxdigit(hex2))
        {
         hex1+=2;
         hex2+=2;
        }
        else
        {
            //not valid, break.
            valid = 0;
        }
    }
    return valid;
}

/**
 * getDataEnd
 * Returns the column of the last valid hex character.
 * @param line -the line read from the file
 * @return int column -the index of the last column containing a valid hex character.
**/
int Loader::getDataEnd(string line) {
    char byte1 = line.c_str()[DATABEGIN];
    char byte2 = line.c_str()[DATABEGIN+1];
    int column = 0;
    
    while(true) {
        //while both char's are valid hex characters
        if (isxdigit(byte1) && isxdigit(byte2)) {
            column++; 
        } else {
            break;
        }
    }
    return column;
}
/**
 * getData
 * Gets the data from the input line.
 * @param line -the line read from the input file.
 * @return data -A string containing the data section of the input line.
**/
string getData(string line) {
    string data = "";
    for(int i = 0; i < strlen(line.c_str()); i++) {
        //TODO: method body.
    }
    line = line << 28;
    return line;
}

/**
 * loadLine
 * Takes a line from the file and loads each byte into memory.
 *      NOTE: TODO:This function peforms no error checking. 
 * @param line -A syntactially correct and error free line read from the input file.
 * @return void -Upon returning, the error free line has been read into memory.
*/
void Loader::loadLine(string line) 
{
   int firstByte = DATABEGIN;
   int secondByte = DATABEGIN + 1;
   uint8_t firstByteData;
   uint8_t secondByteData;
   bool imem_error = false;
   //get the address
    uint32_t address = convert(line,ADDRBEGIN,ADDREND);
    cout << "address: %x" << address << endl;
    //get the data
     while( isxdigit(line.c_str()[firstByte]) && isxdigit(line.c_str()[secondByte]))
     {
      firstByteData = convert(line, firstByte, firstByte);
      secondByteData = convert(line, secondByte, secondByte);
      firstByte += 2;
      secondByte += 2;
      Memory::getInstance()->putByte(firstByteData, address, imem_error);
      Memory::getInstance()->putByte(secondByteData, address, imem_error);    
     }
}

/**
 * hasError
 * Takes an instruction from the current line of input and checks for errors.
 *      Checks both the address and data portion of the line for errors.
 * @param line -the line read from the input file.
 * @return bool -false if no errors, true otherwise.
**/
bool Loader::hasError(string line) {
    if (!hasAddrError(line) && !hasDataError(line)){
        //Line has no Address or Data Errors.
        return false;
    } else {
        //Line has errors.
        return true;
    }
}

/**
 * hasAddrError
 * Takes an address from the current line of input and checks for errors.
 * @param line -the line read from the input file
 * @return bool -false if no errors, true otherwise
**/
bool Loader::hasAddrError(string line) {
    //check columns 0-1 to ensure characters are '0' and 'x'.
    if (line.c_str()[0] == '0' && line.c_str()[1] == 'x') {
        //check columns 2-4 to ensure valid hex digit.
        for(int i = 2; i < 5; i++) {
            if(!isxdigit(line.c_str()[i])) {
                return false;
            }
        }
        //the address on a line must be greater than the address
        //  of the last byte of data.
        //uint64_t data = getData(line); 
        //int instrLength = getOpcodeLength(line);
        //int lineLength = strlen(line); 
        //get the address of line as a number..  
        string address = line.c_str()[2] + line.c_str()[3] + line.c_str()[4];
        string data = "";
        for(int i = 7; line.c_str()[i] != NULL; i++) {
            data += line.c_str()[i];
        }
        int addrHex = strtol(address,NULL,16);
        int instrLength = strlen(data); 
        int instrHex = strtol(data,NULL,16);
        int addrLastByte = addrHex + instrLength;
        if (addrLastByte <= (instrLength + addrHex)) {
            //address of last btye
        }
        //TODO: write above check.
        return true;
    } else {
        return false;
    }
}

/**
 * hasDataError
 * Takes the data portion from the current line of input and checks for errors.
 * @param line -the line read form the input file
 * @return bool -false if no errors, true otherwise
**/
bool Loader::hasDataError(string line) {
    //TODO: write method body.
}

/**
 * isAllSpace
 * Checks to see if some range within the string is all spaces. 
 * @param start -the starting char index in the range to check.
 * @param end -the ending char index in the range to check.
 * @param line -the line read from the input file.
 * @return bool -true if all characters within the specified
 *  range are spaces, false otherwise.
**/
bool Loader::isAllSpace(int start, int end, string line) {
    //TODO: write method body.
}
/**
 * getOpcodeLength
 * Returns the lenght of the instruction data.
 * @param line -the line read from the input file.
 * @return length -the length of the instruction.
**/
int getOpcodeLength(string line) {
    //TODO: method body.
    int instrLength;
    for(i = 7; line.c_str()[i] != NULL; i++) {
        instrLength = i;
    }
    return instrLength
}

//You'll need to add more helper methods to this file.  Don't put all of your code in the
//Loader constructor.  When you add a method here, add the prototype to Loader.h in the private
//section.

