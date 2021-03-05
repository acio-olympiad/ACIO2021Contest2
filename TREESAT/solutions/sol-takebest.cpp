#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>

using namespace std;

int N, M, K;
map<pair<int, int>, pair<int, int>> m;
vector<int> selected;

int main() {
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 1; i <= M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        pair<int, int> p = { u, v };
        if (m.find(p) == m.end() || m[p].first > w) {
            m[p] = { w, i };
        }
    }
    long long ans = 0;
    for (pair<pair<int, int>, pair<int, int>> p : m) {
        ans += p.second.first;
        selected.push_back(p.second.second);
    }
    sort(selected.begin(), selected.end());
    
    fprintf(stderr, "%lld\n", ans);
    printf("%d\n", (int)selected.size());
    for (int i = 0; i < selected.size(); i++) {
        if (i == 0) printf("%d", selected[i]);
        else printf(" %d", selected[i]);
    }
    printf("\n");
}
