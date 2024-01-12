#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 10;

set<int> alives;
int losedTo[MAXN];

int main(){

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        alives.insert(i);
    }

    while (m--) {
        int l, r, w;
        cin >> l >> r >> w;

        auto firstAlive = alives.lower_bound(l);
        auto lastAlive = alives.upper_bound(r);

        if (firstAlive == alives.end()) {
            continue;
        }

        for (auto i = firstAlive; i != lastAlive; ++i) {
            if (*i != w) {
                losedTo[*i] = w;
            }
        }
        alives.erase(firstAlive, lastAlive);
        alives.insert(w);
    }

    for (int i = 1; i <= n; i++) {
        cout << losedTo[i] << ' ';
    }

    return 0;
}