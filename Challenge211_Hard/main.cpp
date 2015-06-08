#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


void getFreq(const std::vector<int> vec, std::vector<int> &freq) {
    for (int n : vec) {
      freq[n-1]++;
    }
}

void printVec(const std::vector<int> &v){
    for(auto n : v)
        std::cout<< n << " ";
    std::cout<<std::endl; 
}

void getPairsAndSingles(std::vector<int> &p, std::vector<int> &s, const std::vector<int> &v){

    std::vector<int> freq(*std::max_element(v.begin(), v.end()));
    getFreq(v, freq);

    for(int i=0;i<freq.size();i++){
      int pairs = freq[i]/2;
      int solos = freq[i]%2;
      
      for(int j=0;j<pairs;j++){
         p.push_back(i+1);
         p.push_back(i+1);
      }
      for(int j=0;j<solos;j++){
         s.push_back(i+1);
      }
    }

    //printVec(p);
    //printVec(s);

    std::sort(p.begin(), p.end(), std::greater<int>());

    //check
    if(s.size() < p.size()/2){
      //std::cout<<"Resizing pairs and solos!"<<std::endl;
      int count = std::count(p.begin(), p.end(), p[0]);
      //std::cout<<count<<std::endl;
      for(int i=0;i<count;i++){
        s.push_back(p[0]);
        p.erase(p.begin());
      }
      //s.push_back(p[0]);
      //s.push_back(p[0]);
      //p.erase(p.begin(), p.begin()+2);
    }

    std::sort(p.begin(), p.end(), std::greater<int>());
    std::sort(s.begin(), s.end(), std::greater<int>());

    //printVec(v);
    //printVec(p);
    //printVec(s);
}

void solve(std::vector<int> &best, std::vector<int> &p, std::vector<int> &s, int &index){

    //std::cout<<index<<std::endl;

    if(s.size() >= 1){
       if(p.size() >= 2){
          best[index] = s[0];
          s.erase(s.begin());
          index++;
       } else {
          std::sort(s.begin(), s.end());
          for(auto d : s){
             best[index] = d;
             index++;
          }
          return;
       }
       //std::cout<<"After single"<<std::endl;
       //printVec(best);
    }

    if(p.size() >= 2){
       best[index] = p[0];
       best[index+1] = p[1];
       p.erase(p.begin(), p.begin()+2);
       index+=2;
       //std::cout<<"After pair"<<std::endl;
       //printVec(best);
    }

    if(index >= best.size() || (p.size()==0 && s.size()==0)) return;
    else solve(best, p, s, index);
}

int getScore(const std::vector<int> &v){
 
    int score = 0;
    for(int i=0;i<v.size();i++){
       if(i==0){
         if(v[i] > v[i+1]) score++;
         else if(v[i] < v[i+1]) score--;  
       } else if(i==v.size()-1){
          if(v[i] > v[i-1]) score++;
          else if(v[i] < v[i-1]) score--;  
       } else {
          if(v[i]>v[i-1] && v[i]>v[i+1]) score++;
          else if(v[i]<v[i-1] && v[i]<v[i+1]) score--; 
       }
    }
    return score;
}

void checkLastElement(std::vector<int> &best){

    int min = *std::min_element(best.begin(), best.end());
    if(best.at(best.size()-1) == min && std::count(best.begin(), best.end(), min) == 1){
	//std::cout<<"is last!"<<std::endl;
        std::vector<int> tmp = best;
        int score=getScore(best);
        int index=-1;
        for(int i=0;i<tmp.size();i++){
           std::iter_swap(tmp.begin()+i, tmp.end()-1);
           //printVec(tmp);
           int tmpScore = getScore(tmp);
           std::iter_swap(tmp.begin()+i, tmp.end()-1); // swap back
           //std::cout<<"score: "<<tmpScore<<std::endl;
           if(tmpScore > score){
             score = tmpScore; 
             index = i;
           }
        }
        if(index!= -1){ 
           std::iter_swap(best.begin()+index, best.end()-1);
        }
    } 
}

int main(int len, char *c [])
{
    std::ifstream f(c[len-1]);

    std::vector<int> vec((std::istream_iterator<int>(f)), std::istream_iterator<int>());
    std::vector<int> best(vec.size());
    std::sort(vec.begin(), vec.end());

    std::cout<<"Original"<<std::endl;
    printVec(vec);

    std::vector<int> pair, single;
    getPairsAndSingles(pair, single, vec);
   
    int index=0;
    solve(best, pair, single, index);
    checkLastElement(best); 

    std::cout<<"Solution"<<std::endl;
    printVec(best);
    std::cout<<"Score: "<<getScore(best)<<std::endl;
}

