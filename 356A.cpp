#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;
int winner[4 * MAXN];
int winnerCount[4 * MAXN];
int winnerLazy[4 * MAXN];

void updateNode(int nodeNumber, int segStart, int segEnd, int value);
void removeLaziness(int nodeNumber, int segStart, int segEnd, bool recursive);
void updateWinner(int nodeNumber, int segStart, int segEnd, int updateSegStart, int updateSegEnd, int whoWon);
void printAll(int nodeNumber, int segStart, int segEnd);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

    int n, m;
    cin >> n >> m;
    while (m--) {
        int l, r, w;
        cin >> l >> r >> w;
        updateWinner(1, 1, n + 1, l, r + 1, w);
    }
    // cerr << "updating winners finished" << endl;

    removeLaziness(1, 1, n + 1, true);
    // cerr << "removing laziness finished" << endl;

    printAll(1, 1, n + 1);

    return 0;
}

void updateNode(int nodeNumber, int segStart, int segEnd, int value) {
    if (segEnd - segStart == 1) {
        if(segStart != value && winner[nodeNumber] == 0) {
            // cerr << "updating node " + to_string(nodeNumber) + "(" + to_string(segStart) + "," + to_string(segEnd) + ") value to: " + to_string(value) << '\n';
            winner[nodeNumber] = value;
        }
    } else {
        if (winner[nodeNumber] == 0 || (value != winner[nodeNumber] && segStart <= winner[nodeNumber] && winner[nodeNumber] < segEnd && winnerCount[nodeNumber] < 2)) {
            if (winnerCount[nodeNumber] == 1 && winnerLazy[nodeNumber] != 0) {
                removeLaziness(nodeNumber, segStart, segEnd, false);
            }
            // cerr << "updating node " + to_string(nodeNumber) + "(" + to_string(segStart) + "," + to_string(segEnd) + ") value to: " + to_string(value) << '\n';
            winner[nodeNumber] = winnerLazy[nodeNumber] = value;
            winnerCount[nodeNumber]++;
        }
    }
}

void removeLaziness(int nodeNumber, int segStart, int segEnd, bool recursive) {
    // cerr << "removing laziness of node " + to_string(nodeNumber) + "(" + to_string(segStart) + "," + to_string(segEnd) + ") value is: " + to_string(winner[nodeNumber]) << '\n';

    if (segEnd - segStart == 1) {
        return;
    }

    int segMid = (segStart + segEnd) / 2;
    if (winnerLazy[nodeNumber] != 0) {
        updateNode(nodeNumber * 2, segStart, segMid, winnerLazy[nodeNumber]);
        updateNode(nodeNumber * 2 + 1, segMid, segEnd, winnerLazy[nodeNumber]);
        winnerLazy[nodeNumber] = 0;

    }
    if (recursive) {
        removeLaziness(nodeNumber * 2, segStart, segMid, recursive);
        removeLaziness(nodeNumber * 2 + 1, segMid, segEnd, recursive);
    }
}

void updateWinner(int nodeNumber, int segStart, int segEnd, int updateSegStart, int updateSegEnd, int whoWon) {
    // cerr << "updateWinner(int " + to_string(nodeNumber) + ", int " + to_string(segStart) + ", int " + to_string(segEnd) + ", int " + to_string(updateSegStart) + ", int " + to_string(updateSegEnd) + ", int " + to_string(whoWon) + ") " << endl;

    if (segEnd <= updateSegStart || updateSegEnd <= segStart) {
        return;
    }

    if (segEnd - segStart == 1) {
        updateNode(nodeNumber, segStart, segEnd, whoWon);
    }

    if (updateSegStart <= segStart && segEnd <= updateSegEnd) {
        updateNode(nodeNumber, segStart, segEnd, whoWon);
        return;
    }


    removeLaziness(nodeNumber, segStart, segEnd, false);

    int segMid = (segStart + segEnd) / 2;
    updateWinner(nodeNumber * 2, segStart, segMid, updateSegStart, updateSegEnd, whoWon);
    updateWinner(nodeNumber * 2 + 1, segMid, segEnd, updateSegStart, updateSegEnd, whoWon);
}

void printAll(int nodeNumber, int segStart, int segEnd) {
    // cerr << "node " + to_string(nodeNumber) + "(" + to_string(segStart) + "," + to_string(segEnd) + ") value is: " + to_string(winner[nodeNumber]) << '\n';
    if (segEnd - segStart == 1) {
        cout << winner[nodeNumber] << ' ';
        return;
    }
    int segMid = (segStart + segEnd) / 2;
    printAll(nodeNumber * 2, segStart, segMid);
    printAll(nodeNumber * 2 + 1, segMid, segEnd);
}
