#include <bits/stdc++.h>
using namespace std;

queue <string> Q;
unordered_map <string, int> V;
unordered_map <string, int> visited;
int n;

int _DEBUG = 0;
#define DBG(code) if(_DEBUG == 1){ do{ code }while(0); }

#define EMPTY 0

pair<string,string> Read()
{
    string start, target;
    int x;
    cin>>n;
    for(int i = 1; i <= n; i++){
        cin>>x;
        start += to_string(x-1);
        target += to_string(i-1);
    }
    DBG(cout << "[" << start << " " << target << "]" << endl;)
    return make_pair(start, target);
}

int part(string x, int s, string t, int from){
    string nr;
    for(int i=0; i<=n; ++i){
        string a = x.substr(0,i);
        for(int j=0; j<=n-i; ++j){
            string b = x.substr(i,j);
            for(int k=0; k<=n-i-j; ++k){
                string c = x.substr(i+j,k);
                string d = x.substr(i+j+k);
                
                DBG(printf("[%s] [%s] [%s] [%s]\n", a.c_str(), b.c_str(), c.c_str(), d.c_str());)
                if(from == 1)
                    nr = c + a + d + b;
                else
                    nr = b + d + a + c;

                DBG(cout << "nr: " << nr << " from: " << from << " steps: " << s << endl;)
                
                if(V.find(nr) == V.end()){
                    V[nr] = s;
                    Q.push(nr);
                    visited[nr] = from;
                }
                else{
                    if(visited[nr] != from && visited[nr] != EMPTY)
                        return s + V[nr];
                }
                if(nr == t)
                    return s;
            }
        }
    }
    return -1;
}


int bfs(string s, string t, int label, int lim){
    while(!Q.empty())
        Q.pop();
    Q.push(s);
    visited[s] = label;

    while(!Q.empty()){
        string u = Q.front(); Q.pop();
        int steps = V[u];

        if(u == t){
            return steps;
        }

        if(visited[u] != label && visited[u] != EMPTY)
            return steps + V[u];

        if(steps >= lim)
            return -1;

        int res = part(u, steps+1, t, label);
        if(res != -1)
            return res;
    }
    return -1;
}


int solve(string s, string t){

    // depth 2 forward bfs, i.e. label = 1
    int bfs1 = bfs(s,t,1,2);
    DBG(cout << "bfs1: " << bfs1 << endl;)
    if(bfs1 != -1)
        return bfs1;

    // depth 3 backward bfs, i.e. label = 2
    int bfs2 = bfs(t,s,2,3);
    DBG(cout << "bfs2: " << bfs2 << endl;)
    if(bfs2 != -1)
        return bfs2;

    // else, we required 6 steps.
    return 6;
}

int main(int argc, char **argv)
{
    if(argc > 1)
        _DEBUG = stoi(argv[1]);
    pair<string,string> v = Read();
    cout << solve(v.first, v.second) << endl;


    return 0;
}
