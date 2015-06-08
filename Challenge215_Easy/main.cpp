#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main (int len, char* args []){

  fstream f(args[len-1]);
  double base, num;
  f >> base >> num;
  cout<<base<<" "<<num<<endl;
  
  vector<double> list;
  while(true){
     double sum=0;
     while(num!= 0){
       double tmp = floor(num/10) * 10;
       sum += pow(num - tmp, base);
       num = tmp/10;
       //cout<<sum<<" "<<num<<endl;
     }
     vector<double>::iterator it = find(list.begin(), list.end(), sum);
     if( it == list.end()){ //cannot find
    	 list.push_back(sum);
     } else {
         //cout<<endl<<sum<<" "<<*it<<endl;
         for(vector<double>::iterator i = it; i<list.end(); i++){
            cout<<fixed<<setprecision(0)<<*i<<" ";
            //printf("%s ", *i);
         }
         cout<<endl;
         break;
     }
     //cout<<sum<<endl;
     num = sum;
  }
}

