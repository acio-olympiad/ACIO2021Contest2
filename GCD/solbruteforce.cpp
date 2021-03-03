#include<iostream>
#define MAXN 1005
#define LL long long
using namespace std;

int N,Q;
LL arr[MAXN], pi, vi;
LL gcd(LL a, LL b) {
    if (b == 0) {return(a);}
    return(gcd(b, a%b));
}
LL slv() {
    LL ans=0, cur;
    for (int l=1; l<=N; l++) {
        cur=arr[l];
        for (int r=l; r<=N; r++) {
            cur=gcd(cur, arr[r]);
            ans+=cur;
        }
    }
    return(ans);
}

int main() {
    freopen("gcd.in","r",stdin);
    scanf("%d %d",&N,&Q);
    for (int i=1; i<=N; i++) {
        scanf("%lld", &arr[i]);
    }
    printf("%lld\n", slv());
    for (int i=1; i<=Q; i++) {
        scanf("%lld %lld", &pi, &vi);
        arr[pi]=vi;
        printf("%lld\n",slv());
    }
}
