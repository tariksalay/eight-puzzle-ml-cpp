# Eight Puzzle Solver

**C++17 · A* search · Manhattan distance · Priority queue**

A command-line solver for a 3×3 sliding-tile puzzle. It validates the board, checks whether the target can be reached, and prints a shortest sequence of legal moves to the goal.

## What this project demonstrates

- State-space search with a Manhattan-distance heuristic.
- Best-cost tracking and reconstruction of a solution path.
- Input validation and independent shortest-path checks.

## Start here

| Read | Use it for |
| --- | --- |
| [Project walkthrough](docs/PROJECT_GUIDE.md) | Purpose, workflow, repository map, and a concrete example |
| [Code and artifact reference](docs/CODE_REFERENCE.md) | Important files, functions, classes, and their responsibilities |
| [Development guide](docs/DEVELOPMENT.md) | Setup, configuration, commands, tests, and remaining limitations |

## Explore locally

```sh
mkdir -p build
g++ -std=c++17 -O2 -Wall -Wextra -Werror 8_Puzzle.cpp -o build/eight-puzzle
printf '1 2 3 4 5 6 7 0 8\n' | build/eight-puzzle
python -m unittest discover -s tests -v
```

## Validation and scope

An algorithms learning project, with three passing test groups covering shortest paths, a known 31-move puzzle, and invalid/unsolvable input. There is no trained machine-learning model. The committed Windows executable is a historical build; compile the current source to use this implementation.

[Original demonstration](https://vimeo.com/373321351) describes the earlier project version.

---

[GitHub profile](https://github.com/tariksalay) · [Portfolio](https://tariksalay.github.io/) · [Earlier README](README_HISTORY.md)

The earlier README is preserved as historical context; the guides above describe this branch's implementation.
