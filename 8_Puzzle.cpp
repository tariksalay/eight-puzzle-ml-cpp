#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>

using Board = std::array<int, 9>;
const Board goal{1, 2, 3, 4, 5, 6, 7, 8, 0};

int manhattan(const Board& board) {
    int distance = 0;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 0) continue;
        const int target = board[i] - 1;
        distance += std::abs(i / 3 - target / 3) + std::abs(i % 3 - target % 3);
    }
    return distance;
}

bool solvable(const Board& board) {
    int inversions = 0;
    for (int i = 0; i < 9; ++i)
        for (int j = i + 1; j < 9; ++j)
            if (board[i] && board[j] && board[i] > board[j]) ++inversions;
    return inversions % 2 == 0;
}

struct State {
    Board board;
    int moves;
    int estimate;
};
struct LowestEstimateFirst {
    bool operator()(const State& a, const State& b) const {
        if (a.estimate != b.estimate) return a.estimate > b.estimate;
        return a.moves < b.moves;
    }
};

std::vector<Board> solve(const Board& start) {
    std::priority_queue<State, std::vector<State>, LowestEstimateFirst> frontier;
    std::map<Board, int> best_moves{{start, 0}};
    std::map<Board, Board> parents;
    frontier.push({start, 0, manhattan(start)});
    while (!frontier.empty()) {
        const State state = frontier.top();
        frontier.pop();
        if (state.moves != best_moves.at(state.board)) continue;
        if (state.board == goal) {
            std::vector<Board> path;
            Board current = goal;
            while (true) {
                path.push_back(current);
                if (current == start) break;
                current = parents.at(current);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        const int blank = std::find(state.board.begin(), state.board.end(), 0) - state.board.begin();
        for (const int offset : {-3, 3, -1, 1}) {
            const int next = blank + offset;
            if (next < 0 || next >= 9) continue;
            if ((offset == -1 || offset == 1) && next / 3 != blank / 3) continue;
            Board board = state.board;
            std::swap(board[blank], board[next]);
            const int moves = state.moves + 1;
            const auto previous = best_moves.find(board);
            if (previous == best_moves.end() || moves < previous->second) {
                best_moves[board] = moves;
                parents[board] = state.board;
                frontier.push({board, moves, moves + manhattan(board)});
            }
        }
    }
    return {};
}

int main() {
    std::cout << "Enter the nine tiles (0 is the blank), separated by spaces:\n";
    Board start{};
    std::array<bool, 9> seen{};
    for (int& tile : start) {
        if (!(std::cin >> tile) || tile < 0 || tile > 8 || seen[tile]) {
            std::cerr << "Invalid puzzle: enter each integer from 0 to 8 exactly once.\n";
            return 1;
        }
        seen[tile] = true;
    }
    std::string extra;
    std::string remainder;
    std::getline(std::cin, remainder);
    std::istringstream remaining_input(remainder);
    if (remaining_input >> extra) {
        std::cerr << "Invalid puzzle: expected exactly nine tiles.\n";
        return 1;
    }
    if (!solvable(start)) {
        std::cerr << "This puzzle is unsolvable.\n";
        return 2;
    }
    const auto path = solve(start);
    if (path.empty()) return 2;
    std::cout << "Solution: " << path.size() - 1 << " moves\n";
    for (const Board& board : path) {
        for (int i = 0; i < 9; ++i) std::cout << board[i] << (i % 3 == 2 ? '\n' : ' ');
        std::cout << '\n';
    }
}
