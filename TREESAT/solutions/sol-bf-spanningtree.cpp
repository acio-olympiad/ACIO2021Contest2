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

int use[MAXM];

vector<int> selected;

int f(int x) { if (uf[x] == x) return x; return uf[x] = f(uf[x]); }
void un(int x, int y) { uf[f(x)] = f(y); }

int ask() {
    int tot = 0;
    for (int i = 1; i <= N; i++) uf[i] = i;
    for (int i = 1; i <= M; i++) {
        if (use[i-1]) {
            tot += w[i];
            un(u[i], v[i]);
        }
    }
    int rip = 0;
    // Check spanning tree
    for (int i = 1; i <= N; i++) {
        if (f(i) != f(1)) rip = 1;
    }
    // Check K contstraints
    for (int i = 0; i < K; i++) {
        if (t[i] == 1 && (use[a[i] - 1] != use[b[i] - 1])) rip = 1;
        if (t[i] == 2 && (use[a[i] - 1] == use[b[i] - 1])) rip = 1;
    }
    // Reset UF
    if (rip) return -1;
    return tot;
}

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
    int ans = 2069696969;

    for (int i = 0; i < N-1; i++) {
        use[M-1-i] = 1;
    }
    do {
        int res = ask();
        if (res >= 0 && res < ans) {
            selected.clear();
            ans = res;
            
            for (int i = 1; i <= M; i++) {
                if (use[i-1]) selected.push_back(i);
            }
        }
    } while (next_permutation(use, use+M));

    fprintf(stderr, "%d\n", ans);
    printf("%d\n", selected.size());
    sort(selected.begin(), selected.end());
    for (int i = 0; i < selected.size(); i++) {
        if (i == 0) printf("%d", selected[i]);
        else printf(" %d", selected[i]);
    }
    printf("\n");
}
