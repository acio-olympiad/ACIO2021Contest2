#include<vector>
#include "game.h"
using namespace std;
//You might want to use 64 bit integers. The answer might be big!

int gcd(int a, int b) { //returns gcd of a,b
     return(b ? gcd(b, a%b) : a);
}

long long init(vector <int> A) {
    return(gcd(6,8)); //returns 2
}

long long update(int p, int v) {
    return(0);
}
