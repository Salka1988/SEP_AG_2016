#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

class Element {
protected:
    string name_;

public:

    Element(string n) : name_(n) {
    }
    virtual void print() = 0;
    virtual ~Element(){};
};

class Fish: public Element {
private:
    int age_;
    
public:
    Fish(string n, int y) : Element(n), age_(y) {
    }
    void print() {
      cout << name_ << ", " << age_ << endl;
    }
};

class Plant: public Element {
private:
    bool frost_resistant_;
    
public:
    Plant(string n, bool fr) :Element(n), frost_resistant_(fr) {
    }
    void print() {
      cout << name_ << ", " << (frost_resistant_ ? "frost-resistant" : "not frost-resistant") << endl;
    }
};



int main() {
    vector<Element*> contacts;
    
    while(1) {
        cout << "> ";
        string command;
        getline(cin, command);
        if (cin.bad() || cin.eof()) break;

        if (command == "") continue;
        istringstream iss(command);
        vector <string> tokens{istream_iterator < string > {iss}, istream_iterator < string > {}};
        
        if(tokens[0] == "quit") break;
        
        if(tokens[0] == "add" && tokens.size() == 4) {
          if(tokens[1] == "fish") {
            try{
              contacts.push_back(new Fish(tokens[2], std::stoi(tokens[3])));
            }catch(...) {}
          }
          if(tokens[1] == "plant") {
            if(tokens[3] == "true") {
              contacts.push_back(new Plant(tokens[2], true));

            } else if(tokens[3] == "false") {
              contacts.push_back(new Plant(tokens[2], false));
            }
          }
        }
        
        if(tokens[0] == "list" && tokens.size() == 1) {
          for(auto c: contacts){
            c->print();
          }
        }
        /*
        if(tokens[0] == "show" && tokens.size() >= 2) {
          if(accounts.count(tokens[1])) {
            cout << *(accounts[tokens[1]]) << endl;   
          } else cout << UNKNOWN_NAME << endl;
        }*/
    }
    
    for(auto a : contacts) {
      delete a;   
    }
    
    return 0;
}
