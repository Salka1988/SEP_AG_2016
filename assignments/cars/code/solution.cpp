#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>

class Car {
private:
    std::string color, brand;
    int speed;

public:
    Car(std::string config) {
        std::istringstream iss(config);
        std::vector <std::string> tokens{std::istream_iterator < std::string > {iss},
                                         std::istream_iterator < std::string > {}};
        if (tokens.size() != 3) {
            throw std::runtime_error("Wrong format");
        }

        brand = tokens[0];
        speed = std::stoi(tokens[1]);
        color = tokens[2];
    }

    bool operator==(const Car &other) const {
        return brand == other.brand && speed == other.speed;
    }

    bool operator<(const Car &other) const {
        return speed > other.speed;
    }

    friend std::ostream &operator<<(std::ostream &os, const Car &car);
};

std::ostream &operator<<(std::ostream &os, const Car &car) {
    os << car.brand << ": " << car.speed << " (" << car.color << ")";
    return os;
}

void sortCars(std::vector <Car> &cars) {
    std::sort(cars.begin(), cars.end());
}

void printCars(std::vector <Car> &cars) {
    for (auto c : cars) {
        std::cout << c << std::endl;
    }
}

void removeDuplicateCars(std::vector <Car> &cars) {
    std::sort(cars.begin(), cars.end());
    cars.erase(std::unique(cars.begin(), cars.end()), cars.end());
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <car file>" << std::endl;
        return 0;
    }

    std::vector <Car> cars;
    std::ifstream input(argv[1]);
    std::string line;

    while (std::getline(input, line)) {
        try {
            Car car(line);
            cars.push_back(car);
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }

    removeDuplicateCars(cars);
    printCars(cars);

    sortCars(cars);
    std::cout << std::endl;
    printCars(cars);

}