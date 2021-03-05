#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <utility>
#define MAXN 200005
#define MAXK 105
#define LL long long
using namespace std;

//segtree
class LazySegtree {
    //range add range max
    LL ST[MAXN * 8][2], Lazy[MAXN * 8]; //opt, val
public:
    void pushdown(int cur, bool b) {
        ST[cur][0] += Lazy[cur];
        if (b) {
            Lazy[2*cur] += Lazy[cur];
            Lazy[2*cur+1] += Lazy[cur];
        }
        Lazy[cur] = 0;
    }

    void pushup(int cur) {
        if (ST[2*cur][0] <= ST[2*cur+1][0]) {
            ST[cur][0] = ST[2*cur+1][0];
            ST[cur][1] = ST[2*cur+1][1];
        } else {
            ST[cur][0] = ST[2*cur][0];
            ST[cur][1] = ST[2*cur][1];
        }
    }

    void upd(int val, int lo, int hi, int l, int r, int cur) {
        pushdown(cur, l != r);
        if (lo > r || hi < l) {return;}
        if (lo <= l && hi >= r) {
            Lazy[cur] += val;
            pushdown(cur, l != r);
        } else {
            int mid = (l + r) >> 1;
            upd(val, lo, hi, l, mid, 2*cur);
            upd(val, lo, hi, mid+1, r, 2*cur+1);
            pushup(cur);
        }
    }

    void init(int l, int r, int cur) {
        ST[cur][1] = r; //if take nothing go straight to end
        ST[cur][0] = Lazy[cur] = 0;
        if (l == r) {return;}
        int mid = (l + r) >> 1;
        init(l, mid, 2*cur);
        init(mid+1, r, 2*cur+1);
    }

    pair <LL, int> get() {
        return(pair<LL, int> {ST[1][0], ST[1][1]});
    }
} ST;

int N, K, S[MAXN][3];
vector <pair<int,int> > Seg[MAXN * 2];

//coordinate compress
int val[MAXN * 2], getoriginal[MAXN * 2], pt = 1;
map <int,int> Lookup;

//dp
LL dp[MAXN * 2][MAXK];
int opt[MAXN * 2][MAXK];

int main() {
    freopen("sample.txt","r",stdin);
    scanf("%d %d",&N,&K);
    for (int i=1; i<=N; i++) {
        scanf("%d %d %d",&S[i][0], &S[i][1], &S[i][2]); //l r p
        val[2*i-1] = S[i][0];
        val[2*i] = S[i][1];
    }

    //cc
    sort(val+1, val+2*N+1);
    for (int i=1; i<=2*N; i++) {
        if (val[i] != val[i-1]) {
            Lookup[val[i]] = pt++;
            getoriginal[pt-1] = val[i];
        }
    }
    pt--, opt[pt+1][0]=pt; //pt is largest used index
    for (int i=1; i <= N; i++) {
        S[i][0] = Lookup[S[i][0]];
        S[i][1] = Lookup[S[i][1]];
        Seg[S[i][0]].push_back({S[i][1], S[i][2]});
    }
    //dp
    for (int i=1; i<=K; i++) {
        ST.init(1, pt, 1);
        opt[pt+1][i]=pt;
        for (int j=pt; j>=1; j--) {
            for (auto s: Seg[j]) {
                ST.upd(s.second, j, s.first, 1, pt, 1);
            }
            ST.upd(dp[j+1][i-1],j,j,1,pt,1);
            dp[j][i] = ST.get().first;
            opt[j][i] = ST.get().second; //optimal stab position
        }
    }

    //output:
    printf("%lld\n",dp[1][K]);
    int p = 1;
    for (int i=K; i>=1; i--) {
        printf("%d ", getoriginal[opt[p][i]]);
        p = opt[p][i]+1;
    }
}
