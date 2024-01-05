#include <bits/stdc++.h>

using namespace std;

const int MAX_M = 1000 + 10;

int m;

int gcdNumbers[MAX_M];

bool isSolvable = true;

void input() {
    cin >> m;
    for (int i = 0; i < m; i++) {
        int num;
        cin >> num;
        gcdNumbers[i] = num;
    }
}

void solve() {
    for (int i = 0; i < m; i++) {
        if (gcdNumbers[i] % gcdNumbers[0] != 0) {
            isSolvable = false;
            return;
        }
    }
}

void output() {
    if (isSolvable) {
        cout << 2 * m << endl;
        for (int i = 0; i < m; i++) {
            cout << gcdNumbers[0] << ' ' << gcdNumbers[i] << ' ';
        }
        cout << endl;
    } else {
        cout << -1;
    }
    cout << endl;
}

int main() {

    input();

    solve();

    output();

    return 0;
}