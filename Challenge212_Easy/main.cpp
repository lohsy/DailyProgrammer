#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>

int main (){

  std::string consonant = "bcdfghjklmnpqrstvwxz";
  std::string input = "Jag talar Rövarspråket!";
  std::string encoded;
  //std::string input;
  //std::getline(std::cin, input);
 
  std::cout<<input<<std::endl;
  std::cout<<"Encode"<<std::endl; 

  for(int i=0;i<input.length();i++){
    if(consonant.find(char(tolower(input[i])))!=std::string::npos){
       std::cout<<input[i]<<"o"<<(char)tolower(input[i]);
       encoded += input[i];
       encoded += "o";
       encoded += (char)tolower(input[i]);
    } else { // else
       std::cout<<input[i];
       encoded += input[i];
    }
  }

  std::cout<<std::endl;
  std::cout<<"Decode"<<std::endl;
 
  for(int i=0;i<encoded.length();i++){

    if(i+2 >= encoded.length()){
	std::cout<<encoded.at(i); 
        break;
    }

    char x = tolower(encoded.at(i));
    char y = tolower(encoded.at(i+2));
    if(x == y){
        std::cout<<encoded.at(i);
        i+=2;
    } else {
        std::cout<<encoded.at(i);
    }
  } 
 
  std::cout<<std::endl;
}
