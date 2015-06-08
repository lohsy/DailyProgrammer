#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

int main (int len, char * args []){

  std::ifstream f(args[len-1]);
  std::vector<int> vec((std::istream_iterator<int>(f)), std::istream_iterator<int>());

  int sum = 0;
  for_each(vec.begin(), vec.end(), [&](int i){sum+=i;});
  double mean = ((double)sum) / ((double)vec.size());
  
  double var = 0; 
  for_each(vec.begin(), vec.end(), [&](int i){var+=pow(i-mean,2);});
  double sd = sqrt( ((double)var) / ((double)vec.size()) );
 
  std::cout<<"Standard Deviation of ( ";
  for_each(vec.begin(), vec.end(), [](int i){std::cout<<i<<" ";});
  std::cout<<") = "<<sd<<"."<<std::endl;
}
