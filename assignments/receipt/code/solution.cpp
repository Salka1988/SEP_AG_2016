#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

const string UNKNOWN_NAME = "Receipt does not exist!";

class Entry {
private:
    string name;
    double cost;
public:
    Entry(string n, double c) : name(n), cost(c) {}
    
    double getCost() { return cost; }
    string getName() { return name; }
};

class Receipt {
private:
    string name;
    vector<Entry> products;
    
public:
    Receipt(string n) : name(n) {
    }
    
    void add(Entry e) {
       products.push_back(e);   
    }
    
    friend ostream& operator<<(ostream& os, const Receipt& receipt);

};

ostream& operator<<(ostream& os, const Receipt& receipt) {
    double total = 0;
    for(auto e : receipt.products) {
      os << e.getName() << " " << e.getCost() << endl;
      total += e.getCost();
    }
    os << "----" << endl << "Total: " << total << endl;
    return os;
}

int main() {
    map<string, Receipt*> receipts;
    
    while(1) {
        cout << "> ";
        string command;
        getline(cin, command);
        if (cin.bad() || cin.eof()) break;

        if (command == "") continue;
        istringstream iss(command);
        vector <string> tokens{istream_iterator < string > {iss}, istream_iterator < string > {}};
        
        if(tokens[0] == "quit") break;
        
        if(tokens[0] == "new" && tokens.size() >= 2) {
          receipts[tokens[1]] = new Receipt(tokens[1]);   
        }
        
        if(tokens[0] == "add" && tokens.size() >= 4) {
          if(receipts.count(tokens[1])) {
            try {
              Entry e(tokens[2], stof(tokens[3]));
              receipts[tokens[1]]->add(e);   
            } catch(...) {}
          } else cout << UNKNOWN_NAME << endl;
        }
        
        if(tokens[0] == "print" && tokens.size() >= 2) {
          if(receipts.count(tokens[1])) {
            cout << *(receipts[tokens[1]]) << endl;   
          } else cout << UNKNOWN_NAME << endl;
        }
    }
    
    for(auto a : receipts) {
      delete a.second;   
    }
    
    return 0;
}
