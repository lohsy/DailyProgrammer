#include <iostream>
#include <fstream>

int main (int len, char * args []) {

  std::ifstream file("sample.txt");
  std::string line;

  while(std::getline(file, line)){
    
    std::cout<<line<<std::endl;

    int maxSum = 0;
    int maxJ = 1, maxS = 0, maxE = 1;

    //start end jump
    for(int jump = 1; jump < line.size()/2; jump++){ 
      for(int start = 0; start <line.size()-jump; start++){ 
        for(int end = start+jump; end <line.size(); end++){
           if((end-start)/jump < maxSum) continue;
           int sum = 0;
           for(int i=start;i<=end;i+=jump){
             //std::cout<<line.at(i);
             line.at(i) == 'a' ? sum++ : sum--;
           }
           //std::cout<<std::endl;
           sum = abs(sum);
           //std::cout<<"Sum: "<<sum<<std::endl;
           if(sum > maxSum){
             maxSum = sum; 
             maxJ = jump;
             maxS = start;
             maxE = end;
           }
        }
      }
    } 

    std::cout<<"Max sum: "<<maxSum<<"\t"<<"["<<maxS<<":"<<maxE<<":"<<maxJ<<"]"<<std::endl;
  }
}
