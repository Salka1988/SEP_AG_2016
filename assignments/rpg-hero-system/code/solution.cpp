#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

class RPGHero
{
private:
  string name_;
  int level_;
  int current_XP_;
  int XP_to_next_level_;
  int calcXPFormula()
  {
    return exp(level_/2) + 10;
  }
public:
  RPGHero(string name) : name_(name), level_(1), current_XP_(0), XP_to_next_level_(0)
  {
    XP_to_next_level_ = calcXPFormula();
  }

  RPGHero() {};

  bool gainXP(int XP)
  {
    current_XP_ += XP;
    bool leveled_up = false;
    while (current_XP_ >= XP_to_next_level_)
    {
      current_XP_ -= XP_to_next_level_;
      level_++;
      XP_to_next_level_ = calcXPFormula();
      leveled_up = true;
    }

    return leveled_up;
  }

  string getName() const
  {
    return name_;
  }

  friend ostream& operator<<(ostream& os, const RPGHero& m);
};

ostream& operator<<(ostream& os, const RPGHero& m)
{
  os << m.name_ << " (Level " << m.level_ << ", " << m.current_XP_ << " / " << m.XP_to_next_level_ << " XP)";
  return os;
}

int main() {
  vector<RPGHero*> heroes;

  while (1) {
    cout << "> ";
    string command;
    getline(cin, command);
    if (cin.bad() || cin.eof()) break;

    if (command == "") continue;
    istringstream iss(command);
    vector <string> tokens{ istream_iterator < string > {iss}, istream_iterator < string > {} };

    if (tokens[0] == "quit") break;

    if (tokens[0] == "create" && tokens.size() == 2) {
      
        try {
          heroes.push_back(new RPGHero(tokens[1]));
        }
        catch (...) {}
    }

    if (tokens[0] == "show" && tokens.size() == 1) {
      for (auto h : heroes)
      {
        cout << *h << endl;
      }
      
    }

    if (tokens[0] == "gainXP" && tokens.size() == 2) {
      try {
        int xp_val = stoi(tokens[1]);
        
        for (auto h : heroes)
        {
          if (h->gainXP(xp_val))
          {
            cout << h->getName() <<  " leveled up!" << endl;

          }
          cout << *h << endl;
        }
        
        
      }
      catch (...) {}
      
    }


  }

  for (auto h : heroes)
    delete h;

  return 0;
}