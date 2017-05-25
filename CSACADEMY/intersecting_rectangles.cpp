#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

struct Rectangle {
    int x1, y1, x2, y2;   
};

bool intersect(Rectangle r, Rectangle q){
    Rectangle p;
    p.x1 = max(r.x1, q.x1);
    p.y1 = max(r.y1, q.y1);
    
    p.x2 = min(r.x2, q.x2);
    p.y2 = min(r.y2, q.y2);
    
    if(p.x1 >= p.x2 || p.y1 >= p.y2)
        return false;
    return true;
}

int intersectingRectangles(vector<Rectangle>& rectangles) {
    int cnt = 0;
    int n = rectangles.size();
    for(int i=0; i<n; ++i)
        for(int j=i+1; j<n; ++j)
            if(intersect(rectangles[i], rectangles[j]))
                cnt++;
    return cnt;
}
   
int main() {
    int N;
    cin >> N;
    vector<Rectangle> rectangles;
    for (int i = 0; i < N; ++i) {
        Rectangle rect;
        cin >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2; 
        rectangles.push_back(rect);
    }
    
    cout << intersectingRectangles(rectangles) << "\n";
    return 0;
}

