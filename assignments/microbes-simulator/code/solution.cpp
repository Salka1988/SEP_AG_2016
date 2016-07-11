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

class Microbe {
private:
    double count;
    double factor;
    std::string name;
public:
    Microbe() : count(0), factor(0) {}
    Microbe(std::string n, int c, double f) : name(n), count(c), factor(f) {}

    virtual void grow() = 0;

    void update(std::function<double(double, double)> f) {
        count = f(count, factor);
    }

    friend std::ostream &operator<<(std::ostream &os, const Microbe &m);
};

std::ostream &operator<<(std::ostream &os, const Microbe &m) {
    os << m.name << " (" << (int)m.count << ")";
    return os;
}



class Bacteria : public Microbe {
public:
    Bacteria(std::string name, int count, double factor) : Microbe(name, count, factor) {}

    void grow() {
        update([](double count, double factor) -> double { return count + factor; });
    }
};


class Virus : public Microbe {
public:
    Virus(std::string name, int count, double factor) : Microbe(name, count, factor) {}

    void grow() {
        update([](double count, double factor) -> double { return count * factor; });
    }
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <start file> <time>" << std::endl;
        return 0;
    }

    std::vector <Microbe*> microbes;
    std::ifstream input(argv[1]);
    std::string line;

    while (std::getline(input, line)) {
        try {
            std::istringstream iss(line);
            std::vector <std::string> tokens{std::istream_iterator < std::string > {iss},
                                             std::istream_iterator < std::string > {}};
            if (tokens.size() != 4) {
                throw std::runtime_error("Wrong format");
            }

            Microbe* m = nullptr;
            if(tokens[0] == "V") {
                m = new Virus(tokens[1], std::stoi(tokens[2]), std::stod(tokens[3]));
            } else if(tokens[0] == "B") {
                m = new Bacteria(tokens[1], std::stoi(tokens[2]), std::stod(tokens[3]));
            }
            if(m) microbes.push_back(m);
            else throw std::runtime_error("Wrong format");
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }

    int t = std::stoi(argv[2]);
    if(t > 0) {
        while (t--) {
            for (auto m : microbes) {
                m->grow();
            }
        }
    }
    for (auto m : microbes) {
        std::cout << *m << std::endl;
        delete m;
    }
}