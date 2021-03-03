#include<iostream>
#include<vector>
#include<utility>
#define MAXN 100005
#define LL long long
using namespace std;
int N, Q, pi;
LL A[MAXN], vi;
vector <pair<int,int> > ST[MAXN*4][2]; //(val, ind) l->r and r<-l
LL Sum[MAXN*4];

int gcd(int a, int b) {
     return(b ? gcd(b, a%b) : a);
}

void pushup(int cur, int lo, int hi) {
    ST[cur][0].clear();
    ST[cur][1].clear();
    for (auto p: ST[2*cur][0]) {
        ST[cur][0].push_back(p);
    }
    for (auto p: ST[2*cur+1][0]) {
        int res=gcd(p.first, ST[cur][0].back().first);
        if (res != ST[cur][0].back().first) {
            ST[cur][0].push_back({res, p.second});
        }
    }
    for (auto p: ST[2*cur+1][1]) {
        ST[cur][1].push_back(p);
    }
    for (auto p: ST[2*cur][1]) {
        int res=gcd(p.first, ST[cur][1].back().first);
        if (res != ST[cur][1].back().first) {
            ST[cur][1].push_back({res, p.second});
        }
    }
    Sum[cur]=Sum[2*cur]+Sum[2*cur+1];
    for (int l=0; l<ST[2*cur][1].size(); l++) {
        for (int r=0; r<ST[2*cur+1][0].size(); r++) {
            LL g=gcd(ST[2*cur][1][l].first, ST[2*cur+1][0][r].first);
            LL len1=ST[2*cur][1][l].second- (l+1<ST[2*cur][1].size() ? ST[2*cur][1][l+1].second : lo-1);
            LL len2=(r+1<ST[2*cur+1][0].size() ? ST[2*cur+1][0][r+1].second : hi+1) - ST[2*cur+1][0][r].second;
            Sum[cur]+=(LL) g*len1*len2;
        }
    }
}

void update(int ind, LL val, int l, int r, int cur) {
    if (ind < l || ind > r) {return;}
    if (l == r) {
        ST[cur][0].clear();
        ST[cur][1].clear();
        ST[cur][0].push_back({ (int) val, l});
        ST[cur][1].push_back({ (int) val, r});
        Sum[cur]=val;
    } else {
        int mid=(l+r)>>1;
        update(ind, val, l, mid, 2*cur);
        update(ind, val, mid+1, r, 2*cur+1);
        pushup(cur, l, r);
    }
}

void build(int l, int r, int cur) {
     if (l == r) {
        ST[cur][0].reserve(30);
        ST[cur][1].reserve(30);
        ST[cur][0].push_back({ (int) A[l], l});
        ST[cur][1].push_back({ (int) A[r], r});
        Sum[cur]=A[l];
    } else {
        int mid=(l+r)>>1;
        build(l, mid, 2*cur);
        build(mid+1, r, 2*cur+1);
        pushup(cur, l, r);
    }
}

int main() {
    freopen("gcd.in","r",stdin);
    freopen("gcd.out","w",stdout);
    scanf("%d %d",&N,&Q);
    for (int i=1; i<=N; i++) {
        scanf("%lld", &A[i]);
    }
    build(1,N,1);
    printf("%lld\n", Sum[1]);
    for (int i=1; i<=Q; i++) {
        scanf("%d %lld", &pi, &vi);
        update(pi, vi, 1, N, 1);
        A[pi]=vi;
        printf("%lld\n",Sum[1]);
    }
}

/*
void disp(int cur) {
     printf("Displaying node %d\n", cur);
     printf("Sum: %lld\n", Sum[cur]);
     printf("GCD ranges from left to right: \n");
     for (auto p: ST[cur][0]) {
        printf("Val %d Ind %d\n", p.first, p.second);
     }
     printf("GCD ranges from right to left: \n");
     for (auto p: ST[cur][1]) {
        printf("Val %d Ind %d\n", p.first, p.second);
     }
     printf("\n");
}
*/
