
class Loader
{
   private:
      bool loaded;   //set to true if a file is successfully loaded into memory
      ifstream inf;  //input file handle
      bool openFile(int argc, char * agrv[]);    //helper method opens the file and checks .yo extension.
      void loadLine(string line);
      int32_t convert(string line, int start, int end); //returns a string as an int
      int getDataEnd(string line);  //returns the index of the last valid hex token.
      bool hasAddress(string s);    //return true if the input line has an address
      uint32_t getAddress(string line);    //returns the address of the instruction. 
      bool hasData(string s);       //return true if the input line has data
      bool isHexData(string s);     //returns true if the input string (presumably data) is valid hex chars.
      uint8_t getData(string line); // gets data from input line. The Returns the data section of input line
      bool hasAddrError(string line);   //Takes an address from the current line of input and checks for errors.
      bool hasDataError(string line);   //Takes the data portion from the current line of input and checks for errors.
      bool hasError(string line);   //Checks the address and data portion from the current line of input for errors.
      bool isAllSpace(int start, int end, string line); //Checks to see if some range with the string is all spaces.
   public:
      Loader(int argc, char * argv[]);
      bool isLoaded();  //returns the value of the loaded data member. 
};
