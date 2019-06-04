#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> edges[MAXN];
int n;

vector<int> path;
int cnt;

bool dfs(int u, int vis, int orig) {
	cnt++;

	path.push_back(u);
	vis |= 1 << u;

	if (vis == (1 << n) - 1) {
		for (int v : edges[u]) if (v == orig) return true;
		return false;
	}

	for (int v: edges[u]) {
		if ((vis & (1 << v)) == 0)
			if (dfs(v, vis, orig)) return true;
	}

	path.pop_back();
	return false;
}

int main() {
	int m; cin >> n >> m;
	while(m--) {
		int u, v; cin >> u >> v;
		u--, v--;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	int total = 0;
	for (int i = 0; i < n; i++) {
		cnt = 0;
		if (dfs(i, 0, i)) {
			cout << "HAMILTON!" << endl;
			for (int v : path) {
				cout << v << " ";
			} cout << i << endl;
			return 0;
		}
		printf("Started in %d. Tried %d possibilities\n", i, cnt);
		total += cnt;
	}

	printf("nenhum ciclo hamiltoniano encontrado, testou %d possibilidades\n", total);
	return 0;
}