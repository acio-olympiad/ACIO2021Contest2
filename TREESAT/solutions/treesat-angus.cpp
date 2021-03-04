#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
#define MAXN 100010
#define int long long
#ifdef DEBUG
	#define D(x...) printf(x)
#else
	#define D(x...)
#endif
struct UF {
	int rep[MAXN];
	UF() {
		iota(rep, rep+MAXN, 0);
	}
	int findrep(int a) {
		if (rep[a] == a) return a;
		return rep[a] = findrep(rep[a]);
	}
	void merge(int a, int b) {
		rep[findrep(a)] = findrep(b);
	}
	bool connected(int a, int b) {
		return findrep(a) == findrep(b);
	}
};
UF uf, uf2;
int n, m, k, u[MAXN], v[MAXN], w[MAXN], notallowed[MAXN];
vector<int> constraints[MAXN];
vector<int> groups[MAXN];
vector<pair<int, int> > twoconstraints;

vector<int> adj[MAXN];
int seen[MAXN], upto;
void dfs(int a) {
	if (seen[a] == upto) return;
	seen[a] = upto;
	for (auto b : adj[a]) dfs(b);
}
ld valueOfNode(int a) {
	set<int> components;
	int value = 0;
	for (auto b : groups[a]) {
		components.insert(uf2.findrep(u[b]));
		components.insert(uf2.findrep(v[b]));
		adj[uf2.findrep(u[b])].push_back(uf2.findrep(v[b]));
		adj[uf2.findrep(v[b])].push_back(uf2.findrep(u[b]));
		value += w[b];
	}
	upto++;
	// dfs our graph to count components;
	int comps = 0;
	for (auto b : groups[a]) {
		int node = uf2.findrep(u[b]);
		if (seen[node] != upto) {
			dfs(node);
			comps++;
		}
	}

	// remove edges
	for (auto b : groups[a]) {
		adj[uf2.findrep(u[b])].pop_back();
		adj[uf2.findrep(v[b])].pop_back();
	}

	int usefullness = (int)components.size() - comps;
	if (!usefullness) return 1e18;
	return (ld)value / (ld)(usefullness);
}

signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	for (int i = 1; i <= m; i++) {
		scanf("%lld%lld%lld", &u[i], &v[i], &w[i]);
	}
	for (int i = 0; i < k; i++) {
		int t, a, b;
		scanf("%lld%lld%lld", &t, &a, &b);
		if (t == 1) {
			uf.merge(a, b);
		} else {
			twoconstraints.emplace_back(a, b);
		}
	}
	for (auto a : twoconstraints) {
		constraints[uf.findrep(a.first)].push_back(uf.findrep(a.second));
		constraints[uf.findrep(a.second)].push_back(uf.findrep(a.first));
	}

	for (int i = 1; i <= m; i++) {
		groups[uf.findrep(i)].push_back(i);
	}
	int ans = 0;
	vector<int> used;
	while (1) {
		// brute force, bc why not
		// find the m
		pair<ld, int> mn = { 1e18, 0 };
		for (int i = 1; i <= m; i++) {
			if (!notallowed[i] && groups[i].size()) {
				mn = min(mn, { valueOfNode(i), i });
			}
		}
		if (mn.first == 1e18) break;

		int g = mn.second;
		for (auto a : groups[g]) {
			uf2.merge(u[a], v[a]);
			D("merging %lld and %lld\n", u[a], v[a]);
			D("components %lld %lld\n", uf2.findrep(u[a]), uf2.findrep(v[a]));
			ans += w[a];
			used.push_back(a);
		}

		for (auto a : constraints[g]) {
			notallowed[a] = 1;
		}

		// progress bar purposes only
		set<int> s;
		for (int i = 1; i <= n; i++) {
			s.insert(uf2.findrep(i));
		}
		fprintf(stderr, "%lu components remaining\n", s.size());
	}

	sort(used.begin(), used.end());

	printf("%lu\n", used.size());
	for (auto a : used) printf("%lld ", a);
	printf("\n");
	fprintf(stderr, "cost %lld\n", ans);

	for (int i = 1; i < n; i++) {
		assert(uf2.findrep(i) == uf2.findrep(i+1));
	}
}