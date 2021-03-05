#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cassert>
#include <utility>
#define MAXN 1005
#define MAXM 100005
#define MAXK 100005
using namespace std;

int N, M, K;
int uf[MAXN];
int u[MAXM], v[MAXM], w[MAXM], seen[MAXM];
int t[MAXK], a[MAXK], b[MAXK];
vector<int> selected, es;
vector<pair<int, int>> eg[MAXM];

int f(int x) { if (uf[x] == x) return x; return uf[x] = f(uf[x]); }
void un(int x, int y) { uf[f(x)] = f(y); }

void dfs(int x) {
    seen[x] = 1;
    es.push_back(x);
    un(u[x], v[x]);
    for (pair<int, int> p : eg[x]) if (!seen[p.first] && p.second == 1) {
        dfs(p.first);
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 1; i <= N; i++) uf[i] = i;
    for (int i = 1; i <= M; i++) {
        scanf("%d %d %d", u+i, v+i, w+i);
    }
    for (int i = 0; i < K; i++) {
        scanf("%d %d %d", t+i, a+i, b+i);
        eg[a[i]].push_back({ b[i], t[i] });
        eg[b[i]].push_back({ a[i], t[i] });
    }

    // End boilerplate
    // So we basically ignore K and get on with our lives
    int ans = 2069696969;

    for (int i = 1; i <= M; i++) {
        if (!seen[i]) {
            for (int j = 1; j <= N; j++) uf[j] = j;
            dfs(i);
            int rip = 0;
            for (int j = 1; j <= N; j++) if (f(j) != f(1)) {
                rip = 1;
            }
            if (!rip) {
                int tot = 0;
                for (int x : es) tot += w[x];
                if (tot < ans) {
                    ans = tot;
                    selected.clear();
                    for (int x : es) selected.push_back(x);
                }
                ans = min(ans, tot);
            }
            es.clear();
        }
    }

    fprintf(stderr, "%d\n", ans);
    printf("%d\n", (int)selected.size());
    sort(selected.begin(), selected.end());
    for (int i = 0; i < selected.size(); i++) {
        if (i == 0) printf("%d", selected[i]);
        else printf(" %d", selected[i]);
    }
    printf("\n");
}
