#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int main (int len, char * args[]){

    fstream f(args[len-1]);
    int num_wire, num_compare, w1, w2;
    f >> num_wire >> num_compare;
   
    vector<pair<int, int>> pairs;

    while(f >> w1 >> w2) {
       //cout << w1 << " " << w2 << endl;
       pair<int,int> tmp(w1,w2);
       pairs.emplace_back(tmp);
    }

    bool valid=true;
    vector<int> seq(num_wire, 0); 
   
    for(double i=0;i<pow(2,num_wire);i++){ 
       //get binary sequence
       double sum = i;
       for(int j=0;j<seq.size();j++){
          int t = pow(2, seq.size() - j -1);
          if(sum >= t){
             sum -= t;
             seq[j] = 1;
          }
       }
       
       //get ground truth  
       vector<int> gt(seq);
       sort(gt.begin(), gt.end());
 
       //sort network
       for(pair<int,int> p : pairs){
          if(seq[p.first] > seq[p.second]){
              int tmp = seq[p.first];
              seq[p.first] = seq[p.second]; 
              seq[p.second] = tmp; 
          }
       } 

       //verification
       int one [] = {1};
       int zero [] = {0};
       int it_seq0 = find_end(seq.begin(), seq.end(), zero, zero+1) - seq.begin();
       int it_seq1 = find_first_of(seq.begin(), seq.end(), one, one+1) - seq.begin();
       int it_gt0 = find_end(gt.begin(), gt.end(), zero, zero+1) - gt.begin();
       int it_gt1 = find_first_of(gt.begin(), gt.end(), one, one+1) - gt.begin();

       if(it_seq0 != it_gt0 || it_seq1 != it_gt1){     
          valid = false;
          break;
       } 
   
       for(int j=0;j<seq.size();j++) seq[j]=0;
    }
 
    if(valid)
        cout<<"Valid"<<endl;
     else 
        cout<<"Invalid"<<endl;
}
