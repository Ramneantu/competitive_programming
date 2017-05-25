#include<bits/stdc++.h>

#define rep(i,a,b) for(int i=int(a); i<=int(b); ++i)
#define rev(i,b,a) for(int i=int(b); i>=int(a); --i)
#define rec(i,a,b,c) for(int i=int(a); i<=int(b); i+=int(c))
#define recv(i,a,b,c) for(int i=int(a); i>=int(b); i-=int(c))
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back(x)
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it=(container).begin(); it != (container).end(); ++it)
#define sqr(x) ((x)*(x))
#define sz(a) int((a).size())
#define mod(a,n) ((a) < 0 ? ((n)+(a)) : ((a)%(n)))
#define mout(M,n,m) rep(i,0,(n)-1){ rep(j,0,(m)-1) cout << (M)[i][j] << " ";  cout << "\n"; }
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

class Graph {
    public:
        vector<vector<int> > G;
        int edge_cost;
        Graph(int n) {
            G.resize(n, vector<int>());
            edge_cost = 6;
        }

        void add_edge(int u, int v) {
            G[u].push_back(v);
            G[v].push_back(u);
        }

        vector<int> shortest_reach(int start) {
          vector<int> dist(G.size(), -1);
          vector<bool> visited(G.size(),false);
          queue<int> Q;
          Q.push(start);
          dist[start] = 0;
          visited[start] = true;
          while(!Q.empty()){
            int v = Q.front(); Q.pop();
            for(int i=0; i<G[v].size(); ++i){
                int u = G[v][i];
                if(!visited[u]){
                  Q.push(u);
                  dist[u] = dist[v] + edge_cost;
                  visited[u] = true;
                }
            }
          }
           return dist;
        }

};

int main() {
    int queries;
    cin >> queries;

    for (int t = 0; t < queries; t++) {

      int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6:
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
      int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
