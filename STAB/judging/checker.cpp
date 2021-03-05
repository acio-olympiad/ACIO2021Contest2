#define CMS
// NOTE: Please ONLY use the testlib.h that is provided with the checker.
// Modifications have been made to it such that it will not break on invalid output.
#include "testlib.h"
#define MAXN 200005
#define LL long long
using namespace std;
int N,K,S[MAXN][3], Stabs[105];
const int MAXV = 1e9;
set <int> Stabset;
int main(int argc, char * argv[])
{
    //setName("compares two signed integers");
    registerTestlibCmd(argc, argv);

    //read input file
    int N = inf.readInt();
    inf.readSpace();
    int K = inf.readInt();
    inf.readEoln();
    for (int i=1; i<=N; i++) {
        int l = inf.readInt();
        inf.readSpace();
        int r = inf.readInt();
        inf.readSpace();
        int p = inf.readInt();
        S[i][0] = l, S[i][1] = r, S[i][2] = p;
        if (i != N) {inf.readEoln();}
    }
    inf.readEof();

    LL j_value = ans.readLong();

    LL p_value = ouf.readLong();

    //if (j_value != p_value) {
    //    quitf(_wa, "expected %lld, found %lld", p_value, j_value);
    //}

    //checkers ignore spaces
    for (int i=0; i<K; i++) {
        Stabs[i] = ans.readInt(1, MAXV);
        if (i && Stabs[i] < Stabs[i-1]) {
            quitf(_wa, "elements not in increasing order");
        }
        Stabset.insert(Stabs[i]);
    }

    LL sum = 0;
    for (int i=1; i<=N; i++) {
        if (Stabset.lower_bound(S[i][0]) == Stabset.end()) {
            continue;
        }
        auto v = Stabset.lower_bound(S[i][0]);
        if (v != Stabset.end() && (*v) <= S[i][1]) {sum += S[i][2];}
    }
    if (sum != j_value) {
        quitf(_wa, "construction invalid, value %lld rather than %lld",sum,j_value);
    }
    //checker
    quitf(_ok, "answer is %lld", j_value);
}
