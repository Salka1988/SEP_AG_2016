#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

class BitArray {
private: 
  BitArray(const BitArray& ba) {};
public: 
  int length_;
  int *array_;

  BitArray(int *arr, int length): array_(arr), length_(length) {} ;
  ~BitArray() {};
  BitArray& operator&= (const BitArray& rhs) {
    if(this->length_ != rhs.length_) {
      cout << "dimension mismatch" << endl;
      return *this;
    }
    for(int i = 0; i < this->length_; i++) {
      this->array_[i] &= rhs.array_[i];
    }
    return *this;
  }
  
  
  BitArray& operator&= (const int rhs) {
    for(int i = 0; i < this->length_; i++) {
      this->array_[i] &= rhs;
    }
    return *this;
  }
};

int main() {

    int arr[] = {1, 2, 3, 4, 5};
    int arr2[] = {0, 0, 0, 0, 0, 0};

    BitArray *ba = new BitArray(arr, 5);
    BitArray a(arr, 5);
    BitArray b(arr2, 6);

    a &= b;
    a &= 1;
    
    for(int i = 0; i < 5; i++) {
      cout << a.array_[i] << endl;
    }
    return 0;
}