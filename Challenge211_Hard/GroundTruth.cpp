#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main(int len, char *c [])
{
    std::ifstream f(c[len-1]);

    std::vector<int> vec((std::istream_iterator<int>(f)), std::istream_iterator<int>());
    std::vector<int> best(vec.size());
    std::sort(vec.begin(), vec.end());

    for(auto n : vec)
        std::cout << n << " ";
    std::cout << "\n";

    int max = 0;
    do{
        int sum = 0;
        if(vec[0] != vec[1])
            sum += vec[0] > vec[1] ? 1 : -1;

        if(vec[vec.size() - 2] != vec[vec.size() - 1])
            sum += vec[vec.size() - 2] < vec[vec.size() - 1] ? 1 : -1;

        for(int i = 1; i < vec.size() - 1; ++i){
            if(vec[i-1] < vec[i] && vec[i+1] < vec[i])
                sum++;
            else if (vec[i-1] > vec[i] && vec[i+1] > vec[i])
                sum--;
        }

        if(sum > max) {
            max = sum;
            std::copy(vec.begin(), vec.end(), best.begin());
        }

    } while(std::next_permutation(vec.begin(), vec.end()));

    std::cout << max << "\n";
    for(auto n : best)
        std::cout << n << " ";
    std::cout << "\n";
}
