//                                         # Problem 22: Find the Length of a Longest Path in a Manhattan-like Grid

// Length of a Longest Path in the Manhattan Tourist Problem
// Find the length of a longest path in a rectangular city.
// Given: Integers n and m, followed by an n × (m+1) matrix Down and an (n+1) × m matrix Right. The two matrices are separated by the "-" symbol.
// Return: The length of a longest path from source (0, 0) to sink (n, m) in the n × m rectangular grid whose edges are defined by the matrices Down and Right.


// 4 4
// 1 0 2 4 3
// 4 6 5 2 1
// 4 4 5 2 1
// 5 6 8 5 3
// -
// 3 2 4 0
// 3 2 4 2
// 0 7 3 3
// 3 3 0 2
// 1 3 2 2

// 34

#include <iostream>
#include <vector>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> down(n, std::vector<int>(m + 1));
    std::vector<std::vector<int>> right(n + 1, std::vector<int>(m));
    std::vector<std::vector<int>> point(n + 1, std::vector<int>(m + 1));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m + 1; ++j) {
            std::cin >> down[i][j];
        }
    }

    std::cin.ignore(2);

    for(int i = 0; i < n + 1; ++i) {
        for(int j = 0; j < m; ++j) {
            std::cin >> right[i][j];
        }
    }

    point[0][0] = 0;
    for(int j = 0; j < m; ++j) {
        point[0][j + 1] = point[0][j] + right[0][j];
    }

    for(int i = 0; i < n; ++i) {
        point[i + 1][0] = point[i][0] + down[i][0];
    }

    for(int i = 1; i < n + 1; ++i) {
        for(int j = 1; j < m + 1; ++j) {
            int cur_down = point[i - 1][j] + down[i - 1][j];
            int cur_right = point[i][j - 1] + right[i][j - 1];
            point[i][j] = ((cur_down > cur_right) ? cur_down : cur_right);
        }
    }

    std::cout << point[n][m] << std::endl;
    return 0;
}