#define CMS
// NOTE: Please ONLY use the testlib.h that is provided with the checker.
// Modifications have been made to it such that it will not break on invalid output.
#include "testlib.h"
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 1005
#define MAXM 100005
#define MAXK 100005

int uf[MAXN];
int N, M, K, edges;
long long X;
double P;
int edge[MAXM];
int u[MAXM], v[MAXM], w[MAXM], use[MAXM];
int t[MAXK], a[MAXK], b[MAXK];

int f(int x) { if (uf[x] == x) return x; return uf[x] = f(uf[x]); }
void un(int x, int y) { uf[f(x)] = f(y); }

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    N = inf.readInt();
    M = inf.readInt();
    K = inf.readInt();
    edges = ans.readInt();
    X = ouf.readLong();
    P = ouf.readDouble();
    for (int i = 1; i <= N; i++) {
        uf[i] = i;
    }

    for (int i = 1; i <= M; i++) {
        u[i] = inf.readInt();
        v[i] = inf.readInt();
        w[i] = inf.readInt();
    }
    for (int i = 0; i < K; i++) {
        t[i] = inf.readInt();
        a[i] = inf.readInt();
        b[i] = inf.readInt();
    }

    long long weight_sum = 0;

    for (int i = 1; i <= edges; i++) {
        edge[i] = ans.readInt();
        if (edge[i] <= edge[i-1]) quit(_wa, "Input is not in ascending order.");
        use[edge[i]] = 1;
        weight_sum += w[edge[i]];
        un(u[edge[i]], v[edge[i]]);
    }

    fprintf(stderr, "Weight sum: %lld\n", weight_sum);

    for (int i = 1; i <= N; i++) {
        if (f(i) != f(1)) {
            quit(_wa, "Input does not connect the graph!");
        }
    }
    
    for (int i = 0; i < K; i++) {
        if (t[i] == 1 && use[a[i]] != use[b[i]]) {
            printf("%d\n", i);
            quit(_wa, "Input does not satisfy constraints.");
        }
        if (t[i] == 2 && use[a[i]] && use[b[i]]) {
            printf("%d\n", i);
            quit(_wa, "Input does not satisfy constraints.");
        }
    }

    double prop = (double)weight_sum / (double)X;

    double points = min(1.0, 0.3 + 0.7 * exp(1.25 * (prop-1) / (1-P)));
    if (fabs(1.0 - points) < 0.0001f) {
        quitf(_ok, "Accepted");
    } else {
        quitp(points, "Accepted");
    }
}
