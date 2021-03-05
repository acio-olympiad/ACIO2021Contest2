#include <iostream>
using namespace std;

/*
type 1: partition into intersecting windows [1,k], [a+1,k+a],[2a+1,k+2a] ...
    and load some segments into each window randomly

    In general we can define a f(k,a,l,n) load:
        -L intervals (or some number of things per interval)
        -shift of interval of a
        -length of interval k
        -n things per group
weights are chosen arbitarily

K = 1, 2, 10, 25, 100 are options [former 2 only for subtasks 3,4]

l small: very dense e.g l = 1,2,3
l medium: l = N/x for x = 25 ... 100
l = large: l = N/x for x = 1 ... 5

shift: a = medium (k/3 ... k/2)
        a = large: k+1 (buckets disjoint)

length of interval: k = 1 (subtask 1 only)
                    k = 20 (k small, for subtask 2)
                    k = 30000 (for all other subtasks)

In all,
6 cases subtask 1
12 cases subtask 2 (k = 20)
12 cases subtask 3 (k = 30000)
6 cases sub 4
12 cases sub 5
24 cases sub 6

+1 min case + 2 samples = 87 cases
*/

int rng(int l, int r) {
    if (l == r) {return(l);}
    return(l + (rand()%(r-l)));
}
const int MAXP = 1000000000;
int main() {
    //read n k a l K
    int n,k,a,l,K, seed;
    cin >> n >> k >> a >> l >> K >> seed;
    int lo = 1, hi = k;
    printf("%d %d\n",n*l,K);
    for (int i=1; i<=l; i++) {
        for (int j=1; j <= n; j++) {
            int x = rng(lo,hi),y=rng(lo,hi), p=rng(1,MAXP);
            printf("%d %d %d",min(x,y), max(x,y),p);
            if (i < l || j < n) {printf("\n");}
        }
        lo += a, hi += a;
    }
}



