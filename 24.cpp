//                                         # Problem 24: Find a Highest-Scoring Local Alignment of Two Strings

// Local Alignment Problem
// Find the highest-scoring local alignment between two strings.
// Given: Two amino acid strings.
// Return: The maximum score of a local alignment of the strings, followed by a local alignment of these strings achieving the maximum score.
// Use the PAM250 scoring matrix and indel penalty σ = 5. (If multiple local alignments achieving the maximum score exist, you may return any one.)


// MEANLY
// PENALTY

// 15
// EANL-Y
// ENALTY

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::map<char, int> pam_index = {
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

 std::vector<std::vector<int>> pam = {
    { 2, -2,  0,  0, -3,  1, -1, -1, -1, -2, -1,  0,  1,  0, -2,  1,  1,  0, -6, -3},
    {-2, 12, -5, -5, -4, -3, -3, -2, -5, -6, -5, -4, -3, -5, -4,  0, -2, -2, -8,  0},
    { 0, -5,  4,  3, -6,  1,  1, -2,  0, -4, -3,  2, -1,  2, -1,  0,  0, -2, -7, -4},
    { 0, -5,  3,  4, -5,  0,  1, -2,  0, -3, -2,  1, -1,  2, -1,  0,  0, -2, -7, -4},
    {-3, -4, -6, -5,  9, -5, -2,  1, -5,  2,  0, -3, -5, -5, -4, -3, -3, -1,  0,  7},
    { 1, -3,  1,  0, -5,  5, -2, -3, -2, -4, -3,  0,  0, -1, -3,  1,  0, -1, -7, -5},
    {-1, -3,  1,  1, -2, -2,  6, -2,  0, -2, -2,  2,  0,  3,  2, -1, -1, -2, -3,  0},
    {-1, -2, -2, -2,  1, -3, -2,  5, -2,  2,  2, -2, -2, -2, -2, -1,  0,  4, -5, -1},
    {-1, -5,  0,  0, -5, -2,  0, -2,  5, -3,  0,  1, -1,  1,  3,  0,  0, -2, -3, -4},
    {-2, -6, -4, -3,  2, -4, -2,  2, -3,  6,  4, -3, -3, -2, -3, -3, -2,  2, -2, -1},
    {-1, -5, -3, -2,  0, -3, -2,  2,  0,  4,  6, -2, -2, -1,  0, -2, -1,  2, -4, -2},
    { 0, -4,  2,  1, -3,  0,  2, -2,  1, -3, -2,  2,  0,  1,  0,  1,  0, -2, -4, -2},
    { 1, -3, -1, -1, -5,  0,  0, -2, -1, -3, -2,  0,  6,  0,  0,  1,  0, -1, -6, -5},
    { 0, -5,  2,  2, -5, -1,  3, -2,  1, -2, -1,  1,  0,  4,  1, -1, -1, -2, -5, -4},
    {-2, -4, -1, -1, -4, -3,  2, -2,  3, -3,  0,  0,  0,  1,  6,  0, -1, -2,  2, -4},
    { 1,  0,  0,  0, -3,  1, -1, -1,  0, -3, -2,  1,  1, -1,  0,  2,  1, -1, -2, -3},
    { 1, -2,  0,  0, -3,  0, -1,  0,  0, -2, -1,  0,  0, -1, -1,  1,  3,  0, -5, -3},
    { 0, -2, -2, -2, -1, -1, -2,  4, -2,  2,  2, -2, -1, -2, -2, -1,  0,  4, -6, -2},
    {-6, -8, -7, -7,  0, -7, -3, -5, -3, -2, -4, -4, -6, -5,  2, -2, -5, -6, 17,  0},
    {-3,  0, -4, -4,  7, -5,  0, -1, -4, -1, -2, -2, -5, -4, -4, -3, -3, -2,  0, 10}
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
            diag[i][j] = pam[pam_index[first[i]]][pam_index[second[j]]];
        }
    }

    point[0][0] = 0;
    path[0][0] = 'X';
    for(int j = 0; j < m; ++j) {
        point[0][j + 1] = 0;
        path[0][j + 1] = 't';
    }

    for(int i = 0; i < n; ++i) {
        point[i + 1][0] = 0;
        path[i + 1][0] = 't';
    }

    for(int i = 1; i < n + 1; ++i) {
        for(int j = 1; j < m + 1; ++j) {
            int cur_down = point[i - 1][j] + down[i - 1][j];
            int cur_right = point[i][j - 1] + right[i][j - 1];
            int cur_diag = point[i - 1][j - 1] + diag[i - 1][j - 1];

            int tmp1 = (cur_down > cur_diag) ? cur_down : cur_diag;
            char tmp1_c = (cur_down > cur_diag) ? 'f' : 'd';

            int tmp2 = (cur_right > tmp1) ? cur_right : tmp1;
            char tmp2_c = (cur_right > tmp1) ? 'r' : tmp1_c;

            point[i][j] = (0 > tmp2) ? 0 : tmp2;
            path[i][j] = (0 > tmp2) ? 't' : tmp2_c;
        }
    }

    int max_i = 0;
    int max_j = 0;
    int max_point = 0;
    for(int i = 1; i < n + 1; ++i) {
        for(int j = 1; j < m + 1; ++j) {
            if (point[i][j] > max_point) {
                max_point = point[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    std::cout << max_point << std:: endl;

    int i = max_i;
    int j = max_j;
    std::string first_align, second_align;
    while (i != 0 || j != 0) {
        if (path[i][j] == 't') {
            break;
        } else if (path[i][j] == 'r') {
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