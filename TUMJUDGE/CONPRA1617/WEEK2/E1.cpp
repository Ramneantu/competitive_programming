#include<bits/stdc++.h>
//
//  main.cpp
//  Plop
//
//  Created by Cosmin Vlaicu on 27.10.2016.
//  Copyright © 2016 Cosmin Vlaicuasa. All rights reserved.
//
using namespace std;
#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
vector<int> parent;
vector<int> size;
vector<vector<int> > hates;

void init_set(int n){
    parent.resize(n);
    size.resize(n);
    for(int i=0;i<n;i++){
        parent.at(i)=i;
        size.at(i)=1;
      }
}

int find_set(int x){
    if(parent.at(x)==x){
        return x;
    }else{
        return find_set(parent.at(x));
    }
}

void union_set(int i, int j){
    int fx=find_set(i);
    int fy=find_set(j);
    if(size.at(fx)<size.at(fy)){
        parent.at(fx)=fy;
        size.at(fy)+=size.at(fx);
    }else{
        parent.at(fy)=fx;
        size.at(fx)+=size.at(fy);
    }

}
int main(int argc, const char * argv[]) {

  int t;
  cin >> t;
    rep(_t,1,t){
        int n,m;
        cin >> n >> m;
        init_set(n);
        hates.clear();
        hates.resize(n,vector<int>());
        vector<pair<int,int> > F;
        vector<pair<int,int> > H;
        rep(i,0,m-1){
            char c;
            int x,y;
            cin >> c >> x >> y;
            x--;
            y--;
            if(c == 'F')
                F.push_back(make_pair(x,y));
            else
                H.push_back(make_pair(x,y));
        }
        rep(i,0,F.size()-1)
        union_set(F[i].first, F[i].second);
        rep(i,0,H.size()-1){
            int sx = find_set(H[i].first);
            int sy = find_set(H[i].second);
            hates[sx].push_back(sy);
            hates[sy].push_back(sx);
        }
        // hates(i) = all the people i hates, so these people can join together and have i as a common enemy.
        for(int i=0; i<hates.size(); ++i)
            for(int j=1; j<hates[i].size(); ++j)
                union_set(hates[i][0], hates[i][j]);

        cout << "Case #" << _t << ": ";
        if(2*size[find_set(0)] > n)
            cout << "yes\n";
        else
            cout << "no\n";
    }
}
