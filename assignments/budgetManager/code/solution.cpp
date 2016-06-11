#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <exception>
#include <stdexcept>
#include <limits>
#include <functional>

class Budget
{
private:
  std::string name_;
  int amount_;

public:
  Budget(std::string name, int amount) : name_(name), amount_(amount) {}  
  
  virtual std::string printBudget() = 0;

  int getAmount()
  {
  	return amount_;
  }

  std::string getName()
  {
  	return name_;
  }

  void setAmount(int amount)
  {
  	amount_ = amount;
  }

  void setName(std::string name)
  {
  	name_ = name;
  }
};

class Expense : public Budget
{
  private:
  public:
    Expense(std::string name, int amount) : Budget(name, amount) {}  
    std::string printBudget()
    {
      std::string output = "You spent " + std::to_string(this->getAmount()) + " on " + this->getName();
      return output;
    }
};

class Income : public Budget
{
  private:
  public:
    Income(std::string name, int amount) : Budget(name, amount) {}
    std::string printBudget()
    {
      std::string output = "You received " + std::to_string(this->getAmount()) + " from " + this->getName();
      return output;
    }
};

int main()
{
  std::vector <Budget*> budgets;
  
  while(1)
  {
    std::cout << "> ";
    std::string command;
    std::getline(std::cin, command);
    if(std::cin.bad() || std::cin.eof()) break;

    if(command == "") continue;
    std::istringstream iss(command);
    std::vector<std::string> tokens{std::istream_iterator <std::string> {iss}, std::istream_iterator <std::string> {}};

    if(tokens[0] == "quit") break;
    
    if(tokens[0] == "add")
    {
      if(tokens.size() != 4)
      {
        std::cout << "Wrong parameter count!" << std::endl;
      }
      else
      {
        Budget *b = nullptr;
        if(tokens[1] == "income")
        {
          b = new Income(tokens[2], std::stoi(tokens[3]));
        }
        else if(tokens[1] == "expense")
        {
          b = new Expense(tokens[2], std::stoi(tokens[3]));
        }
        if(b) budgets.push_back(b);
      }  
    }
    
    if(tokens[0] == "save" && tokens.size() >=2)
    {
      std::ofstream file;
      file.open(tokens[1]);
      int total = 0;
      for(auto m : budgets)
      {
        file << m->printBudget() << std::endl;
        total += m->getAmount();
      }
      file << "Total: " << total << std::endl;
      file.close();
    }
  }
  return 0;
}
