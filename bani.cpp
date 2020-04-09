// Copyright Grama Nicolae 2020
#include <fstream>
#include <vector>

std::fstream in("bani.in");
std::ofstream out("bani.out");

#define lint unsigned long int
#define MOD 1000000007

lint solve(lint n) {
    lint count = 5;

    // The current number of bills of the different types
    lint count10, count50, count100, count200, count500;

    // The old number of bills of the different types
    // (first time, we can use any of the bills)
    lint old10 = 1, old50 = 1, old100 = 1, old200 = 1, old500 = 1;

    while (n > 1) {
        // Compute the new counts
        count = (count * 2 + old200) % MOD;
        count10 = (old50 + old100 + old500) % MOD;
        count50 = (old10 + old200) % MOD;
        count100 = (old10 + old100 + old200) % MOD;
        count200 = (old50 + old500) % MOD;
        count500 = (old200) % MOD;

        // Update the old counts for the next iteration
        old10 = count10;
        old50 = count50;
        old100 = count100;
        old200 = count200;
        old500 = count500;

        // "Increase" the current number of bills used
        n--;
    }

    return count;
}

// Compute x to the power y in O(log y) time
lint power(lint x, lint y) {
    lint res = 1;
    while (y > 0) {
        if (y % 2 == 1) {
            res = res * x;
            res %= MOD;
        }

        y = y >> 1;
        x = x * x;
        x %= MOD;
    }
    return res;
}

int main() {
    lint n;
    short type;
    in >> type >> n;
    in.close();

    // For the first type, the number of combinations is
    // 5 * (2 ^ (n - 1))
    if (type == 1) {
        lint pow = 5;

        pow *= power(2, n - 1);
        pow %= MOD;
        out << pow << "\n";
        out.close();
        return 0;
    }

    // Type = 2
    out << solve(n) << "\n";

    out.close();
    return 0;
}
