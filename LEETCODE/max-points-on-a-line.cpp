#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};
 
class Solution {
public:

	long double getAngleBetween(const Point& a, const Point& b) {
		//cout << b.y - a.y << "/" << b.x - a.x << endl;
		return (long double)(atan2((long double)(b.y - a.y), (long double)(b.x - a.x)));
	}

    int maxPoints(vector<Point>& points) {

    	if(points.size() <= 1)
    		return points.size();

    	int res = 0;

    	sort(points.begin(), points.end(), [](Point a, Point b){if(a.y == b.y) return a.x < b.x; else return a.y < b.y; });

    	for(int i=0; i<points.size(); ++i) {
    		int c = 1;
    		vector<pair<int,long double> > angles;
    		for(int j=i+1; j<points.size(); ++j) {
    			if(points[j].x == points[i].x && points[j].y == points[i].y)
    				c++;
    			angles.push_back({j, getAngleBetween(points[i],points[j])});
    		}
    		map<long double,int> M;
    		for(auto& a : angles){
    			int j = a.first;
    			if(points[j].x == points[i].x && points[j].y == points[i].y)
    				continue;
    			M[a.second]++;
    		}

    		for(auto& k : M){
    			res = max(res, k.second+c);
    		}
    		res = max(res, c);
    	}

    	return res;
    }
};

int main() {


	int t;
	cin >> t;
	for(int _t=1; _t<=t; _t++) {
		Solution S;
		int n;
		cin >> n;
		vector<Point> ps;
		for(int i=0; i<n; ++i) {
			int x,y;
			cin >> x >> y;
			ps.push_back(Point(x,y));
		}
		cout << "Case #" << _t << ": " << S.maxPoints(ps) << endl;
	}

	return 0;
}