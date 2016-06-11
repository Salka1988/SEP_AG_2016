#include <iostream>
#include <random>
#include <string>


class RandomGuesser
{
public:

	enum CLOSENESS
	{
		eMuchTooHigh,
		eTooHigh,
		eMatch,
		eTooLow,
		eMuchTooLow,
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
		case eMuchTooHigh:
			return "Much too high!";
		case eMuchTooLow:
			return "Much too low!";
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

	CLOSENESS operator()(int guessed)
	{
		++num_guesses_;

		if ((num_guesses_ >= max_guesses_) && max_guesses_ != 0)
			return eNumGuessesExceeded;

		if (guessed == random_num_)
			return eMatch;
		if (guessed > max_)
			return eMuchTooHigh;
		if (guessed < min_)
			return eMuchTooLow;
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

int main()
{
	int min = 0;
	int max = 0;
	int max_guesses = 0;

	std::cout << "::: Random Number Guesser :::" << std::endl;
	std::cout << "Please enter the minimum value: ";
	std::cin >> min;

	std::cout << "Please enter the maximum value: ";
	std::cin >> max;

	std::cout << "Please enter the maximum guesses (0 for unlimited): ";
	std::cin >> max_guesses;
	std::cout << std::endl;

	if (min >= max)
	{
		std::cout << "The minimum value must be smaller than the maximum value!" << std::endl;
		return 0;
	}

	RandomGuesser game(min, max, max_guesses);

	RandomGuesser::CLOSENESS state = RandomGuesser::eUndefined;
	while (state != RandomGuesser::eMatch && state != RandomGuesser::eNumGuessesExceeded)
	{
		int number = 0;
		std::cout << "Guess a number between " << game.getMin() << " and " << game.getMax();
		
		if (game.getMaxGuesses() != 0)
			std::cout << ", " << game.getMaxGuesses() - game.getNumGuesses() << " guesses remaining: ";
		else
			std::cout << ": ";

		std::cin >> number;

		state = game(number);

		std::cout << game.getStringForState(state) << std::endl;
	}


	return 0;

}