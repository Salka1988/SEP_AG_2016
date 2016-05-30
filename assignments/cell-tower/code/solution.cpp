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

class CellTower {
private:
    double lat, lng;
    std::string provider;
    double dist;

public:
    CellTower(std::string config) {
        std::istringstream iss(config);
        std::vector <std::string> tokens{std::istream_iterator < std::string > {iss},
                                         std::istream_iterator < std::string > {}};
        if (tokens.size() != 3) {
            throw std::runtime_error("Wrong format");
        }

        lat = std::stod(tokens[0]);
        lng = std::stod(tokens[1]);
        provider = tokens[2];
        dist = 0;
    }

    void calculateDistance(double latitude, double longitude, std::string prov) {
        if(provider != prov) {
            dist = std::numeric_limits<double>::max();
        } else {
            dist = (latitude - lat) * (latitude - lat) + (longitude - lng) * (longitude - lng);
        }
    }

    bool operator<(CellTower& other) {
        return dist < other.dist;
    }

    bool operator==(std::string prov) {
        return prov == provider;
    }

    friend std::ostream &operator<<(std::ostream &os, const CellTower &tower);
};

std::ostream &operator<<(std::ostream &os, const CellTower &tower) {
    os << tower.provider << " (" << tower.lat << ", " << tower.lng << ")";
    return os;
}


int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cout << "Usage: " << argv[0] << " <cell-file> <latitude> <longitude> <provider>" << std::endl;
        return 0;
    }

    std::string provider = std::string(argv[4]);
    double lat, lng;
    try {
        lat = std::stod(argv[2]);
        lng = std::stod(argv[2]);
    } catch(std::exception e) {
        std::cout << "Invalid parameters" << std::endl;
        return 0;
    }

    std::vector <CellTower> towers;
    std::ifstream input(argv[1]);
    std::string line;

    while (std::getline(input, line)) {
        try {
            CellTower tower(line);
            tower.calculateDistance(lat, lng, provider);
            towers.push_back(tower);
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::sort (towers.begin(), towers.end());

    for (auto t : towers) {
        if(t == provider) {
            std::cout << t << std::endl;
            break;
        }
    }

}