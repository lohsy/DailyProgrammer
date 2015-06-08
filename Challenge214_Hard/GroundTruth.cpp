#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

typedef std::pair<double, double> XY;

int main() {
    std::ifstream f("challenge3.txt");
    f.ignore(10, '\n');

    std::vector<XY> vec;
    double x, y;
    while (f >> x >> y)
        vec.emplace_back(x, y);

    XY pos = { 0.5f, 0.5f };
    double len = 0;

    while(!vec.empty()) {
        double min = 10;
        auto best = vec.begin(), it = vec.begin();
        for ( ; it != vec.end(); ++it) {
            auto dist = (it->first - pos.first)*(it->first - pos.first) + (it->second - pos.second)*(it->second - pos.second);
            if(dist < min) {
                min = dist;
                best = it;
            }
        }
        pos = *best;
        len += sqrt(min);

        std::swap(*best, vec.back());
        vec.pop_back();
    }
    std::cout << len << std::endl;
}
