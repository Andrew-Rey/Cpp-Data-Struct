#include "Heuristic.h"
#include <cmath>
#include <iostream>

/*
	便于计算马哈顿距离，得到给定数码应在的位置。
	@grideSize: 数码问题的大小，8数码问题应该包括0-8，所以size为9
	@value: 数码的值

	样例：
	0 1 2
	3 4 5
	6 7 8

	Position position = getPosition(9, 5);	// 数码值5应该在的位置
	position的值应该为(1, 2)，也就是5应该在第2行第3列
*/
heuristic::Position heuristic::getPosition(int gridSize, int value) {
    int width = (int) sqrt(gridSize);
    return {value / width, value % width};
}

int heuristic::misplace(std::vector<int> &state, std::vector<int> &goalState) {
    /*
        h1 = the number of misplaced tiles.
        Example:
        Goal:
        0 1 2
        3 4 5
        6 7 8
        Current:
        7 2 4
        5 0 6
        8 3 1

        All the eight tiles are out of position, so the start state would have h1 = 8.
        h1 is an admissible heuristic because it is clear that any tile that is out of place must be moved at least once.

        Reference:
        3.6 HEURISTIC FUNCTIONS
    */
    // TODO
    int h1 = 0;
    if (state.empty() || goalState.empty()) return -1;
    for (auto it0 = state.begin(), it1 = goalState.begin();
         it0 != state.end() && it1 != goalState.end();
         ++it0, ++it1) {
        if (*it0 != *it1 && *it0 != 0) ++h1;
    }

    return h1;
}

int heuristic::manhattan(std::vector<int> &state, std::vector<int> &goalState) {
    /*
        h2 = the sum of the distances of the tiles from their goal positions.
        Example:
        Goal:
        0 1 2
        3 4 5
        6 7 8
        Current:
        7 2 4
        5 0 6
        8 3 1

        Because tiles cannot move along diagonals, the distance we will count is the sum of the horizontal
        and vertical distances. This is sometimes called the city block distance or Manhattan distance.
        h2 is also admissible because all any move can do is move one tile one step closer to the goal.
        Tiles 1 to 8 in the start state give a Manhattan distance of h2 = 3+1 + 2 + 2+ 2 + 3+ 3 + 2 = 18.

        Reference:
        3.6 HEURISTIC FUNCTIONS
    */
    //TODO:
    int h2 = 0;
    Position position0{}, position1{};
    for (int it0 : state) {
        position0 = getPosition(9, it0);
        for (int &it1 : goalState) {
            if (state[it0] == it1) {
                position1 = getPosition(9, it1);
                h2 += abs(position0.row - position1.row) + abs(position0.col - position1.col);
                break;
            }
        }
    }
    return h2;
}
