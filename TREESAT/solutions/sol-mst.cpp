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
int u[MAXM], v[MAXM], w[MAXM];
int t[MAXK], a[MAXK], b[MAXK];
vector<int> selected;

int f(int x) { if (uf[x] == x) return x; return uf[x] = f(uf[x]); }
void un(int x, int y) { uf[f(x)] = f(y); }

int main() {
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 1; i <= N; i++) uf[i] = i;
    for (int i = 1; i <= M; i++) {
        scanf("%d %d %d", u+i, v+i, w+i);
    }
    for (int i = 0; i < K; i++) {
        scanf("%d %d %d", t+i, a+i, b+i);
    }

    // End boilerplate
    // So we basically ignore K and get on with our lives
    vector<pair<int, int>> edges;
    for (int i = 1; i <= M; i++) {
       edges.push_back({ w[i], i });
    }
    sort(edges.begin(), edges.end());
    int ans = 0;
    for (int i = 0; i < M; i++) {
        int ind = edges[i].second;
        if (f(u[ind]) != f(v[ind])) {
            un(u[ind], v[ind]);
            ans += w[ind];
            selected.push_back(ind);
        }
    }
    printf("%d\n", ans);
    sort(selected.begin(), selected.end());
    for (int i = 0; i < selected.size(); i++) {
        if (i == 0) printf("%d", selected[i]);
        else printf(" %d", selected[i]);
    }
    printf("\n");
}
