#include <iostream>
#include <array>
#include <sstream>
#include <ctime>
#include <algorithm>

using std::cout;
using std::endl;

typedef std::pair<unsigned int, unsigned int> Position;   // first -> x, second -> y
constexpr Position GAMEFIELD_SIZE(3,3);
typedef std::array<std::array<char, GAMEFIELD_SIZE.first>, GAMEFIELD_SIZE.second> GameField;

class Game
{
    GameField field_;
  public:
    Game()
    {
      for(auto &line : field_) line.fill(' ');    // init field
    }
    void run()
    {
      std::string line;
      for(;;)
      {
        printField();

        cout << "sep> ";
        std::getline(std::cin, line);
        if(line == "quit") break;

        std::stringstream stream(line);
        Position pos;
        if(stream >> pos.first && stream >> pos.second &&
          pos.first < GAMEFIELD_SIZE.first && pos.second < GAMEFIELD_SIZE.second)
        {
          setTile(pos, 'X');
        }
        else
          cout << "Error: Invalid coordinate, use: <x y>." << endl;
      }
    }
  private:
    void setTile(const Position &position, const char tile)
    {
      if(countFreeFields() == 0)
      {
        cout << "Error: Field is full!" << endl;
        return;
      }
      else if(field_[position.second][position.first] != ' ')
      {
        cout << "Error: Cannot set Tile on occupied Field!" << endl;
        return;
      }
      field_[position.second][position.first] = tile;
      setRandomTile('O');
    }
    void setRandomTile(const char tile)
    {
      if(countFreeFields() == 0) return;
      Position rand_pos;
      do
      {
        rand_pos = {rand() % GAMEFIELD_SIZE.first, rand() % GAMEFIELD_SIZE.second};
      }while(field_[rand_pos.second][rand_pos.first] != ' ');
      field_[rand_pos.second][rand_pos.first] = tile;
    }
    int countFreeFields() const
    {
      int free_fields = 0;
      for(auto &line : field_)
        free_fields += std::count(line.begin(), line.end(), ' ');
      return free_fields;
    }
    void printField() const
    {
      for(auto &line : field_)
      {
        for(auto &element : line)
          cout << "----";
        cout << "-" << endl;
        for(auto &element : line)
          cout << "| " << element << " ";
        cout << "|" << endl;
      }
      for(auto &element : field_[0])
        cout << "----";
      cout << "-" << endl;
    }
};

int main(void)
{
  std::srand(std::time(0));
  Game game;
  game.run();
}
