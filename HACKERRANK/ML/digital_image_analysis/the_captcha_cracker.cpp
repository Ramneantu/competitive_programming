#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;

typedef vector<vector<vector<double> > > IRGB;
typedef vector<vector<vector<double> > > IGRAY;


IRGB read_rgb() {

  int r, c;
  cin >> r >> c;

  IRGB img;
  img.resize(r, vector<vector<double> > (c, vector<double>()));

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      string tok;
      cin >> tok;
      istringstream iss(tok);
      double v;
      while (iss >> v) {
        img[i][j].push_back(v);
        if (iss.peek() == ',') {
          iss.ignore();
        }
      }
    }
  }

  return img;
}


void print_img(IRGB& img) {

  for (auto& r : img) {
    for (auto &c : r) {
      cout << c[0] << "," << c[1] << "," << c[2] << " ";
    }
    cout << endl;
  }
}




//0.21 R + 0.72 G + 0.07 B.

int main () {


  auto img = read_rgb();

  cout << 30 << " " << 60 << endl;
  print_img(img);



  return 0;
}
