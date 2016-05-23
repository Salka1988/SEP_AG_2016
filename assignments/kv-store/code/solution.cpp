#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;


enum Type {
    INTEGER, STRING
};

class Entry {
private:
    string name;
    Type type;
    string value_str;
    int value_int;
    
public:
    Entry(string n, string val) : name(n), value_str(val), type(STRING) { }
    Entry(string n, int val) : name(n), value_int(val), type(INTEGER) { }
    
    Type getType() { return type; }
    int getValueInt() { return value_int; }
    string getValueString() { return value_str; }
    
    bool add(Entry* other) {
        if(other->getType() != type) {
            return false;
        }
        switch(type) {
            case INTEGER:
                value_int += other->getValueInt();
                break;
            case STRING:
                value_str += other->getValueString();
                break;
        }
        return true;
    }
    
    friend ostream& operator<<(ostream& os, const Entry& e);

};

ostream& operator<<(ostream& os, const Entry& e) {
    if(e.type == INTEGER) os << "Integer: " << e.value_int;
    else os << "String: " << e.value_str;
    return os;
}

int main() {
    map<string, Entry*> kv;
    
    while(1) {
        cout << "> ";
        string command;
        getline(cin, command);
        if (cin.bad() || cin.eof()) break;

        if (command == "") continue;
        istringstream iss(command);
        vector <string> tokens{istream_iterator < string > {iss}, istream_iterator < string > {}};
        
        if(tokens[0] == "bye") break;
        
        if(tokens[0] == "set" && tokens.size() >= 2) {
          if(tokens[2] == "Integer") {
              try {
                kv[tokens[1]] = new Entry(tokens[1], stoi(tokens[3]));
              } catch(...) {}
          } else if(tokens[2] == "String") {
            kv[tokens[1]] = new Entry(tokens[1], tokens[3]);
          }
        }
        
        if(tokens[0] == "add" && tokens.size() >= 3) {
          if(kv.count(tokens[1]) && kv.count(tokens[2])) {
            if(!kv[tokens[1]]->add(kv[tokens[2]])) {
              cout << "Incompatible datatypes" << endl;   
            }
          }
        }
        
        if(tokens[0] == "get" && tokens.size() >= 2) {
          if(kv.count(tokens[1])) {
            cout << *(kv[tokens[1]]) << endl;   
          }
        }
    }
    
    for(auto a : kv) {
      delete a.second;   
    }
    
    return 0;
}
