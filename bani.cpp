// Copyright Grama Nicolae 2020
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

std::fstream in("bani.in");
std::ofstream out("bani.out");

#define lint long int

lint solve(lint n) {
    lint count = 5;

    lint count10, count50, count100, count200, count500;
    lint old10 = 1, old50 = 1, old100 = 1, old200 = 1, old500 = 1;

    while (n > 1) {
        count = (count * 2 + old200) % 1000000007;
        count10 = (old50 + old100 + old500) % 1000000007;
        count50 = (old10 + old200) % 1000000007;
        count100 = (old10 + old100 + old200) % 1000000007;
        count200 = (old50 + old500) % 1000000007;
        count500 = (old200) % 1000000007;

        old10 = count10;
        old50 = count50;
        old100 = count100;
        old200 = count200;
        old500 = count500;
        n--;
    }

    return count;
}

lint power(lint x, unsigned int y) {
    lint res = 1;  // Initialize result

    while (y > 0) {
        // If y is odd, multiply x with result
        if (y & 1) {
            res = res * x;
            res %= 1000000007;
        }

        // n must be even now
        y = y >> 1;  // y = y/2
        x = x * x;   // Change x to x^2
        x %= 1000000007;
    }
    return res;
}

int main() {
    lint n;
    short type;
    in >> type >> n;

    if (type == 1) {
        lint pow = 5;

        pow *= power(2, n - 1);
        pow %= 1000000007;
        out << pow << "\n";
        return 0;
    }

    out << solve(n) << "\n";
    in.close();
    out.close();
    return 0;
}
