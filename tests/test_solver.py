"""Compile once and compare A* solutions against an independent breadth-first search."""
from collections import deque
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
GOAL = (1, 2, 3, 4, 5, 6, 7, 8, 0)


def adjacent(board):
    blank = board.index(0)
    for offset in (-3, 3, -1, 1):
        other = blank + offset
        if not 0 <= other < 9 or (abs(offset) == 1 and blank // 3 != other // 3):
            continue
        nxt = list(board)
        nxt[blank], nxt[other] = nxt[other], nxt[blank]
        yield tuple(nxt)


class SolverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory()
        cls.binary = str(Path(cls.temp.name) / 'eight-puzzle')
        subprocess.run(['g++', '-std=c++17', '-Wall', '-Wextra', '-Werror', '-O2',
                        str(ROOT / '8_Puzzle.cpp'), '-o', cls.binary], check=True)

    @classmethod
    def tearDownClass(cls):
        cls.temp.cleanup()

    def run_solver(self, tiles):
        return subprocess.run([self.binary], input=tiles, text=True, capture_output=True, timeout=15)

    def test_shortest_paths_and_legal_moves(self):
        distances = {GOAL: 0}
        pending = deque([GOAL])
        while pending:
            board = pending.popleft()
            if distances[board] == 8:
                continue
            for nxt in adjacent(board):
                if nxt not in distances:
                    distances[nxt] = distances[board] + 1
                    pending.append(nxt)
        for board in list(distances)[::max(1, len(distances) // 30)]:
            result = self.run_solver(' '.join(map(str, board)))
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertIn(f'Solution: {distances[board]} moves', result.stdout)
            rows = [tuple(map(int, line.split())) for line in result.stdout.splitlines()
                    if len(line.split()) == 3 and line.replace(' ', '').isdigit()]
            path = [sum(rows[i:i + 3], ()) for i in range(0, len(rows), 3)]
            self.assertEqual(path[0], board)
            self.assertEqual(path[-1], GOAL)
            for a, b in zip(path, path[1:]):
                self.assertIn(b, list(adjacent(a)))

    def test_hardest_known_distance(self):
        result = self.run_solver('8 6 7 2 5 4 3 0 1')
        self.assertEqual(result.returncode, 0)
        self.assertIn('Solution: 31 moves', result.stdout)

    def test_invalid_and_unsolvable(self):
        for tiles in ('0 0 1 2 3 4 5 6 7', '1 2', '9 1 2 3 4 5 6 7 8',
                      'one 2 3 4 5 6 7 8 0', '1 2 3 4 5 6 7 8 0 extra'):
            self.assertEqual(self.run_solver(tiles).returncode, 1)
        self.assertEqual(self.run_solver('1 2 3 4 5 6 8 7 0').returncode, 2)


if __name__ == '__main__':
    unittest.main()
