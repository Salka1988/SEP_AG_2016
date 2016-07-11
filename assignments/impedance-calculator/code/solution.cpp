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

class Impedance
{
private:
  int real_;
  int imag_;

public:
  virtual void setImpedance(int real, int imag) = 0;

  int getReal()
  {
  	return real_;
  }

  int getImag()
  {
  	return imag_;
  }

  void setReal(int real)
  {
  	real_ = real;
  }

  void setImag(int imag)
  {
  	imag_ = imag;
  }
};

class Resistor : public Impedance
{
  private:
  public:
    void setImpedance(int real, int imag)
    {
    	this->setReal(real);
    	this->setImag(0);
    }
};

class Capacitor : public Impedance
{
  private:
  public:
    void setImpedance(int real, int imag)
    {
      this->setReal(real);
      this->setImag(-imag);
    }
};

class Inductance : public Impedance
{
  private:
  public:
    void setImpedance(int real, int imag)
    {
      this->setReal(real);
      this->setImag(imag);
    }
};

int main(int argc, char *argv[])
{
  if (argc != 2) 
  {
    std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
    return 0;
  }

  std::vector <Impedance*> impedances;
  std::ifstream input(argv[1]);
  std::string line;

  while(std::getline(input,line))
  {
    try
    {
      std::istringstream iss(line);
      std::vector <std::string> tokens{std::istream_iterator < std::string > {iss}, std::istream_iterator < std::string > {}};
      if (tokens.size() != 3) 
      {
        throw std::runtime_error("Wrong format");
      }

      Impedance *imp = nullptr;
      if(tokens[0] == "R")
      {
        imp = new Resistor();
        imp->setImpedance(std::stoi(tokens[1]), std::stoi(tokens[2]));
      }
      else if(tokens[0] == "L")
      {
        imp = new Inductance();
        imp->setImpedance(std::stoi(tokens[1]), std::stoi(tokens[2]));
      }
      else if(tokens[0] == "C")
      {
        imp = new Capacitor();
        imp->setImpedance(std::stoi(tokens[1]), std::stoi(tokens[2]));      
      }

      if(imp) impedances.push_back(imp);
      else throw std::runtime_error("Wrong format");
    } 
    catch (std::exception e) 
    {
      std::cout << e.what() << std::endl;
    }
  }

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

    if(tokens[0] == "calculate" && tokens.size() >= 2)
    {
      int real;
      int imag;
      if(tokens[1] == "series")
      {

        for(auto imp : impedances)
        {
          real += imp->getReal();
          imag += imp->getImag();
          delete imp;
        }
        std::cout << "Z=" << real << "+j" << imag << std::endl;
      }
    }
  }
  return 0;
}