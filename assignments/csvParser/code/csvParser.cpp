#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

enum ERROR {
  SUCCESS,
  FILE_DOES_NOT_EXIST,
  NUMBERS_NOT_VALID
};

void printErr(ERROR err) {
  switch(err) {
    case FILE_DOES_NOT_EXIST:
      cout << "File does not exist!" << endl;
      break;
    case NUMBERS_NOT_VALID:
      cout << "Numbers not valid!" << endl;
      break;
    default:
      break;
  }
}

typedef vector<string> DimArray1;
typedef vector<DimArray1> DimArray2;

class CsvParser {
private:
  DimArray2 csvTable;
public:
  ERROR fillCsvTableFromFile(string file) {
    ifstream fileStream(file);
    if(!fileStream)
      return FILE_DOES_NOT_EXIST;
    
    while(1) {
      string line;
      if(!std::getline(fileStream, line))
        break;

      csvTable.push_back(DimArray1());
      
      //cout << "line: " << line << endl;
     
      int startIndex, endIndex;
      startIndex = endIndex = 0;
      // manual tokenize
      for(unsigned i = 0; i < line.length(); i++) {
        const char c = line[i];
        if(c == ';') {
          endIndex = i;
        
          DimArray1 &vectorLine = csvTable[csvTable.size() - 1];
          string str = string(line, startIndex, endIndex - startIndex);
          vectorLine.push_back(str);
          
          //cout << "str: " << str << endl;
          
          startIndex = endIndex + 1;
        }
      }
    }
    
    return SUCCESS;
  }
  
  ERROR getCsvEntry(string &result, int rowNumber, int columnNumber = -1) {

    if(rowNumber > (signed)csvTable.size())
      return NUMBERS_NOT_VALID;

    DimArray1 &rowVector = csvTable.at(rowNumber - 1);
    
    if(columnNumber == -1) {
      std::for_each(rowVector.begin(), rowVector.end(), [&](const std::string &part){ result += (part + ";"); });
    }
    else {
      if(columnNumber > (signed)rowVector.size())
        return NUMBERS_NOT_VALID;
      result = rowVector.at(columnNumber - 1);
    }
    
    return SUCCESS;
  }
};

int main() {
    CsvParser csvParser;
    
    while(true) {
        cout << "> ";
        string command;
        
        if(!getline(cin, command))
          break;

        if (command == "") continue;
        istringstream iss(command);
        vector <string> tokens{istream_iterator < string > {iss}, istream_iterator < string > {}};
        
        // QUIT
        if(tokens[0] == "quit") {
           break;
        } else if(tokens[0] == "load" && tokens.size() == 2) {
          ERROR err = csvParser.fillCsvTableFromFile(tokens[1]);
          if(err != SUCCESS) {
            printErr(err);
            continue;
          }
        // SHOW
        } else if(tokens[0] == "show" && (tokens.size() == 2 || tokens.size() == 3)) {
          // valid check
          int row = std::stol(tokens[1]);
          int col = (tokens.size() == 3) ? std::stol(tokens[2]) : -1;
          if(row < 1 || (tokens.size() == 3 && col < 1)) {
            printErr(NUMBERS_NOT_VALID);
            continue;
          }
          
          string result;
          if(csvParser.getCsvEntry(result, row, col) != SUCCESS) {
            printErr(NUMBERS_NOT_VALID);
            continue;
          }
          cout << result << endl;
        }

    }
    
    return 0;
}
