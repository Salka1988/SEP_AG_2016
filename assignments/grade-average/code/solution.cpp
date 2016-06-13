#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;


class Subject
{
private:
	string name_;
	float grade_;

public:

	Subject(string name, float grade) : name_(name), grade_(grade)
	{
	}

	float getGrade()
	{
		return grade_;
	}

	string getName()
	{
		return name_;
	}

	friend ostream& operator<<(ostream& os, const Subject& s);
};

class Student
{
private:
	string name_;
	vector<Subject> subjects_;

public:
	Student(string name) : name_(name)
	{
		
	}

	Student() : name_("")
	{

	}

	const vector<Subject>& getSubjects() const
	{
		return subjects_;
	}

	void addSubject(string name, float grade)
	{
		subjects_.push_back(Subject(name, grade));
	}

	float calcGradeAverage()
	{
		float avg = 0.0f;
		for (auto subject : subjects_)
			avg += subject.getGrade();

		return avg / subjects_.size();
	}

	string getName() const
	{
		return name_;
	}


	friend ostream& operator<<(ostream& os, const Student& s);
};

ostream& operator<<(ostream& os, const Subject& s)
{
	os << s.name_ << ": " << s.grade_;
	return os;
}

ostream& operator<<(ostream& os, const Student& s)
{
	auto subjects = s.getSubjects();
	os << s.getName() << endl;
	for (auto subject : subjects)
		os << subject << endl;
	return os;
}

int main() {
	map<string, Student*> students;

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
					students[tokens[1]] = (new Student(tokens[1]));
				}
				catch (...) {}
		}

		if (tokens[0] == "add" && tokens.size() == 4) {

			try {
				students[tokens[1]]->addSubject(tokens[2], stof(tokens[3]));
			}
			catch (...) {}
		}

		if (tokens[0] == "show" && tokens.size() == 1) {
			for (auto s : students)
			{
				cout << *(s.second);
			}
			
		}

		if (tokens[0] == "average" && tokens.size() == 1) {
			try {
				
				
				for (auto s : students)
				{
					Student stud = *(s.second);
					cout << "Grade average of " << stud.getName() << ": " << stud.calcGradeAverage() << endl;
				}
				
				
			}
			catch (...) {}
			
		}


	}

	for (auto s : students)
	{
		delete (s.second);
	}

	return 0;
}
