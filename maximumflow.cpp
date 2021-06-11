#include <bits/stdc++.h>
using namespace std;

const int lm = 1005;
struct edge {
	int v, flow, c, rev; 
};
int level[lm];
vector <edge> adj[lm];
int n, m, s, t;

bool addlevel(int s, int t) {
	for (int i = 0; i < n; i++) {
		level[i] = -1;
	}	
	level[s] = 0;
	queue <int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (edge e : adj[u]) {
			if (e.flow < e.c && level[e.v] < 0) {
				level[e.v] = level[u] + 1;
				q.push(e.v);
			} 
		}
	}
	return level[t] >= 0;
}

int sendflow(int u, int t, int flow, int start[]) {
	if (u == t) return flow;
	for ( ; start[u] < (int)adj[u].size(); start[u]++) {
		edge &e = adj[u][start[u]];
		if (level[e.v] == level[u]+1 && e.flow < e.c) {
			int minflow = sendflow(e.v, t, min(flow, e.c - e.flow), start);
			if (minflow > 0) {
				e.flow += minflow;
				adj[e.v][e.rev].flow -= minflow;
				return minflow;
			}
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		edge a{v, 0, c, (int)adj[v].size()};
		edge b{u, 0, 0, (int)adj[u].size()};
		adj[u].push_back(a);
		adj[v].push_back(b);
	}
	int ans = 0;
	while (addlevel(s, t)) {
		int *start = new int[n] {0};
		while (int flow = (sendflow(s, t, INT_MAX, start))) {
			ans += flow;
		}
	}
	int ansm = 0;
	for (int u = 0; u < n; u++) {
		for (edge e : adj[u]) {
			if (e.flow > 0) ansm += 1;
		}
	}
	cout << n << " " << ans << " " << ansm << endl;
	for (int u = 0; u < n; u++) {
		for (edge e : adj[u]) {
			if (e.flow > 0) cout << u << " " << e.v << " " << e.flow << endl;
		}
	}
	return 0;
}