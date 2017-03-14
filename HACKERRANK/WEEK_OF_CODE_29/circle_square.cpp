#include <cassert>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <queue>
#include <cmath>


using namespace std;
#define DEBUG 0
#define DBG(code){ if(DEBUG) do{ code }while(0); }


double l2(int x0, int y0, int x1, int y1){
  return sqrt((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1));
}

int di[] = {-1,0,1,0};
int dj[] = {0,1,0,-1};
int h,w;

inline bool valid(vector<vector<int> >& M, int i, int j){
  return (i>=0 && i<M.size() && j>=0 && j<M[0].size());
}
inline void putpixel(vector<vector<int> >& M, int x, int y, int v){
  if(valid(M, y, x)){
    DBG(cout << x << "," << y << endl;)
    M[y][x] = v;
  }
}

void fill(vector<vector<int> >& M, int i, int j, int v){
  if(M[i][j] == v)
    return;
  M[i][j] = v;
  for(int k=0; k<4; ++k)
    if(valid(M, i+di[k], j+dj[k]))
      fill(M,i+di[k], j+dj[k],v);
}


void draw_circle(vector<vector<int> >& M, int x0, int y0, int radius)
{
  DBG(cout << "circle:\n";)
  int x = radius;
  int y = 0;
  while (x >= y)
  {
    double d1 = l2(x-1+x0, y+y0, x0, y0);
    double d2 = l2(x+x0, y+y0, x0, y0);

    double e1 = fabs(d1-radius);
    double e2 = fabs(d2-radius);

    if(e1 < e2){
    //if((x*x + y*y - radius*radius)>0){
      x--;
    }
    else if(d2 > radius){
      x--;
    }

      putpixel(M, x0 + x, y0 + y,1);
      putpixel(M, x0 + y, y0 + x,1);
      putpixel(M, x0 - y, y0 + x,1);
      putpixel(M, x0 - x, y0 + y,1);
      putpixel(M, x0 - x, y0 - y,1);
      putpixel(M, x0 - y, y0 - x,1);
      putpixel(M, x0 + y, y0 - x,1);
      putpixel(M, x0 + x, y0 - y,1);

      y++;
  }
  fill(M,y0,x0,1);
}

int get_octant(int x0, int y0, int x1, int y1){

  if(x0 == x1){
    if(y0 <= y1)
      return 2;
    else
      return 6;
  }
  if(y0 == y1){
    if(x0 <= x1)
      return 0;
    else
      return 4;
  }
  double slope = (y1-y0)*1.0 / (x1-x0);

  if(slope > 0 && slope <= 1){
    if(x0 < x1)
      return 0;
    else
      return 4;
  }
  else if(slope > 1){
    if(y0 < y1)
      return 1;
    else
      return 5;
  }
  else if(slope < 0 && slope >= -1){
    if(x0 < x1)
      return 7;
    else
      return 3;
  }
  else if(slope < -1){
    if(y0 < y1)
      return 2;
    else
      return 6;
  }
  return 0;
}

void octant_zero(int octant, int& x, int& y, bool to){
  switch (octant) {
    case 0:
      break;
    case 1:
      swap(x,y);
      break;
    case 2:
      if(to){
        x = -x;
        swap(x,y);
      }
      else{
        y = -y;
        swap(x,y);
      }
      break;
    case 3:
      x = -x;
      break;
    case 4:
      x = -x;
      y = -y;
      break;
    case 5:
      x = -x;
      y = -y;
      swap(x,y);
      break;
    case 6:
      if(to){
        y = -y;
        swap(x,y);
      }
      else{
        x = -x;
        swap(x,y);
      }
      break;
    case 7:
      y = -y;
      break;
  }
}

#define B 1
#if B == 0
void plotline(vector<vector<int> >& M, int x0, int y0, int x1, int y1){
  DBG(cout << "SQUARE:\n";)
  int octant = get_octant(x0,y0,x1,y1);
  octant_zero(octant, x0, y0, true);
  octant_zero(octant, x1, y1, true);

  int dx = x1 - x0;
  int dy = y1 - y0;
  int D = 2*dy - dx;
  int y = y0;

  vector<pair<int,int> > ps;

  for(int x=x0; x<=x1; ++x){
    ps.push_back(make_pair(x,y));
    if(D > 0){
      y = y + 1;
      D = D - 2*dx;
    }
    D = D + 2*dy;
  }
  for(int i=0; i<ps.size(); ++i){
    int x = ps[i].first;
    int y = ps[i].second;
    octant_zero(octant, x, y, false);
    putpixel(M,x,y,2);
  }
}
#elif B == 1
void plotline(vector<vector<int> >& M, int x0, int y0, int x1, int y1)
{
   int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
   int err = dx+dy, e2; /* error value e_xy */

   for(;;){  /* loop */
      putpixel(M,x0,y0,2);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}
#endif

void drawsquare(vector<vector<int> >& M, int x1, int y1, int x2, int y2){
  double xc = (x1 + x2)*1.0/2  ; double yc = (y1 + y2)*1.0/2  ;    // Center point
  double xd = (x1 - x2)*1.0/2  ; double yd = (y1 - y2)*1.0/2  ;    // Half-diagonal

  double x3 = xc - yd  ;  double y3 = yc + xd;    // Third corner
  double x4 = xc + yd  ;  double y4 = yc - xd;    // Fourth corner

  plotline(M, round(x1),round(y1), round(x3),round(y3));
  plotline(M, round(x1),round(y1), round(x4),round(y4));
  plotline(M, round(x2),round(y2), round(x3),round(y3));
  plotline(M, round(x2),round(y2), round(x4),round(y4));

  fill(M,yc,xc,2);
}


int main(){

  int x,y,r,x0,y0,x1,y1;
  cin >> w >> h;
  cin >> x >> y >> r;
  cin >> x0 >> y0 >> x1 >> y1;

  x += 100;
  y += 100;
  x0 += 100;
  y0 += 100;
  x1 += 100;
  y1 += 100;

  vector<vector<int> > M(301, vector<int>(301, 0));

  //draw_circle(M, x, y, r);
  //drawsquare(M, x0,y0, x1,y1);
  plotline(M, round(x0),round(y0), round(x1),round(y1));

  for(int i=100; i<100+h; ++i){
    for(int j=100; j<100+w; ++j)
      if(M[i][j] >= 1)
        cout << "#";
      else
        cout << ".";
    cout << "\n";
  }


	return 0;
}
