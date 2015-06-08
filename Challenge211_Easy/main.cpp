#include <iostream>
#include <string>

std::string firstLine (char x, std::string y){
  if(x == 'B')
    return x + y + ", " + x + y + " bo Bo" + y + ",";
  else 
    return x + y + ", " + x + y + " bo B" + y + ",";
}

std::string secondLine (char x, std::string y){
  if(x == 'F')
    return "Bonana fanna fo Fo" + y + ",";
  else
    return "Bonana fanna fo F" + y + ",";
}

std::string thirdLine (char x, std::string y){
  if(x == 'M')
    return "Fee fy mo Mo" + y + ",";
  else
    return "Fee fy mo M" + y + ",";
}

int main () {

  //read name as string
  //std::string name = "Lincoln!";
  //std::string name = "Nick!";
  std::string name;
  getline(std::cin, name);

  //split name to 1st letter and the rest of the chars (without !)
  char first = name.at(0);
  std::string rest = name.substr(1, name.size()-2);

  //generate each line
  std::cout<<firstLine(first, rest)<<std::endl;
  std::cout<<secondLine(first, rest)<<std::endl;
  std::cout<<thirdLine(first, rest)<<std::endl;
  std::cout<<name<<std::endl;

}
