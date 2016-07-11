#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

class Spaceship
{
public:
	Spaceship(std::string name, float hitpoints, float speed)
		: hitpoints_(hitpoints)
		, speed_(speed)
		, name_(name)
	{
	}

	Spaceship(const Spaceship & other) = delete;
	void operator=(const Spaceship & other) = delete;
        virtual ~Spaceship() {}

	virtual void print() = 0;

	float getHitpoints() const { return hitpoints_; }
	float getSpeed() const { return speed_; }

protected:
	float hitpoints_;
	float speed_;
	std::string name_;
};

class Battleship : public Spaceship
{
public:
	Battleship(std::string name, float hitpoints, float speed, float weapons_power)
		: Spaceship(name, hitpoints, speed)
		, weapons_power_(weapons_power)
	{
	}

	float getWeaponsPower() const { return weapons_power_; }

	Battleship(const Battleship & other) = delete;
	void operator=(const Battleship & other) = delete;

	void print()
	{
		std::cout << "Battleship: " << name_ << std::endl;
		std::cout << "Hitpoints: " << hitpoints_ << std::endl;
		std::cout << "Speed: " << speed_ << std::endl;
		std::cout << "Weapons Power: " << weapons_power_ << std::endl << std::endl;
	}

protected:
	float weapons_power_;
};

class Freightship : public Spaceship
{
public:
	Freightship(std::string name, float hitpoints, float speed, float capacity)
		: Spaceship(name, hitpoints, speed)
		, capacity_(capacity)
	{
	}

	float getCapacity() const { return capacity_; }

	Freightship(const Freightship & other) = delete;
	void operator=(const Freightship & other) = delete;

	void print()
	{
		std::cout << "Freightship: " << name_ << std::endl;
		std::cout << "Hitpoints: " << hitpoints_ << std::endl;
		std::cout << "Speed: " << speed_ << std::endl;
		std::cout << "Capacity: " << capacity_ << std::endl << std::endl;
	}

protected:
	float capacity_;
};

int main()
{
	std::vector<Spaceship*> spaceships;

	while (1) 
	{
		std::cout << "> ";
		std::string command;
		std::getline(std::cin, command);
		if (std::cin.bad() || std::cin.eof()) break;

		if (command == "") continue;
		std::istringstream iss(command);
		std::vector<std::string> tokens{ std::istream_iterator < std::string > {iss}, std::istream_iterator < std::string > {} };

		if (tokens[0] == "quit") break;

		if (tokens[0] == "add" && tokens.size() == 6) {
			if (tokens[1] == "battleship") 
					spaceships.push_back(new Battleship(tokens[2], atof(tokens[3].c_str()), atof(tokens[4].c_str()), atof(tokens[5].c_str())));

			if (tokens[1] == "freightship")
				spaceships.push_back(new Freightship(tokens[2], atof(tokens[3].c_str()), atof(tokens[4].c_str()), atof(tokens[5].c_str())));
		}

		if (tokens[0] == "list" && tokens.size() == 1) {
			for (auto ship : spaceships){
				ship->print();
			}
		}
	}

	for (auto a : spaceships) {
		delete a;
	}

	return 0;

}