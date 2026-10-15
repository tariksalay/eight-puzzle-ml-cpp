# Code and artifact reference

[Overview](../README.md) · [Walkthrough](PROJECT_GUIDE.md) · [Development guide](DEVELOPMENT.md)

This reference describes the files on this branch. Function names are navigation aids; the walkthrough explains how their inputs, state, and outputs fit together.

## Solver components

All solver logic is in [8_Puzzle.cpp](../8_Puzzle.cpp).

| Component | Responsibility |
| --- | --- |
| `Board` | Fixed array of nine integers; row-major tiles, with `0` as the blank. |
| `manhattan` | Sum of tile distances from goal positions; excludes the blank. |
| `solvable` | Check the inversion parity appropriate to the 3×3 puzzle. |
| `State` | Board plus the move count and estimated remaining distance. |
| `LowestEstimateFirst` | Priority-queue ordering by total estimated path cost. |
| `solve` | Expand legal neighbors, keep best move counts, record parents, and reconstruct a shortest route. |
| `main` | Read and validate input, reject unsolvable boards, call search, and print the solution. |

## Search state

The frontier is a `std::priority_queue`. `best_moves` records the best discovered cost for each board; `parent` records the predecessor used to reconstruct the route. Stale queue entries are skipped. These structures exist only during one solve; there is no database or saved model.

## Inputs, outputs, and checks

[input.txt](../input.txt) and [prog1_output.txt](../prog1_output.txt) retain historical sample artifacts. Current runs print to standard output; they do not overwrite the old output file automatically. The historical executable is not the recommended entry point: compile the source using the development guide.

The [test directory](../tests/) checks compilation, legal/optimal paths on bounded BFS samples and a difficult board, plus invalid and unsolvable input. Read the walkthrough for exit statuses and an end-to-end example.
