#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

class Contact {
protected:
    string name_;

public:

    Contact(string n) : name_(n) {
    }
    virtual void print() = 0;
    virtual ~Contact(){};
};

class PrivateContact: public Contact {
private:
    int birth_year_;
    
public:
    PrivateContact(string n, int y) : Contact(n), birth_year_(y) {
    }
    void print() {
      cout << name_ << ", " << birth_year_ << endl;
    }
};

class BusinessContact: public Contact {
private:
    string email_;
    
public:
    BusinessContact(string n, string e) :Contact(n), email_(e) {
    }
    void print() {
      cout << name_ << ", " << email_ << endl;
    }
};



int main() {
    vector<Contact*> contacts;
    
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
          if(tokens[1] == "private") {
            try{
              contacts.push_back(new PrivateContact(tokens[2], std::stoi(tokens[3])));
            }catch(...) {}
          }
          if(tokens[1] == "business") {
            contacts.push_back(new BusinessContact(tokens[2], tokens[3]));
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
