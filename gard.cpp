// Copyright Grama Nicolae 2020
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

fstream in("gard.in");
ofstream out("gard.out");

#define lint long int

struct Fence {
    lint start, end;
};

bool isSmaller(Fence f1, Fence f2) {
    if (f1.start == f2.start) {
        return f1.end > f2.end;
    }
    return f1.start < f2.start;
}

bool isEqual(Fence f1, Fence f2) {
    return (f1.start == f2.start) && (f1.end == f2.end);
}

bool isNull(Fence f1) { return (f1.start == -1); }

void solve(vector<Fence> arr) {
    sort(arr.begin(), arr.end(), isSmaller);
    lint count = 0;

    Fence* list = (Fence*)malloc(arr.size() * sizeof(Fence));
    for (lint i = 0; i < arr.size(); ++i) {
        list[i] = arr[i];
    }

    for (lint i = 0; i < arr.size() - 1; ++i) {
        if (!isNull(list[i])) {
            for (lint j = i + 1; j < arr.size(); ++j) {
                // If this wasn't counted already
                if (!isNull(list[j])) {
                    if (list[i].end >= list[j].end) {
                        count++;
                        count %= 1000000007;
                        list[j].start = -1;
                    }

                    if (list[j].start > list[i].end) {
                        break;
                    }
                }
            }
        }
    }

    free(list);
    out << count << "\n";
}

int main() {
    vector<Fence> arr;
    lint n;
    in >> n;
    for (int i = 0; i < n; ++i) {
        Fence f;
        in >> f.start >> f.end;
        arr.push_back(f);
    }

    solve(arr);
    in.close();
    out.close();
    return 0;
}
