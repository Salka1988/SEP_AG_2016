#include <iostream>
#include <random>
#include <string>
#include <fstream>


class RandomGuesser
{
public:

	enum CLOSENESS
	{
		eTooHigh,
		eMatch,
		eTooLow,
		eNumGuessesExceeded,
		eUndefined
	};


	RandomGuesser(int min, int max, int max_guesses = 100)
		: max_(max)
		, min_(min)
		, num_guesses_(0)
		, max_guesses_(max_guesses)
	{
		std::default_random_engine  random_engine;
		std::uniform_int_distribution<int> dist(min_, max_);
		random_num_ = dist(random_engine);
	}

	RandomGuesser(std::string filename)
	{
		std::fstream file("testfile.cfg");
		file >> min_ >> max_ >> max_guesses_;
		file.close();

		std::default_random_engine  random_engine;
		std::uniform_int_distribution<int> dist(min_, max_);
		random_num_ = dist(random_engine);
	}

	int getMax() const
	{
		return max_;
	}

	int getMin() const
	{
		return min_;
	}

	int getMaxGuesses() const
	{
		return max_guesses_;
	}

	int getNumGuesses() const
	{
		return num_guesses_;
	}

	std::string getStringForState(CLOSENESS state)
	{
		switch (state)	
		{
		case eMatch:
			return "Congratulations, you have guessed the number!";
		case eTooHigh:
			return "Too high!";
		case eTooLow:
			return "Too low!";
		case eNumGuessesExceeded:
			return "Number of maximum guesses exceeded!";
		case eUndefined:
			return "Undefined game state!";
		default:
			return "State value unknown!";
		}

	}

	CLOSENESS takeGuess(int guessed)
	{
		++num_guesses_;

		if ((num_guesses_ >= max_guesses_) && max_guesses_ != 0)
			return eNumGuessesExceeded;

		if (guessed == random_num_)
			return eMatch;
		if (guessed < random_num_)
			return eTooLow;
		if (guessed > random_num_)
			return eTooHigh;

		return eUndefined;
	}

private:

	int max_;
	int min_;
	int random_num_;
	int num_guesses_;
	int max_guesses_;

};

int main(int argc, char ** argv)
{
	RandomGuesser * game;

	if (argc == 2)
		game = new RandomGuesser(argv[1]);

	else if (argc == 4)
		game = new RandomGuesser(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

	else
	{
		std::cout << "Wrong usage" << std::endl;
		return 0;
	}

	RandomGuesser::CLOSENESS state = RandomGuesser::eUndefined;
	while (state != RandomGuesser::eMatch && state != RandomGuesser::eNumGuessesExceeded)
	{
		int number = 0;
		std::cout << "Guess a number between " << game->getMin() << " and " << game->getMax();
		
		if (game->getMaxGuesses() != 0)
			std::cout << ", " << game->getMaxGuesses() - game->getNumGuesses() << " guesses remaining: ";
		else
			std::cout << ": ";

		std::cin >> number;

		state = game->takeGuess(number);

		std::cout << game->getStringForState(state) << std::endl;
	}

	return 0;

}