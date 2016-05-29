#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

const string UNKNOWN_FLIGHT = "Flight does not exist!";
const string SEAT_NOT_OCCUPIED = "Seat not occupied!";
const string FULLY_BOOKED = "Flight fully booked!";

class Flight {
private:
    string flight_number_;
    map<int, string> passengers_;
    int max_passengers_;
    int cur_seat_number_;
public:
    Flight(string flight_number, int max_passengers) : 
    flight_number_(flight_number), max_passengers_(max_passengers), cur_seat_number_(1) {}
    
    void addPassenger(string passenger) {
      if(passengers_.size() < max_passengers_)
        passengers_[cur_seat_number_++] = passenger;
      else 
        cout << FULLY_BOOKED << endl;
    }
    
    void removePassengerFromSeat(int seat_number) {
    
      if(passengers_.count(seat_number)) {
        passengers_.erase(seat_number);
      } else cout << SEAT_NOT_OCCUPIED << endl;
    }
    
    
    void listPassengers() {
      for(auto p: passengers_) {
        cout << p.first << ": " << p.second << endl;
      }
    }
    
  //  double getCost() { return cost; }
  //  string getName() { return name; }
};

int main() {
    map<string, Flight*> flights;
    
    while(1) {
        cout << "> ";
        string command;
        getline(cin, command);
        if (cin.bad() || cin.eof()) break;

        if (command == "") continue;
        istringstream iss(command);
        vector <string> tokens{istream_iterator < string > {iss}, istream_iterator < string > {}};
        
        if(tokens[0] == "quit") break;
        
        if(tokens[0] == "create" && tokens.size() == 3) {
          try {
          }catch(...) {}
          
          if(!flights.count(tokens[1])) {
            try {
              flights[tokens[1]] = new Flight(tokens[1], std::stoi(tokens[2]));  
            } catch(...) {}
          } else cout << "Flight does already exist!" << endl;
        }
        
        if(tokens[0] == "book" && tokens.size() == 3) {
          if(flights.count(tokens[1])) {
            try {
              flights[tokens[1]]->addPassenger(tokens[2]);   
            } catch(...) {}
          } else cout << UNKNOWN_FLIGHT << endl;
        }
        
        if(tokens[0] == "takeoff" && tokens.size() == 2) {
          if(flights.count(tokens[1])) {
             flights[tokens[1]]->listPassengers();  
             flights.erase(tokens[1]); 
          } else cout << UNKNOWN_FLIGHT << endl;
        }
        
        if(tokens[0] == "cancel" && tokens.size() == 3) {
          if(flights.count(tokens[1])) {
            try {
              flights[tokens[1]]->removePassengerFromSeat(std::stoi(tokens[2]));   
            }catch(...) {
              cout << "No valid seat number!" << endl; 
            }
          } else cout << UNKNOWN_FLIGHT << endl;
        }
    }
    
    for(auto a : flights) {
      delete a.second;   
    }
    
    return 0;
}
