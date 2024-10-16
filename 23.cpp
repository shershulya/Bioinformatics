//                                         # Problem 23: Find a Highest-Scoring Alignment of Two Strings

// Global Alignment Problem
// Find the highest-scoring alignment between two strings using a scoring matrix.
// Given: Two amino acid strings.
// Return: The maximum alignment score of these strings followed by an alignment achieving this maximum score.
// Use the BLOSUM62 scoring matrix and indel penalty σ = 5. (If multiple alignments achieving the maximum score exist, you may return any one.)


// PLEASANTLY
// MEANLY

// 8
// PLEASANTLY
// -MEA--N-LY

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::map<char, int> blosum_index = {
    {'A',  0},
    {'C',  1},
    {'D',  2},
    {'E',  3},
    {'F',  4},
    {'G',  5},
    {'H',  6},
    {'I',  7},
    {'K',  8},
    {'L',  9},
    {'M', 10},
    {'N', 11},
    {'P', 12},
    {'Q', 13},
    {'R', 14},
    {'S', 15},
    {'T', 16},
    {'V', 17},
    {'W', 18},
    {'Y', 19}
};

 std::vector<std::vector<int>> blosum = {
    { 4,  0, -2, -1, -2,  0, -2, -1, -1, -1, -1, -2, -1, -1, -1,  1,  0,  0, -3, -2},
    { 0,  9, -3, -4, -2, -3, -3, -1, -3, -1, -1, -3, -3, -3, -3, -1, -1, -1, -2, -2},
    {-2, -3,  6,  2, -3, -1, -1, -3, -1, -4, -3,  1, -1,  0, -2,  0, -1, -3, -4, -3},
    {-1, -4,  2,  5, -3, -2,  0, -3,  1, -3, -2,  0, -1,  2,  0,  0, -1, -2, -3, -2},
    {-2, -2, -3, -3,  6, -3, -1,  0, -3,  0,  0, -3, -4, -3, -3, -2, -2, -1,  1,  3},
    { 0, -3, -1, -2, -3,  6, -2, -4, -2, -4, -3,  0, -2, -2, -2,  0, -2, -3, -2, -3},
    {-2, -3, -1,  0, -1, -2,  8, -3, -1, -3, -2,  1, -2,  0,  0, -1, -2, -3, -2,  2},
    {-1, -1, -3, -3,  0, -4, -3,  4, -3,  2,  1, -3, -3, -3, -3, -2, -1,  3, -3, -1},
    {-1, -3, -1,  1, -3, -2, -1, -3,  5, -2, -1,  0, -1,  1,  2,  0, -1, -2, -3, -2},
    {-1, -1, -4, -3,  0, -4, -3,  2, -2,  4,  2, -3, -3, -2, -2, -2, -1,  1, -2, -1},
    {-1, -1, -3, -2,  0, -3, -2,  1, -1,  2,  5, -2, -2,  0, -1, -1, -1,  1, -1, -1},
    {-2, -3,  1,  0, -3,  0,  1, -3,  0, -3, -2,  6, -2,  0,  0,  1,  0, -3, -4, -2},
    {-1, -3, -1, -1, -4, -2, -2, -3, -1, -3, -2, -2,  7, -1, -2, -1, -1, -2, -4, -3},
    {-1, -3,  0,  2, -3, -2,  0, -3,  1, -2,  0,  0, -1,  5,  1,  0, -1, -2, -2, -1},
    {-1, -3, -2,  0, -3, -2,  0, -3,  2, -2, -1,  0, -2,  1,  5, -1, -1, -3, -3, -2},
    { 1, -1,  0,  0, -2,  0, -1, -2,  0, -2, -1,  1, -1,  0, -1,  4,  1, -2, -3, -2},
    { 0, -1, -1, -1, -2, -2, -2, -1, -1, -1, -1,  0, -1, -1, -1,  1,  5,  0, -2, -2},
    { 0, -1, -3, -2, -1, -3, -3,  3, -2,  1,  1, -3, -2, -2, -3, -2,  0,  4, -3, -1},
    {-3, -2, -4, -3,  1, -2, -2, -3, -3, -2, -1, -4, -4, -2, -3, -3, -2, -3, 11,  2},
    {-2, -2, -3, -2,  3, -3,  2, -1, -2, -1, -1, -2, -3, -1, -2, -2, -2, -1,  2,  7}
                                        };

int main(void) {
    std::string first, second;
    std::cin >> first >> second;


    int n, m;
    n = first.length();
    m = second.length();
    
    std::vector<std::vector<int>> down(n, std::vector<int>(m + 1));
    std::vector<std::vector<int>> right(n + 1, std::vector<int>(m));
    std::vector<std::vector<int>> diag(n, std::vector<int>(m));
    std::vector<std::vector<int>> point(n + 1, std::vector<int>(m + 1));

    std::vector<std::vector<char>> path(n + 1, std::vector<char>(m + 1));

    int indel_penalty = -5;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m + 1; ++j) {
            down[i][j] = indel_penalty;
        }
    }

    for(int i = 0; i < n + 1; ++i) {
        for(int j = 0; j < m; ++j) {
            right[i][j] = indel_penalty;
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            diag[i][j] = blosum[blosum_index[first[i]]][blosum_index[second[j]]];
        }
    }

    point[0][0] = 0;
    path[0][0] = 'X';
    for(int j = 0; j < m; ++j) {
        point[0][j + 1] = point[0][j] + right[0][j];
        path[0][j + 1] = 'r';
    }

    for(int i = 0; i < n; ++i) {
        point[i + 1][0] = point[i][0] + down[i][0];
        path[i + 1][0] = 'f';
    }

    for(int i = 1; i < n + 1; ++i) {
        for(int j = 1; j < m + 1; ++j) {
            int cur_down = point[i - 1][j] + down[i - 1][j];
            int cur_right = point[i][j - 1] + right[i][j - 1];
            int cur_diag = point[i - 1][j - 1] + diag[i - 1][j - 1];

            int tmp = (cur_down > cur_diag) ? cur_down : cur_diag;
            char tmp_c = (cur_down > cur_diag) ? 'f' : 'd';

            point[i][j] = (cur_right > tmp) ? cur_right : tmp;
            path[i][j] = (cur_right > tmp) ? 'r' : tmp_c;
        }
    }

    std::cout << point[n][m] << std:: endl;

    int i = n;
    int j = m;
    std::string first_align, second_align;
    while (i != 0 || j != 0) {
        if (path[i][j] == 'r') {
            first_align += '-';
            second_align += second[j - 1];
            j -= 1;
        } else if (path[i][j] == 'f') {
            first_align += first[i - 1];
            second_align += '-';
            i -= 1;
        } else if (path[i][j] == 'd') {
            first_align += first[i - 1];
            second_align += second[j - 1];
            i -= 1;
            j -= 1;
        }
    }

    std::reverse(first_align.begin(), first_align.end());
    std::reverse(second_align.begin(), second_align.end());
    std::cout << first_align << std::endl;
    std::cout << second_align << std::endl;
    return 0;
}