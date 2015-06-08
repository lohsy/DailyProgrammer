#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct Point {
  double x,y;
};

double getDistance(Point a, Point b){
  return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));
}

double getDistanceNoSquare(Point a, Point b){
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void getNearestTreat(double &distance_travelled, Point &dog, vector<Point> &treats) {

   double distance = 100000;
   int index;
   for(int i=0; i<treats.size(); i++){
     double cur_distance = getDistanceNoSquare(dog, treats[i]);
     if(cur_distance < distance) { 
        distance = cur_distance;
        index = i;
     }
   } 

   distance_travelled += sqrt(distance);
   dog.x = treats[index].x;
   dog.y = treats[index].y;
   treats.erase(treats.begin()+index); 
   //cout<<dog.x<<" "<<dog.y<<endl;
}

int main (int len, char * args []){

   int num_treats;
   cin >> num_treats;

   cout<<"Treats: "<<num_treats<<endl;
 
   vector<Point> t;

   for(int i=0; i<num_treats; i++){
     double x,y;
     cin >> x >> y;
     t.push_back({x,y});
     //cout<<t[i].x<<" "<<t[i].y<<endl;
   }

   Point dog({0.5,0.5});

   //start
   double distance_travelled = 0;
   for(int i=0; i<num_treats; i++){
      getNearestTreat(distance_travelled, dog, t);
   }
 
   cout<<"Distance travelled: "<<distance_travelled<<endl;
}
