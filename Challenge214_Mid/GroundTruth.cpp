#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
using namespace std;

int main() {
  int color = 0, x = 0, y = 0, w, h;
  cin >> w >> h;
  vector<int> xs, ys;
  struct Rect {
    int xmin, ymin, xmax, ymax, color;
  };
  vector<Rect> rects;
  do {
    xs.emplace_back(x);
    xs.emplace_back(x+w);
    ys.emplace_back(y);
    ys.emplace_back(y+h);
    rects.push_back({x, y, x+w, y+h, color});
  } while (cin >> color >> x >> y >> w >> h);
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());

  vector<int> image(xs.size()*ys.size());
  for (const auto& rect : rects) {
    int x_begin = lower_bound(xs.begin(), xs.end(), rect.xmin) - xs.begin();
    int x_end = lower_bound(xs.begin(), xs.end(), rect.xmax) - xs.begin();
    int y_begin = lower_bound(ys.begin(), ys.end(), rect.ymin) - ys.begin();
    int y_end = lower_bound(ys.begin(), ys.end(), rect.ymax) - ys.begin();
    for (int x = x_begin; x < x_end; ++x) {
      #pragma omp simd
      for (int y = y_begin; y < y_end; ++y) {
        image[x*ys.size()+y] = rect.color;
      }
    }
  }

  map<int, uint64_t> areas;
  for (int x = 0; x < xs.size()-1; ++x) {
    for (int y = 0; y < ys.size()-1; ++y) {
      areas[image[x*ys.size()+y]] += (xs[x+1]-xs[x]) * (ys[y+1]-ys[y]);
    }
  }
  for (const auto& area : areas) {
    cout << area.first << " " << area.second << endl;
  }
}
