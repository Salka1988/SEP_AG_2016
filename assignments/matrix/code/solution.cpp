#include <iostream>
#include <fstream>

#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

class Matrix {
private: 
  Matrix(const Matrix& ba) {};
public: 
  string filename_;
  int rows_;
  int columns_;
  int **array_;

  Matrix(string file): filename_(file), array_(nullptr), columns_(-1), rows_(-1) {
    std::ifstream input(file);
    read(input);
    input.clear();
    input.seekg(0, ios::beg);
    array_ = new int*[rows_];
    read(input);
    
  } ;
  ~Matrix() {};
  
  void read(std::ifstream& input) {
    std::string line;
    
    int cols = -1;
    int rows = 0;

    while (std::getline(input, line)) {
        try {
          std::istringstream iss(line);
          std::vector <std::string> tokens{std::istream_iterator < std::string > {iss},
                                         std::istream_iterator < std::string > {}};
        
          if(array_ == nullptr && columns_ != -1 && columns_ != tokens.size()) {
            cout << "invalid file" << endl;
            break;
          }else if (array_ == nullptr) {
            columns_ = tokens.size();
          } else {
            array_[rows] = new int[columns_];
            int cur_col = 0;

            for(string x : tokens) {
              array_[rows][cur_col++] = std::stoi(x);
            }
          }
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
        rows++;
    }
    rows_ = rows;
  }
  
  void transpose() {
    
    ofstream myfile;
    myfile.open ("transpose.txt");
    for(int x = 0; x < columns_; x++) {
      for(int y = 0; y < rows_; y++) {
        myfile << array_[y][x] << " ";
      }
      myfile << endl;
    }
    myfile.close();
  }
  
};

int main() {

    Matrix *matrix = new Matrix("matrix.txt");
    matrix->transpose();
    return 0;
}