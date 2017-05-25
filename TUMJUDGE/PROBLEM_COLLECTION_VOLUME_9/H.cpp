#include<bits/stdc++.h>

using namespace std;

double l2(int x1, int y1, int x2, int y2){
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


int main(){

  int x[3], y[3];
  for(int i=0; i<3; ++i){
    cin >> x[i];
    cin >> y[i];
  }
  double measured_r;
  cin >> measured_r;

  double a, b, c;
  a = l2(x[0], y[0], x[1], y[1]);
  b = l2(x[1], y[1], x[2], y[2]);
  c = l2(x[2], y[2], x[0], y[0]);

  double A = 0.25 * sqrt(4*a*a*b*b - (a*a + b*b - c*c)*(a*a + b*b - c*c));
  double calculated_r = (2 * A)*1.0 / (a+b+c);

  cout << ((calculated_r - measured_r)*1.0/measured_r)*100.0 << "\n";

  return 0;
}
