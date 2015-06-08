#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

// this is too slow 
//typedef std::vector<std::vector<int>> GRID;
//
//void overlay(GRID &grid, const int color, const int startx, const int starty,
//const int width, const int height){
//
//   for(int i=0; i<width; i++) {
//      for(int j=0; j<height; j++) {
//         grid[startx + i][starty + j] = color;
//      }
//   }
//}
// 
//void print (const GRID grid){
//
//   std::cout<<std::endl;
//   for(int i=0;i<grid[0].size();i++){
//      for(int j=0;j<grid.size();j++){
//	 std::cout<<grid[j][i];
//      }
//      std::cout<<std::endl;
//   }
//   std::cout<<std::endl;
//}
//
struct Rect {
    int col, sx, sy, ex, ey;
    bool isInside(int x, int y){
      return x>=sx && x <=ex && y>=sy && y <=ey;
    }
};

int main (int len, char * args[]){

   std::ifstream f(args[len-1]);
   std::vector<int> params( (std::istream_iterator<int>(f)), std::istream_iterator<int>() );

   int width = params[0];
   int height = params[1]; 
 
   std::vector<Rect> rects;
   for(int i=2; i<params.size(); i+=5){
     int c = params[i];
     int sx = params[i+1];
     int sy = params[i+2];
     int ex = params[i+1] + params[i+3] -1;
     int ey = params[i+2] + params[i+4] -1;
     rects.push_back({c, sx, sy, ex, ey});  
     //std::cout<<c<<" "<<sx<<" "<<sy<<" "<<ex<<" "<<ey<<std::endl;
   }

   std::cout<<rects.size()<<" rects."<<std::endl;
   
   std::vector<int> bins(11, 0);

   //#pragma omp parallel for
   for(int i=0;i<width;i++){
      std::cout<<i<<std::endl;
      for(int j=0;j<height;j++){
         int col = 0;
#pragma omp simd
         for(Rect r : rects){
            if(r.isInside(i, j)){
               col = r.col; 
            }
         }
         bins[col]++;
      }
   }
   
   for(int i=0;i<bins.size();i++){
      std::cout<<"Color "<<i<<": "<<bins[i]<<std::endl;
   }

   //GRID grid;

   //for(int i=0;i<width;i++){
   //   std::vector<int> tmp(height, 0);
   //   grid.push_back(tmp);
   //}

   //print(grid);
   //for(int i = 2; i<params.size(); i+=5){
   //	//overlay(grid, params[2], params[3], params[4], params[5], params[6]);
   //   overlay(grid, params[i], params[i+1], params[i+2], params[i+3], params[i+4]);
   //   print(grid);
   //}
}
