#include <iostream>
#include <list>
#include <array>

using std::cout;
using std::endl;

typedef std::array<std::array<char, 10>, 10> GameField;
typedef std::pair<int, int> Position;   // first -> x, second -> y
constexpr auto make_position = std::make_pair<int, int>;

class Snake
{
    std::list<Position> snake_;
  public:
    Snake()
    {
      // initial snake
      snake_.push_back(make_position(4, 3));
      snake_.push_back(make_position(3, 3));
      snake_.push_back(make_position(2, 3));
    }
    void draw(GameField &field) const
    {
      for(auto &snake_element : snake_)
        field[snake_element.second][snake_element.first] = 'O';
      field[snake_.front().second][snake_.front().first] = 'X';   // snake head
    }
    void move(GameField &field, int x, int y)
    {
      Position new_front = make_position(snake_.front().first + x, snake_.front().second + y);

      // check move against wall and check move back
      if(field[new_front.second][new_front.first] == '#' || new_front == *std::next(snake_.begin(), 1))
        return;

      snake_.pop_back();
      snake_.push_front(new_front);
    }
};

class Game
{
    GameField field_;
    Snake snake_;
  public:
    Game()
    {
      reDraw();
    }
    void run()
    {
      std::string line("");
      for(;line != "quit";)
      {
        reDraw();
        printField();

        cout << "sep> ";
        std::getline(std::cin, line);

        if(line == "r")
          snake_.move(field_, 1, 0);
        else if(line == "l")
          snake_.move(field_, -1, 0);
        else if(line == "u")
          snake_.move(field_, 0, -1);
        else if(line == "d")
          snake_.move(field_, 0, 1);
      }
    }
  private:
    void reDraw()
    {
      for(auto &line : field_) line.fill(' ');    // init field

      // draw borders
      field_.front().fill('#');
      field_.back().fill('#');
      for(auto &line : field_)
        line.front() = line.back() = '#';

      snake_.draw(field_);
    }
    void printField() const
    {
      for(auto &line : field_)
      {
        for(auto &element : line)
          cout << element << ' ';
        cout << endl;
      }
    }
};

int main(void)
{
  Game game;
  game.run();
}
