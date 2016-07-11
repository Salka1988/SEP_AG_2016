#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

const string UNKNOWN_TRAIN = "Train does not exist!";
const string CANNOT_START = "Cannot start train!";
const string START = "Start train!";

class Train {
private:
    string train_number_;
    vector<string> passengers_;
public:
    Train(string train_number) : 
    train_number_(train_number) {}
    
    void addPassenger(string passenger) {
      if(passenger == "pas" || passenger == "con" || passenger == "driver") {
        passengers_.push_back(passenger);
      } else {
        cout << "Cannot add " << passenger << endl;
      }
    }
    
    bool startTrain() {
      if(std::find(passengers_.begin(), passengers_.end(), "con") != passengers_.end() &&
        std::find(passengers_.begin(), passengers_.end(), "driver") != passengers_.end()
      ){
        cout << START << endl;
        return true;
      } else 
      {
        cout << CANNOT_START << endl;
        return false;
      }
    }
    
  //  double getCost() { return cost; }
  //  string getName() { return name; }
};

int main() {
    map<string, Train*> trains;
    
    while(1) {
        cout << "> ";
        string command;
        getline(cin, command);
        if (cin.bad() || cin.eof()) break;

        if (command == "") continue;
        istringstream iss(command);
        vector <string> tokens{istream_iterator < string > {iss}, istream_iterator < string > {}};
        
        if(tokens[0] == "quit") break;
        
        if(tokens[0] == "create" && tokens.size() == 2) {
          if(!trains.count(tokens[1])) {
            try {
              trains[tokens[1]] = new Train(tokens[1]);  
            } catch(...) {}
          } else cout << "Train does already exist!" << endl;
        }
        
        if(tokens[0] == "board" && tokens.size() == 3) {
          if(trains.count(tokens[1])) {
            try {
              trains[tokens[1]]->addPassenger(tokens[2]);   
            } catch(...) {}
          } else cout << UNKNOWN_TRAIN << endl;
        }
        
        if(tokens[0] == "start" && tokens.size() == 2) {
          if(trains.count(tokens[1])) {
             if(trains[tokens[1]]->startTrain()) {
                trains.erase(tokens[1]); 
             }
          } else cout << UNKNOWN_TRAIN << endl;
        }
        
       
    }
    
    for(auto a : trains) {
      delete a.second;   
    }
    
    return 0;
}
