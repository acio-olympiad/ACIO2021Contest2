#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <set>

using namespace std;

const long long int INF = 1e9;

struct range {
    long long int l, r, p;
};

vector<range> v;

map<pair<long long int, long long int>, pair<long long int, long long int>> cache;

bool stabbed(range r, long long int x) {
    return r.l <= x && x <= r.r;
}

// All intervals stabbed by stab, but not by lim.
long long int value(long long int stab, long long int lim) {
    long long int ans = 0;
    for(auto r: v) {
        if(stabbed(r, stab) && !stabbed(r, lim)) {
            ans += r.p;
        }
    }
    //cerr << ans << "\n";
    return ans;
}

// Critical points for "coord compression"
vector<long long int> crits;

// Make K stabs in [1, N]
pair<long long int, long long int> dp(long long int curN, long long int curK) {
    if(curK == 0) {
        return {0, 1};
    }
    if(curN == 0) {
        return {0, 1};
    }
    if(cache.find({curN, curK}) == cache.end()) {
        pair<long long int, long long int> best{-INF, -1};
        //for(long long int i = 1; i <= curN; i++) {
        for(auto c: crits) {
            if(c > curN) {
                continue;
            }
            long long int i = c;
            auto cur = dp(i-1, curK-1);
            cur.first += value(i, curN+1);
            cur.second = i;

            best = max(best, cur);
        }
        cache[{curN, curK}] = best;
        cerr << "We're at " << curN << " " << curK << " = " << best.first << " " << best.second << "\n";
    }

    return cache[{curN, curK}];
}

int main() {
    long long int N, K;
    cin >> N >> K;
    v.resize(N);
    for(long long int i = 0; i < N; i++) {
        cin >> v[i].l >> v[i].r >> v[i].p;
        crits.push_back(v[i].l);
        crits.push_back(v[i].r);
    }
    crits.push_back(1);
    auto best = dp(1e9, K);
    cout << best.first << "\n";
    multiset<long long int> stabbies;
    while(K) {
        stabbies.insert(best.second);
        //cerr << best.first << " " << best.second << "\n";
        //best = cache[{best.second-1, --K}];
        best = dp(best.second-1, --K);
    }
    for(long long int x: stabbies) {
        cout << x << " ";
    }
    cout << "\n";
}
