#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;



class Monster
{
private:
  string name_;
  int hp_;
public:
  Monster(string name, int hp) : hp_(hp), name_(name)
  {}

  bool doDamage(int damage)
  {
    hp_ -= damage;
    return hp_ <= 0;
  }

  bool isDead() const
  {
    return hp_ <= 0;
  }

  string getName() const
  {
    return name_;
  }

  friend ostream& operator<<(ostream& os, const Monster& m);
};

ostream& operator<<(ostream& os, const Monster& m)
{
  os << m.name_ << ":" << m.hp_;
  return os;
}
static bool removeMonsterPred(const Monster* m) 
{
  return m->isDead();
}

int main() {
  vector<Monster*> monsters;

  while (1) {
    cout << "> ";
    string command;
    getline(cin, command);
    if (cin.bad() || cin.eof()) break;

    if (command == "") continue;
    istringstream iss(command);
    vector <string> tokens{ istream_iterator < string > {iss}, istream_iterator < string > {} };

    if (tokens[0] == "quit") break;

    if (tokens[0] == "spawn" && tokens.size() == 3) {
      
        try {
          monsters.push_back(new Monster(tokens[1], stoi(tokens[2])));
        }
        catch (...) {}
    }

    if (tokens[0] == "list" && tokens.size() == 1) {
      for (auto m : monsters)
      {
        cout << *m << endl;
      }
    }

    if (tokens[0] == "damage" && tokens.size() == 2) {
      try {
        int damage_val = stoi(tokens[1]);
        for (auto m : monsters)
        {

          m->doDamage(damage_val);

          if (m->isDead())
          {
            cout << m->getName() << " is removed!" << endl;
          }
          
        }

        monsters.erase(std::remove_if(monsters.begin(), monsters.end(), removeMonsterPred), monsters.end());
      }
      catch (...) {}
      
    }


  }

  for (auto m : monsters)
    delete m;

  return 0;
}
