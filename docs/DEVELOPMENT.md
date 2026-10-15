# Development and validation

Build with a C++17 compiler:

```sh
mkdir -p build
g++ -std=c++17 -O2 -Wall -Wextra -Werror 8_Puzzle.cpp -o build/eight-puzzle
printf '0 1 3 4 2 5 7 8 6\n' | build/eight-puzzle
python -m unittest discover -s tests -v
```

A* now orders states by `moves_so_far + Manhattan_distance`, updates a state's best known cost, and reconstructs an optimal path. Invalid inputs exit with status 1; unsolvable puzzles exit with status 2. Input can be one line or three rows. The committed Windows executable is retained as a historical artifact; rebuild the source to use these fixes. Existing output examples describe the earlier implementation.

Validation compares legal solution paths and optimal move counts against breadth-first search, tests a 31-move puzzle, and rejects malformed/unsolvable boards.
