# Eight Puzzle Solver — C++ Heuristic Search

**C++ · Priority Queue · Manhattan Distance · State-Space Search**

A command-line solver for the classic 3×3 sliding-tile puzzle. The program explores puzzle states and prioritizes candidates using a cost function based on path length plus Manhattan distance from each tile to its goal position.

## Approach

1. Read nine tile values from standard input, where `0` represents the blank space.
2. Represent the 3×3 board as nested C++ vectors.
3. Generate neighboring boards by swapping the blank tile up, down, left, or right.
4. Calculate a Manhattan-distance heuristic and use a priority queue to choose states.
5. Track visited states and parent relationships; print a sequence of boards when the target is reached.

The goal position is:

```text
1 2 3
4 5 6
7 8 0
```

## Code and files

- [8_Puzzle.cpp](8_Puzzle.cpp) — complete C++ source.
- [input.txt](input.txt) — example input file included in the repository.
- [8_Puzzle.exe](8_Puzzle.exe) — historical compiled Windows executable.
- [prog1_output.txt](prog1_output.txt) — output file placeholder.

## Building and experimenting

The source uses the GCC-specific header `<bits/stdc++.h>`, so GCC/G++ is a practical choice:

```bash
g++ -std=c++17 -O2 8_Puzzle.cpp -o eight_puzzle
./eight_puzzle
```

Enter nine values when prompted, for example:

```text
1 2 3 4 5 6 7 0 8
```

These commands are based on source inspection; compilation and runtime behavior have not been verified for this documentation update.

## Video

[Original demonstration on Vimeo](https://vimeo.com/373321351)

## Notes and limitations

The code is inspired by A*-style heuristic search but does not currently establish full A* correctness or guaranteed optimal paths: its queue comparator, handling of path costs, and visited-state strategy warrant further review. It also lacks an explicit solvability test for unsolvable initial arrangements.

This repository is an algorithms exercise, **not a model trained on data**.

[GitHub profile](https://github.com/tariksalay)
