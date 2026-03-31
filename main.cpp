#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int D;
    long long n;
    cin >> D >> n;

    // Number of leaf nodes
    int leaves = 1 << (D - 1);  // 2^(D-1)

    // We need to track the state of internal nodes and leaf nodes
    // Index: 1 to 2^D-1 (1-indexed binary tree)
    // State: 0 = closed, 1 = open
    vector<int> state(1 << D, 0);

    // For each ball, simulate its path by checking current states
    // But with n up to 10^9, we need a smarter approach

    // Key insight:
    // - Each internal node toggles when a ball passes through it
    // - We can determine how many balls passed through each node
    // - For the last ball, we trace its path based on current states

    // Let's calculate how many balls pass through each node
    // Node at position i (1-indexed):
    // - Root (1) gets all n balls
    // - For left child (2*i): gets balls when parent is closed (before toggle)
    // - For right child (2*i+1): gets balls when parent is open (before toggle)

    // Count balls reaching each node
    vector<long long> count(1 << D, 0);
    count[1] = n;

    for (int i = 1; i < (1 << (D - 1)); i++) {
        long long balls = count[i];
        if (balls == 0) continue;

        // Balls alternate: first goes left, second goes right, etc.
        long long left_count = (balls + 1) / 2;
        long long right_count = balls / 2;

        count[2 * i] = left_count;
        count[2 * i + 1] = right_count;

        // State after all balls: odd count means ON, even means OFF
        state[i] = (balls % 2);
    }

    // Set leaf states
    for (int i = (1 << (D - 1)); i < (1 << D); i++) {
        state[i] = (count[i] % 2);
    }

    // Now trace the path of the last ball
    int pos = 1;
    for (int depth = 0; depth < D - 1; depth++) {
        // Check the state BEFORE the last ball arrives
        // We need to reverse the effect of all balls
        long long balls_before_last = count[pos] - 1;
        int state_before = (balls_before_last % 2);

        if (state_before == 0) {
            // Was closed, go left
            pos = 2 * pos;
        } else {
            // Was open, go right
            pos = 2 * pos + 1;
        }
    }

    // pos is now at a leaf node (output the node index itself)
    cout << pos << endl;

    // Output leaf states
    for (int i = 0; i < leaves; i++) {
        if (i > 0) cout << " ";
        cout << state[(1 << (D - 1)) + i];
    }
    cout << endl;

    return 0;
}
