#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9 + 1;

struct SegmentTree {
    int start, end, value;
    bool lazyUpdate = false;

    SegmentTree* left;
    SegmentTree* right;

    SegmentTree(int start, int end, int defaultValue) {
        this->value = defaultValue;
        if (end - start <= 1) {
            return;
        }

        int mid = (end + start) / 2;
        left = &SegmentTree(start, mid, defaultValue);
        right = &SegmentTree(mid, end, defaultValue);
    }

    void updateValue(int value, bool checkLazy) {
        this->value = min(this->value, value);

        if (checkLazy && this->end - this->start != 1) {
            this->lazyUpdate = true;
        }
    }

    void lazyUpdateChildren() {
        if (this->lazyUpdate) {
            if (left != NULL) {
                left->updateValue(this->value, true);
            }
            if (right != NULL) {
                right->updateValue(this->value, true);
            }
        }
    }

    void update(int start, int end, int value) {
        if (this->end < start || end < this->start) {
            return;
        }

        if (start <= this->start && this->end <= end) {
            this->updateValue(value, true);
            return;
        }

        this->lazyUpdateChildren();

        if (left != NULL) {
            left->update(start, end, value);
        }
        if (right != NULL) {
            right->update(start, end, value);
        }
        this->updateValue(min(left->value, right->value), false);
    }

    int result(int start, int end) {
        if (this->end < start || end < this->start) {
            return INF;
        }

        if (start <= this->start && this->end <= end) {
            return this->value;
        }

        this->lazyUpdateChildren();

        int res = INF;
        if (left != NULL) {
            res = min(res, left->result(start, end));
        }
        if (right != NULL) {
            res = min(res, right->result(start, end));
        }

        return res;
    }
};