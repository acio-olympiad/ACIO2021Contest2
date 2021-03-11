#include<iostream>
#include<time.h>
#include<set>
#include <cassert>
#include<utility>
using namespace std;

const int maxV = 100000;
int gen(int t) {
    if (t == 1) {
        return 1<<(rand()%17);
    } else if (t == 2) {
        int val = 1;
        while (val <= maxV/2) {
               // printf("%d\n",val);
            int m = 1;
            if (3*val <= maxV) {m++;}
            if (5*val <= maxV) {m++;}
            int x = rand()%m;
            if (x == 0) {val*=2;}
            if (x == 1) {val*=3;}
            if (x == 2) {val*=5;}
        }
        return(val);
    } else if (t == 3) {
        return (rand()%maxV) + 1;
    }
}
int main() {
    int n,t,s,seed; //n, type of generation, subtask
    /* t = 1: powers of 2
       t = 2: powers of 2 3 5
       t = 3: arbitary
    */
    cin >> n >> t >> s >> seed;
    srand(seed);
    int q = s == 5 ? 10000 : 0;
    printf("%d %d\n",n,q);
    for (int i=1; i<=n; i++) {
        int val = gen(t);
        assert(val > 0);
        printf("%d", val);
        if (i < n) {printf(" ");}
        else {printf("\n");}
    }
    for (int i=0; i<q; i++) {
        printf("%d %d",rand()%n, gen(t));
        if (i+1 != q) {printf("\n");}
    }
}
