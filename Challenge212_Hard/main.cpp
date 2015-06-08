#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> maze;
string path;

class Point{
  public:
   int x,y;
   Point(int xx, int yy):x(xx), y(yy) {}

   bool operator==(const Point p) {
     return p.x == x && p.y == y;
   }

   bool operator!=(const Point p) {
     return p.x!=x || p.y !=y;
   }
};

class Path {
  public:
    Point start, end;
    Path(Point s, Point e):start(s), end(e) {}
};

void readMaze(const char * filename){

  int lines; 
  ifstream file(filename);
  file >> lines;
  cout<<"Lines: "<<lines<<endl;
 
  string s;
  getline(file,s); //move to next line

  for(int i=0;i<lines;i++){
    string s;
    getline(file, s);
    maze.push_back(s);
  }  
 
  cout<<"Maze: "<<endl; 
  for_each(maze.begin(), maze.end(), [](string s){cout<<s<<endl;}); 

  getline(file, path); //path
  cout<<"Path: "<<path<<endl;
}

void getSteps(int &steps, int &index){

   int len=0; 
   for(int i=index;i<path.size();i++){
      if(!isdigit(path[i]))
         break;
      len++;
   }
   string n = path.substr(index, len);
   steps = atoi(n.c_str());
   index +=len-1;
}

void generateNewInstructions(vector<Point> &insN, vector<Point> &insE, 
                          vector<Point> &insS, vector<Point> &insW){
   for(Point p : insN){
      Point e(p.y, -p.x);
      Point s(-p.x, -p.y);
      Point w(-p.y, p.x);
  
      insE.push_back(e);
      insS.push_back(s);
      insW.push_back(w);
   }
}

void getInstruction(vector<Point> &ins){
  //iterate over path
  enum Direction {NORTH, EAST, SOUTH, WEST};
  Direction d = NORTH;
  int steps;

  for(int i=0;i<path.size();i++) {
    if(isdigit(path[i])){
       Point p(0,0);
       getSteps(steps, i);
       cout<<steps<<endl; 
       switch(d) {
        case NORTH: p.x -= steps; break;
        case EAST: p.y += steps; break;
        case SOUTH: p.x += steps; break;
        case WEST: p.y -= steps; break;
      }
      ins.push_back(p);
    } else if (isalpha(path[i])){
      if(path[i]=='l') { //rotate left
        cout<<"Rotated left"<<endl;
        if(d == NORTH) 
          d = WEST;
        else 
          d = static_cast<Direction>(d-1);
      } else if(path[i]=='r') { //rotate right
        cout<<"Rotated right"<<endl;
        if(d == WEST) 
          d = NORTH;
        else 
          d = static_cast<Direction>(d+1);
      }
    } 
  }
}

void findDistance(int &x, int&y){
  //iterate over path
  x=0; y=0;
  enum Direction {NORTH, EAST, SOUTH, WEST};

  Direction d = NORTH;
  int steps;
  for(int i=0;i<path.size();i++) {

    if(isdigit(path[i])){
       getSteps(steps, i);
       cout<<steps<<endl; 
       switch(d) {
        case NORTH: x -= steps; break;
        case EAST: y += steps; break;
        case SOUTH: x += steps; break;
        case WEST: y -= steps; break;
      }
    } else if (isalpha(path[i])){
      if(path[i]=='l') { //rotate left
        cout<<"Rotated left"<<endl;
        if(d == NORTH) 
          d = WEST;
        else 
          d = static_cast<Direction>(d-1);
      } else if(path[i]=='r') { //rotate right
        cout<<"Rotated right"<<endl;
        if(d == WEST) 
          d = NORTH;
        else 
          d = static_cast<Direction>(d+1);
      }
    } 
  }
}

void findGoodSpots(vector<Point> &pts){

   for(int i=0;i<maze.size();i++){
     for(int j=0;j<maze[i].size();j++){
       if(maze[i][j] == ' '){
 	 Point p(i,j);
         pts.push_back(p);
       }
     }
   }
}

void findValidPaths2(vector<Path> &paths, vector<Point> &pts, const int &x, const int &y){

   //for(Point p : pts) {
   for_each(pts.begin(), pts.end(), [&](Point start){
     for(int i=0;i<4;i++){ 
       Point end(start.x, start.y);
       switch(i){
         //north
         case 0 : end.x += x; end.y += y; break;
         //east
         case 1 : end.x -= y; end.y -= x; break;
         //south
         case 2 : end.x -= x; end.y -= y; break;
         //west
         case 3 : end.x += y; end.y += x; break;
       }
       
       //cout<<start.x<<","<<start.y<<"  "<<end.x<<","<<end.y<<endl;
       vector<Point>::iterator it = find(pts.begin(), pts.end(), end);
       if(it != pts.end()) {
          Path newPath(start, end);
          paths.push_back(newPath);
       }
     }
 
   });
}

void findValidPaths(vector<Path> &paths, vector<Point> &pts, vector<Point> &ins){

  for(int i=0;i<pts.size();i++){
     int x = pts[i].x;
     int y = pts[i].y;
     bool pass = true;
     //cout<<"Point ["<<x<<","<<y<<"]"<<endl;

     for(int j=0;j<ins.size();j++){
     
       if(ins[j].x<0){
         for(int step=0;step>=ins[j].x;step--){
           //cout<<"neg x: "<<step<<" x:"<<step+x<<endl;
           //cout<<"try ["<<step+x<<","<<y<<"]"<<endl;
           if(step+x<0 || step+x>=maze.size() || maze[step + x][y]!=' '){
             //cout<<"fail"<<endl;
             pass = false;
             break;
           }
           //cout<<"pass"<<endl;
         }
       } else { 
         for(int step=0;step<=ins[j].x;step++){
           //cout<<"pos x: "<<step<<" x:"<<step+x<<endl;
           //cout<<"try ["<<step+x<<","<<y<<"]"<<endl;
           if(step+x<0 || step+x>=maze.size() || maze[step + x][y]!=' '){
             //cout<<"fail"<<endl;
             pass = false;
             break;
           }
           //cout<<"pass"<<endl;
         } 
       }
    
       if(pass){ 
         if(ins[j].y<0){
            for(int step=0;step>=ins[j].y;step--){
              //cout<<"neg y: "<<step<<" y:"<<step+y<<endl;
              //cout<<"try ["<<x<<","<<step+y<<"]"<<endl;
              if(step+y<0 || step+y>=maze[0].size() || maze[x][step + y]!=' '){
               //cout<<"fail"<<endl;
                pass = false;
                break;
              }
             //cout<<"pass"<<endl;
            }
         } else {   
            for(int step=0;step<=ins[j].y;step++){
              //cout<<"pos y: "<<step<<" y:"<<step+y<<endl;
              //cout<<"try ["<<x<<","<<step+y<<"]"<<endl;
              if(step+y<0 || step+y>=maze[0].size() || maze[x][step + y]!=' '){
               //cout<<"fail"<<endl;
                pass = false;
                break;
              }
             //cout<<"pass"<<endl;
            }
         }
       }
       if(!pass){
          //cout<<"inner fail"<<endl;
          break;
       }
       //cout<<"inner pass"<<endl;
       x += ins[j].x;
       y += ins[j].y;
     }

     if(pass){
        //cout<<"outer pass"<<endl;
        Point end(x,y);
        Path newPath(pts[i], end); 
        paths.push_back(newPath);
     } else {
       //cout<<"outer fail"<<endl;
    }
  }
}

int main (int len, char* args[]) {
  
  //read file
  cout<<"Maze file: "<<args[len-1]<<endl;
  readMaze(args[len-1]); 

  vector<Point> insN, insE, insS, insW;
  getInstruction(insN);
  generateNewInstructions(insN, insE, insS, insW);
  
  cout<<"Instructions North: "<<endl;
  for_each(insN.begin(), insN.end(), [](Point p){cout<<p.x<<" "<<p.y<<endl;});
  cout<<"Instructions East: "<<endl;
  for_each(insE.begin(), insE.end(), [](Point p){cout<<p.x<<" "<<p.y<<endl;});
  cout<<"Instructions South: "<<endl;
  for_each(insS.begin(), insS.end(), [](Point p){cout<<p.x<<" "<<p.y<<endl;});
  cout<<"Instructions West: "<<endl;
  for_each(insW.begin(), insW.end(), [](Point p){cout<<p.x<<" "<<p.y<<endl;});
  
  vector<Point> pts;
  findGoodSpots(pts);

  cout<<"Good spots: "<<endl; 
  for_each(pts.begin(), pts.end(), [](Point p){cout<<"["<<p.x<<","<<p.y<<"] ";});
  cout<<endl;

  vector<Path> goodPaths; 
  findValidPaths(goodPaths, pts, insN);
  findValidPaths(goodPaths, pts, insE);
  findValidPaths(goodPaths, pts, insS);
  findValidPaths(goodPaths, pts, insW);

  //int distx, disty;
  //findDistance(distx, disty);
  //cout<<"x,y: "<<distx<<" "<<disty<<endl;

  //vector<Point> pts;
  //findGoodSpots(pts);

  //cout<<"Good spots: "<<endl; 
  //for_each(pts.begin(), pts.end(), [](Point p){cout<<p.x<<" "<<p.y<<endl;});

  //vector<Path> goodPaths; 
  //findValidPaths(goodPaths, pts, distx, disty);
  //
  cout<<"Paths: "<<endl;
  for_each(goodPaths.begin(), goodPaths.end(), [](Path z){
    cout<<"From ["<<z.start.y<<","<<z.start.x<<"] to ["<<z.end.y<<","<<z.end.x<<"]"<<endl;});
}
