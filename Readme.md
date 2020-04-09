# PA, First Homework - "Another day in GigeLand"

The first homework for the Algorithm Design Course. The problem statement can be found [here](./docs/problem_statement.pdf).

## Bani.cpp - First problem

There can be 2 types of instruction. For the first type, I realised that, for every bill, we can choose only 2 other types of bills. These makes the problem solvable just by computing `(typesOfBills) * (2 ^ (numberOfBills - 1))`, or `5 * 2 ^ (n-1)`. For the second type of instruction, the problem solution is a bit different.

We start by using the old solution: at every step, the current number of possibilities is equal the the old count times two `(count *= 2)`. Because the 200 bill "generates" 3 bills instead of two, we can add this extra to the count. So the formula is now `count = count * 2 + old200`, old200 being the number computed at the last step for the 200 bill.

To know this number, we need to compute this for each other bill type:

```cpp
count10  = (old50 + old100 + old500) % MOD;
count50  = (old10 + old200) % MOD;
count100 = (old10 + old100 + old200) % MOD;
count200 = (old50 + old500) % MOD;
count500 = (old200) % MOD;
```

*(To avoid overflow, we % MOD)*

**Time complexity**

- O(log n) instruction 1
- O(n) instruction 2

**Optimisations**

Initialy, I used a matrix to store the bill counts. However, this was not needed, as I only need the previous results, not all of them.

## Gard.cpp - Second Problem

I found that the problem can be solved more easily by sorting the initial array of fences, in the ascending order of their start and, when those are equal, in descending order of their ends.

Then we can simply check if a fence is included in any of the other fences in front of him (we only check if his end is smaller than the previous fences ends, as his start is guaranteed to be after theirs). If this happens, we update the count and "remove" the fence from the array.

**Time complexity**

- O(n log n) - sorting
- O(n^2) - solving the problem / program complexity

**Optimisations**

There are some small optimisations, the most important being the fact that we stop iterating through fences when the current one starts after the previous ones end.

```cpp
if (arr[j].start > arr[i].end) { break; }
```

## Bomboane.cpp - Third Problem

This is a problem that I solved using dynamic programming, somewhat similar to the knapsack problem, in the way that it uses a matrix to store the results of the subproblems. In my implementation, to reduce the memory usage, I only store the last and current results.

`newRes` - the array with the current results
`oldRes` - the array with the previous results

After both arrays are initialised to 0, I set oldRes[0] to 1. Then, I start iterating through the "students ranges" (the number of candies that can be given to each student), and compute the new array using this formula

`newRes[i] += oldRes[k] + oldRes[k+1] + ...`

Where `i` is the current index and `k = 0 or (i-rangeFinish) -> (i-rangeStart)` *(rangeStart, rangeFinish - the number of candies a student can have, as an interval)*

When we reach the "bottom-right corner" of the "results matrix" (or, in this case, `i = number of students` and `j = number of candies`), we return it, as it contains the result.

**Time complexity**

- O(n * m) - n is the number of students and m the number of candies. There is a constant that can appear (500), which is the "maximum range of candies" a student has.

**Optimisations**

There are two cases I treated sepparately, the case where we no solutions (by giving the maximum number of candies in the range for each student, we still do not give all the candies), and the case where we have only one solution (giving each student the maximym amount of candies). On a test, these reduced the execution time from 0.4 to 0.07 seconds.

© 2020 Grama Nicolae
