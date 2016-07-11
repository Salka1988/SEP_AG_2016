#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

const string UNKNOWN_NAME = "Name does not exist!";

class Account {
private:
    string name;
    int amount;
    
public:
    Account(string n) : amount(0), name(n) {
    }
    
    void add(int money) {
       amount += money;   
    }
    
    friend ostream& operator<<(ostream& os, const Account& account);

};

ostream& operator<<(ostream& os, const Account& account) {
    os << account.name << ": " << account.amount;
    return os;
}

int main() {
    map<string, Account*> accounts;
    
    while(1) {
        cout << "> ";
        string command;
        getline(cin, command);
        if (cin.bad() || cin.eof()) break;

        if (command == "") continue;
        istringstream iss(command);
        vector <string> tokens{istream_iterator < string > {iss}, istream_iterator < string > {}};
        
        if(tokens[0] == "quit") break;
        
        if(tokens[0] == "create" && tokens.size() >= 2) {
          accounts[tokens[1]] = new Account(tokens[1]);   
        }
        
        if(tokens[0] == "add" && tokens.size() >= 3) {
          if(accounts.count(tokens[1])) {
            accounts[tokens[1]]->add(stoi(tokens[2]));   
          } else cout << UNKNOWN_NAME << endl;
        }
        
        if(tokens[0] == "show" && tokens.size() >= 2) {
          if(accounts.count(tokens[1])) {
            cout << *(accounts[tokens[1]]) << endl;   
          } else cout << UNKNOWN_NAME << endl;
        }
    }
    
    for(auto a : accounts) {
      delete a.second;   
    }
    
    return 0;
}
