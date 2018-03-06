#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

typedef long long LL;
typedef int T;
typedef vector<T> VT;
typedef pair<T,T> TT;
typedef vector<TT> VTT;
typedef vector<vector<T> > VVT;

// Graph
typedef vector<VTT> AdjList;

// defines
#define INFINITY INT_MAX


/*
 * Bellman-Ford Algorithm
 * Single Source Shortest Path
 * Works on Graphs with negative edges
 * If Graph contains a negative cycle then Bellman-Ford can detect it.
 */
bool bellman(const AdjList& G, const int s, vector<int>& dist, vector<int>& parent) {

	int N = G.size();
	dist.resize(N, INFINITY);
	parent.resize(N, -1);

	// compute shortest paths from s to all vertices
	dist[s] = 0;
	for (int i=0; i<N-1; ++i) {
		for (int u=0; u<G.size(); ++u) {
			for (int j = 0; j<G[u].size(); ++j) {
				int v = G[u][j].first;
				int w = G[u][j].second;
				if (dist[u] + w < dist[v]) {
					dist[v] = dist[u] + w;
					parent[v] = u;
				}
			}
		}
	}

	// check for negative cycles
	for (int u=0; u<G.size(); ++u) {
		for (int j=0; j<G[u].size(); ++j) {
			int v = G[u][j].first;
			int w = G[u][j].second;
			if (dist[u] + w < dist[v]) { // contains negative cycle
				return true;
			}
		}
	}
	return false;
}
