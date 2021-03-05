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
long long dp[MAXN];
pair<pair<int, int>, int> opt[MAXN];
vector<int> selected;
// Left, right, value
vector<pair<pair<int, int>, int>> intervals[MAXN];

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
    long long ans = 0;
    
    int left = 1, cost = w[1];
    for (int i = 2; i <= M; i++) {
        assert(u[i] + 1 == v[i]);
        if (u[i] != v[i-1]) {
            // Make a new interval
            intervals[v[i-1]].push_back({ { left, i-1 }, cost });
            left = i;
            cost = w[i];
        } else {
            cost += w[i];
        }
    }
    intervals[v[M]].push_back({ { left, M }, cost });

    dp[1] = 0;
    for (int i = 2; i <= N; i++) {
        dp[i] = 2069696969;
        for (pair<pair<int, int>, int> p : intervals[i]) {
            for (int j = u[p.first.first]; j < i; j++) {
                if (dp[j] + p.second < dp[i]) {
                    dp[i] = dp[j] + p.second;
                    opt[i] = { p.first, j };
                }
            }
        }
    }
    ans = dp[N];

    int cur = N;
    while (cur > 1) {
        for (int i = opt[cur].first.first; i <= opt[cur].first.second; i++) {
            selected.push_back(i);
        }
        cur = opt[cur].second;
    }
    
    fprintf(stderr, "%lld\n", ans);
    printf("%d\n", (int)selected.size());
    sort(selected.begin(), selected.end());
    for (int i = 0; i < selected.size(); i++) {
        if (i == 0) printf("%d", selected[i]);
        else printf(" %d", selected[i]);
    }
    printf("\n");
}
