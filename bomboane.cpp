// Copyright Grama Nicolae 2020
#include <memory.h>
#include <fstream>
#include <vector>

std::fstream in("bomboane.in");
std::ofstream out("bomboane.out");

#define lint long int

typedef struct {
    lint start;
    lint finish;
} range;

lint solve(std::vector<range> arr, lint candies) {
    lint *oldRes, *newRes;

    // Two arrays that store intermediate results
    oldRes = (lint *)calloc(sizeof(lint), (candies + 1));
    newRes = (lint *)calloc(sizeof(lint), (candies + 1));

    oldRes[0] = 1;

    // For each student's range
    for (lint i = 1; i <= (lint)arr.size(); ++i) {
        range r = arr[i - 1];

        // Iterate the array from it's tail
        for (lint j = candies; j >= 0; j--) {
            // Compute the new values using the old values
            for (lint c = j - r.start; c >= j - r.finish; c--) {
                if (c < 0) {
                    break;
                }

                newRes[j] = (oldRes[c] + newRes[j]) % 1000000007;
            }

            // If we reached the "bottom-right corner of the matrix
            // return the result
            if (i == (lint)arr.size() && j == candies) {
                lint count = newRes[candies];
                free(newRes);
                free(oldRes);
                return count;
            }
        }

        // Update the old results array and prepare the new one
        memcpy(oldRes, newRes, (candies + 1) * sizeof(lint));
        memset(newRes, 0, (candies + 1) * sizeof(lint));
    }

    free(newRes);
    free(oldRes);
    return 0;
}

int main() {
    // Read data
    lint stud_c, candy_c;
    in >> stud_c >> candy_c;

    lint maxSum = 0;

    std::vector<range> ranges;
    for (int i = 0; i < stud_c; ++i) {
        range r;
        in >> r.start >> r.finish;
        ranges.push_back(r);
        maxSum += r.finish;
    }
    in.close();

    // Treat some simple cases
    if (maxSum < candy_c) {
        out << 0 << "\n";
        out.close();
        return 0;
    } else if (maxSum == candy_c) {
        out << 1 << "\n";
        out.close();
        return 0;
    }

    // Compute the required number
    out << solve(ranges, candy_c) << "\n";

    out.close();
    return 0;
}
