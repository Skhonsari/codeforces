#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> Interval;
typedef pair<Interval, int> Voucher;

int duration(Voucher vo) {
    return vo.first.second - vo.first.first + 1;
}


vector<Voucher> vouchers;

int main() {
    int n, totalDuration;
    cin >> n >> totalDuration;

    for (int i = 0; i < n; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        Voucher voucher(Interval(l, r), c);
        vouchers.push_back(voucher);
    }

    for (auto v : vouchers) {
        cout << v.first.first << ' ' << v.first.second << ' ' << v.second << endl;
    }

    return 0;
}