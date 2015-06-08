#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
string n1 [] = {"", "Eleventy", "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
string h1 [] = {"Atta", "Bibbity", "City", "Dickety", "Ebbity","Fleventy"};
string n2 [] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
string h2 [] = {"Aee", "Bee", "Cee", "Dee", "Eee", "Fee"};
string ten = "bitey ";

string getWord(char c1, char c2){
  string s;

  if(c1 == '0') return isalpha(c2) ? h2[c2 - 'A'] : n2[c2 - '0'];
  else if(c2 == '0') return isalpha(c1) ? h1[c1 - 'A'] : n1[c1 - '0'];
  else {
    isalpha(c1) ? s += h1[c1 - 'A'] : s+= n1[c1 - '0'];
    if(c2 != '0')
      isalpha(c2) ? s += "-" + h2[c2 - 'A'] : s+= "-" + n2[c2 - '0'];
    return s; 
  }
}

string getWord(char c1){
  string s;
  isalpha(c1) ? s += h1[c1 - 'A'] : s+= n1[c1 - '0'];
  return s; 
}

bool checkHex(string s){

   if(s[0] != '0' || s[1] != 'X') return false;
 
   for(int i=2;i<s.size();i++){
     if(!(s[i] == '0' || s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || 
        s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9' || 
        s[i] == 'A' || s[i] == 'B' || s[i] == 'C' || s[i] == 'D' || s[i] == 'E' || 
        s[i] == 'F')) return false;
   }
   return true;
}

int main(){
  int len = 14;
  string samples [] = {"0xF5", "0XB3", "0xE4", "0xBBBB", "0xA0C9",
     "0xB010", "0xFFFF", "0xD00D", "0x10", "0xabcd", "0x0", "0x1111",
     "0xAAA", "0xP00P" };
  
  for(int i=0;i<len;i++){
    string sample = samples[i];
    transform(sample.begin(), sample.end(), sample.begin(), ::toupper);
  
    if(!checkHex(sample)){
       cout<<sample<<" not hex"<<endl;
       continue;
    }
 
    string out;
    int count = 0;
    for(int i=sample.size()-1; i>=2; i-=2){
       if(count > 0) {
         if(sample[i] == '0') out.insert(0, "-" + ten);
         else out.insert(0, " " + ten);
       }

       if(i-1 == 1){ 
         out.insert(0, getWord(sample[i]));
       } else {
         out.insert(0, getWord(sample[i-1], sample[i]));
       }
  
       count++;
    }
 
    if(out.size() == 0) out = "Zero";
    transform(out.begin()+1, out.end(), out.begin()+1, ::tolower);
    cout<<sample<<"->"<<out<<endl;
  }
}
