#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include <cstring>
#include <climits>
#include <fstream>
#include <algorithm>
using namespace std;

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
 * Complexity: O(|V| * |E|)
 * Improvement:
 * For relaxation use only nodes that were improved.
 * Complexity: O(|V| * |E| * log(|V|))¢
 */
bool bellman(const AdjList& G, const int s, vector<T>& dist, vector<int>& parent) {

	int N = G.size();
	dist.resize(N, INFINITY);
	parent.resize(N, -1);
	queue<int> Q;
	vector<bool> in_queue(N, false);
	vector<int> cnt_in_queue(N, 0);

	// compute shortest paths from s to all vertices
	dist[s] = 0;
	Q.push(s);
	in_queue[s] = true;
	cnt_in_queue[s] = 1;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		in_queue[u] = false;
		for (int j=0; j<G[u].size(); ++j) {
			int v = G[u][j].first;
			T w = G[u][j].second;
			if (dist[u] != INFINITY && dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				if (!in_queue[v]) {
					if (cnt_in_queue[v] >= N) {
						return true;
					}
					else {
						parent[v] = u;
						Q.push(v);
						in_queue[v] = true;
						cnt_in_queue[v]++;
					}
				}
			}
		}
	}
	return false;
}