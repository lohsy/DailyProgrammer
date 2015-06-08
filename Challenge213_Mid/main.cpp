//finds the min effort required to type a sentence on a keyboard

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctype.h>
#include <limits>

struct Point {
public:
    int x,y;
    Point():x(0),y(0){}
    Point(int X, int Y):x(X), y(Y){}
};

struct Hand {
private:
    Point location;
    bool init; 
    std::string name;
    int effort;

int calculateEffort(const Point &pt){
    return abs(location.x - pt.x) + abs(location.y - pt.y);
}

bool isSamePoint(const Point &pt){
   return pt.x == location.x && pt.y == location.y;
}

public:
    Hand(std::string n):name(n){
      location.x=-1;
      location.y=-1;
      init = false;
      effort = 0;
    }

   std::string getCharName(const Point &pt, const std::vector<std::string> k){
      std::string s;

      if(k[pt.x][pt.y] == '#')
         s = "space";
      else if(k[pt.x][pt.y] == '^')
         s = "shift";
      else
         s = k[pt.x][pt.y];
      return s;
   }

   void move(const Point &pt, const std::vector<std::string> k){

      //if(isSamePoint(pt)) return;

      std::string curChar = getCharName(pt, k);
      int curEffort = 0; 
      if(!init){
        std::cout<<curChar<<": use "<<name<<" hand."<<"\t"<<curEffort<<"\t"<<pt.x<<","<<pt.y<<std::endl;
        init = true;
      } else {
      	std::string prevChar = getCharName(location, k);
        curEffort = calculateEffort(pt);
        std::cout<<curChar<<": Move "<<name<<" hand from "<<prevChar<<".\t"<<curEffort<<"\t"<<pt.x<<","<<pt.y<<std::endl;
        effort += curEffort;
      }
      location = pt;
      //int curEffort = 0;
      //std::string prevChar = getCharName(location, k);
      //int prevInit = init;

      //if(init) 
      //  curEffort = calculateEffort(pt);

      //location = pt;
      //if(location.x != -1 && location.y != -1)
      //   init = true;

      //std::string curChar = getCharName(pt, k);

      //effort += curEffort;

      //if(!prevInit) //first time
      //  std::cout<<": use "<<name<<" hand."<<"\t"<<curEffort<<std::endl;
      //else
      //  std::cout<<": Move "<<name<<" hand from "<<"\t"<<curEffort<<std::endl;
      ////std::cout<<": use "<<name<<" hand."<<"\t"<<effort<<"\t"<<location.x<<","<<location.y<<std::endl;
   }

   bool isInit(){
      return init;
   }

   Point getLoc(){
     return location;
   }
  
   int getEffort(){
     return effort;
   } 
};

std::vector<Point> getLocations(const std::vector<std::string> &k, const char &character){
 
    std::vector<Point> pts;

    char c = tolower(character);

    for(int i=0;i<k.size();i++){
       for(int j=0;j<k[i].size();j++){
          if(k[i][j] == c) pts.push_back(Point(i,j));
       }
    }

    return pts;
}

Point getLocation(const std::vector<std::string> &k, const char &character){
 
    char c = tolower(character);
    if(c == ' ') c = '#';

    for(int i=0;i<k.size();i++){
       for(int j=0;j<k[i].size();j++){
          if(k[i][j] == c) return Point(i,j);
       }
    }

    std::cout<<c<<" not found!"<<std::endl;
    return Point(-1,-1);
}

bool isNearLeft(const Point &loc, const std::vector<std::string> kb){
     return (loc.y-1) <= kb[0].size()/2;
}

int getEffort(const Point &s, const Point &e){
    return abs(s.x - e.x) + abs(s.y - e.y);
}

//alpha keys
void moveWithMinimalEffort(Hand &left, Hand &right, const Point &letterLoc,
const std::vector<std::string> kb){
     
     int effort = std::numeric_limits<int>::max();
     bool leftHand = false;

     int e = getEffort(right.getLoc(), letterLoc);
     if(e < effort){
        effort = e;
        leftHand = false;
     }
     e = getEffort(left.getLoc(), letterLoc);
     if(e < effort){
        effort = e;
        leftHand = true;
     }
     if(leftHand) left.move(letterLoc, kb);
     else  right.move(letterLoc, kb); 
}

//spaces
void moveWithMinimalEffort(Hand &left, Hand &right,
const std::vector<Point> &spaces, const std::vector<std::string> kb){
     int effort = std::numeric_limits<int>::max();
     Point whichSpace = right.getLoc();
     bool leftHand = false;

     for(Point s : spaces){
       int e = getEffort(left.getLoc(), s);
       //std::cout<<"["<<left.getLoc().x<<","<<left.getLoc().y<<"] to ["<<
       //s.x<<","<<s.y<<"] takes "<<e<<" effort."<<std::endl;
       if(e < effort){
          effort = e;
          leftHand = true;
          whichSpace= s;
       }
       e = getEffort(right.getLoc(), s);
       //std::cout<<"["<<right.getLoc().x<<","<<right.getLoc().y<<"] to ["<<
       //s.x<<","<<s.y<<"] takes "<<e<<" effort."<<std::endl;
       if(e < effort){
          effort = e;
          leftHand = false;
          whichSpace = s;
       }
     }
     if(leftHand) left.move(whichSpace, kb); 
     else right.move(whichSpace, kb); 
}

//shifts
void moveWithMinimalEffort(Hand &left, Hand &right, const Point &letterLoc,
const std::vector<Point> &shifts, const std::vector<std::string> kb){
     int effort = std::numeric_limits<int>::max();
     Point whichShift = left.getLoc();
     bool leftHandOnShift = false;

     for(Point s : shifts){
	int e = getEffort(left.getLoc(),s) + getEffort(right.getLoc(), letterLoc);
        if(e < effort){
           effort = e;
           leftHandOnShift = true;
           whichShift = s;
        }
	e = getEffort(right.getLoc(),s) + getEffort(left.getLoc(), letterLoc);
        if(e < effort){
           effort = e; 
           leftHandOnShift = false;
           whichShift = s; 
        }
     }
     if(leftHandOnShift){
        left.move(whichShift, kb); right.move(letterLoc, kb); 
     } else {
        right.move(whichShift, kb); left.move(letterLoc, kb);
     }
}

void move(Hand &left, Hand &right, const char &c, const std::vector<std::string> &kb,
const std::vector<Point> &spaces, const std::vector<Point> &shifts){

    Point letterLoc = getLocation(kb, c);
    if(isupper(c)){//needs shift key
      if(!left.isInit() && !right.isInit()){//all not init
	if(isNearLeft(letterLoc, kb)){//char is near left side keyboard
	   right.move(shifts.at(1), kb);
           left.move(letterLoc, kb);
        } else {
	   left.move(shifts.at(0), kb);
           right.move(letterLoc, kb);
        }    
      } // end if all not init
      else if(!left.isInit()){
	   left.move(shifts.at(0), kb);
           right.move(letterLoc, kb);
      }
      else if(!right.isInit()){
	   right.move(shifts.at(1), kb);
           left.move(letterLoc, kb);
      } else {
           moveWithMinimalEffort(left, right, letterLoc, shifts, kb);
      }
    } // end needs shift key
    else if(c == ' '){ // key = space
      if(!left.isInit()){
	   left.move(spaces.at(0), kb);
      }
      else if(!right.isInit()){
	   right.move(spaces.at(spaces.size()-1), kb);
      } else {
           moveWithMinimalEffort(left, right, spaces, kb);
      }     
    } // end key = space
    else {// default key
      if(!left.isInit() && !right.isInit()){//all not init
	if(isNearLeft(letterLoc, kb)){//char is near left side keyboard
           left.move(letterLoc, kb);
        } else { 
           right.move(letterLoc, kb);
        } // end if all not init
      } else if (!left.isInit()){
           left.move(letterLoc, kb);
      } else if(!right.isInit()){
           right.move(letterLoc, kb);
      } else {
           moveWithMinimalEffort(left, right, letterLoc, kb);
      }
    } //end default key
}

int main (int len, char * args []) {
  
    const char *letters [] = {"qwertyuiop",
                              "asdfghjkl ",
                              "^zxcvbnm ^",
                              "   #####  "};

    //const std::string message = "The quick brown Fox";
    std::cout<<"Enter string: "<<std::endl;
    std::string message;
    std::getline(std::cin, message);
 
    std::vector<std::string> keyboard(letters, letters+4);  
    std::vector<Point> spaces = getLocations(keyboard, '#');
    std::vector<Point> shifts = getLocations(keyboard, '^');
    
    Hand leftHand("left");
    Hand rightHand("right");
    int totalEffort = 0;
    
    std::cout<<message<<std::endl;
 
    for(int i=0;i<message.size();i++){
       move(leftHand, rightHand, message.at(i), keyboard, spaces, shifts); 
    }

   std::cout<<"Total Effort: "<<leftHand.getEffort() + rightHand.getEffort()<<std::endl;
    
}

