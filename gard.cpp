// Copyright Grama Nicolae 2020
#include <algorithm>
#include <fstream>
#include <vector>

std::fstream in("gard.in");
std::ofstream out("gard.out");

#define lint unsigned long int

struct Fence {
    int start, end;

    // By convention, a fence is null if it starts at -1
    bool isNull() { return (start == -1); }
};

// Comparator for std::sort
bool isSmaller(const Fence first, const Fence other) {
    if (first.start == other.start) {
        return first.end > other.end;
    }
    return first.start < other.start;
}

lint solve(std::vector<Fence> arr) {
    // Sort the array in O(n log n), in ascending order of the fence start
    // and descending order of fence end
    sort(arr.begin(), arr.end(), isSmaller);
    lint count = 0;

    // For each fence
    for (lint i = 0; i < arr.size() - 1; ++i) {
        if (!arr[i].isNull()) {
            for (lint j = i + 1; j < arr.size(); ++j) {
                // If this wasn't counted/removed already
                if (!arr[j].isNull()) {
                    if (arr[i].end >= arr[j].end) {
                        // Update count
                        count++;
                        count %= 1000000007;

                        // Remove the fence
                        arr[j].start = -1;
                    }

                    // After this point, is guaranteed we won't find any fence
                    // that is contained in "i" fence
                    if (arr[j].start > arr[i].end) {
                        break;
                    }
                }
            }
        }
    }

    return count;
}

int main() {
    // Read input
    std::vector<Fence> arr;
    lint n;
    in >> n;
    for (lint i = 0; i < n; ++i) {
        Fence f;
        in >> f.start >> f.end;
        arr.push_back(f);
    }
    in.close();

    // Solve problem
    out << solve(arr) << "\n";

    out.close();
    return 0;
}
