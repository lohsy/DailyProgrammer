#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

//template <typename T>
//void convert (T t){
//   if(is_convertible<T, bool>::value)
//       //cout<<t<<" is convertible "<<(t ? "True" : "False")<<endl;
//       cout<<t<<" is convertible."<<endl;
//   else{
//       cout<<t<<" is not convertible."<<endl;
//   }
//}

template <typename T>
typename enable_if<is_convertible<T, bool>::value, T>::type
convert(T t) {
   cout<<t<<" is convertible "<<(t ? "True" : "False")<<endl;
}

template <typename T>
typename enable_if<!is_convertible<T, bool>::value, T>::type
convert(T t) {
   cout<<t<<" not is convertible "<<endl;
}

int main (){
  
   string a = "Hello World!";
   char b = ' ';
   char c= '0';
   int d = 1;
   int e = 0;
   double f = 0.0;
   int g [] = {};
   int h [] = {1,2,3};
   bool i = true;
   bool j = false;
 
   convert(a);
   convert(b);
   convert(c);
   convert(d);
   convert(e);
   convert(f);
   convert(g);
   convert(h);
   convert(i);
   convert(j);

}
