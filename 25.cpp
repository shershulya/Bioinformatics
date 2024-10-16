//                                         # Problem 25: Find a Highest-Scoring Multiple Sequence Alignment

// Multiple Longest Common Subsequence Problem
// Find a longest common subsequence of multiple strings.
// Given: Three DNA strings.
// Return: The maximum score of a multiple alignment of these three strings, followed by a multiple alignment of the three strings achieving this maximum.
// Use a scoring function in which the score of an alignment column is 1 if all three symbols are identical and 0 otherwise.
// (If more than one multiple alignment achieve the maximum, you may return any one.)


// ATATCCG
// TCCGA
// ATGTACTG

// 3
// ATATCC-G-
// ---TCC-GA
// ATGTACTG-

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

int main(void) {
    std::string first, second, third;
    std::cin >> first >> second >> third;


    int n, m, l;
    n = first.length();
    m = second.length();
    l = third.length();
    
    std::vector<std::vector<std::vector<int>>> down(n, std::vector<std::vector<int>>((m + 1), std::vector<int>(l + 1)));
    std::vector<std::vector<std::vector<int>>> left((n + 1), std::vector<std::vector<int>>((m + 1), std::vector<int>(l)));
    std::vector<std::vector<std::vector<int>>> right((n + 1), std::vector<std::vector<int>>(m, std::vector<int>(l + 1)));
    std::vector<std::vector<std::vector<int>>> diag_left(n, std::vector<std::vector<int>>((m + 1), std::vector<int>(l)));
    std::vector<std::vector<std::vector<int>>> diag_right(n, std::vector<std::vector<int>>(m, std::vector<int>(l + 1)));
    std::vector<std::vector<std::vector<int>>> diag_up((n + 1), std::vector<std::vector<int>>(m, std::vector<int>(l)));
    std::vector<std::vector<std::vector<int>>> diag(n, std::vector<std::vector<int>>(m, std::vector<int>(l)));

    std::vector<std::vector<std::vector<int>>> point((n + 1), std::vector<std::vector<int>>((m + 1), std::vector<int>(l + 1)));
    std::vector<std::vector<std::vector<char>>> path((n + 1), std::vector<std::vector<char>>((m + 1), std::vector<char>(l + 1)));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m + 1; ++j) {
            for(int k = 0; k < l + 1; ++k) {
                down[i][j][k] = 0;
            }
        }
    }

    for(int i = 0; i < n + 1; ++i) {
        for(int j = 0; j < m + 1; ++j) {
            for(int k = 0; k < l; ++k) {
                left[i][j][k] = 0;
            }
        }
    }

    for(int i = 0; i < n + 1; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < l + 1; ++k) {
                right[i][j][k] = 0;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m + 1; ++j) {
            for(int k = 0; k < l; ++k) {
                diag_left[i][j][k] = 0;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < l + 1; ++k) {
                diag_right[i][j][k] = 0;
            }
        }
    }

    for(int i = 0; i < n + 1; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < l; ++k) {
                diag_up[i][j][k] = 0;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < l; ++k) {
                diag[i][j][k] = ((first[i] == second[j] && second[j] == third[k]) ? 1 : 0);
            }
        }
    }

    point[0][0][0] = 0;
    path[0][0][0] = 'Q';

    for(int j = 0; j < m; ++j) {
        point[0][j + 1][0] = point[0][j][0] + right[0][j][0];
        path[0][j + 1][0] = 'r';
    }

    for(int i = 0; i < n; ++i) {
        point[i + 1][0][0] = point[i][0][0] + down[i][0][0];
        path[i + 1][0][0] = 'f';
    }

    for(int k = 0; k < l; ++k) {
        point[0][0][k + 1] = point[0][0][k] + left[0][0][k];
        path[0][0][k + 1] = 'l';
    }

    for(int i = 1; i < n + 1; ++i) {
        for(int j = 1; j < m + 1; ++j) {
            int cur_down = point[i - 1][j][0] + down[i - 1][j][0];
            int cur_right = point[i][j - 1][0] + right[i][j - 1][0];
            int cur_diag_right = point[i - 1][j - 1][0] + diag_right[i - 1][j - 1][0];

            int tmp1 = (cur_down > cur_diag_right) ? cur_down : cur_diag_right;
            char tmp1_c = (cur_down > cur_diag_right) ? 'f' : 'x';

            int tmp2 = (cur_right > tmp1) ? cur_right : tmp1;
            char tmp2_c = (cur_right > tmp1) ? 'r' : tmp1_c;

            point[i][j][0] = tmp2;
            path[i][j][0] = tmp2_c;
        }
    }

    for(int i = 1; i < n + 1; ++i) {
        for(int k = 1; k < l + 1; ++k) {
            int cur_down = point[i - 1][0][k] + down[i - 1][0][k];
            int cur_left = point[i][0][k - 1] + left[i][0][k - 1];
            int cur_diag_left = point[i - 1][0][k - 1] + diag_left[i - 1][0][k - 1];

            int tmp1 = (cur_down > cur_diag_left) ? cur_down : cur_diag_left;
            char tmp1_c = (cur_down > cur_diag_left) ? 'f' : 'y';

            int tmp2 = (cur_left > tmp1) ? cur_left : tmp1;
            char tmp2_c = (cur_left > tmp1) ? 'l' : tmp1_c;

            point[i][0][k] = tmp2;
            path[i][0][k] = tmp2_c;
        }
    }

    for(int j = 1; j < m + 1; ++j) {
        for(int k = 1; k < l + 1; ++k) {
            int cur_left = point[0][j][k - 1] + left[0][j][k - 1];
            int cur_right = point[0][j - 1][k] + right[0][j - 1][k];
            int cur_diag_up = point[0][j - 1][k - 1] + diag_up[0][j - 1][k - 1];

            int tmp1 = (cur_right > cur_diag_up) ? cur_right : cur_diag_up;
            char tmp1_c = (cur_right > cur_diag_up) ? 'r' : 'z';

            int tmp2 = (cur_left > tmp1) ? cur_left : tmp1;
            char tmp2_c = (cur_left > tmp1) ? 'l' : tmp1_c;

            point[0][j][k] = tmp2;
            path[0][j][k] = tmp2_c;
        }
    }

    for(int i = 1; i < n + 1; ++i) {
        for(int j = 1; j < m + 1; ++j) {
            for(int k = 1; k < l + 1; ++k) {
                int cur_down = point[i - 1][j][k] + down[i - 1][j][k];
                int cur_left = point[i][j][k - 1] + left[i][j][k - 1];
                int cur_right = point[i][j - 1][k] + right[i][j - 1][k];

                int cur_diag_up = point[i][j - 1][k - 1] + diag_up[i][j - 1][k - 1];
                int cur_diag_left = point[i - 1][j][k - 1] + diag_left[i - 1][j][k - 1];
                int cur_diag_right = point[i - 1][j - 1][k] + diag_right[i - 1][j - 1][k];

                int cur_diag = point[i - 1][j - 1][k - 1] + diag[i - 1][j - 1][k - 1];

                int tmp1 = (cur_down > cur_diag) ? cur_down : cur_diag;
                char tmp1_c = (cur_down > cur_diag) ? 'f' : 'd';

                int tmp2 = (cur_left > tmp1) ? cur_left : tmp1;
                char tmp2_c = (cur_left > tmp1) ? 'l' : tmp1_c;

                int tmp3 = (cur_right > tmp2) ? cur_right : tmp2;
                char tmp3_c = (cur_right > tmp2) ? 'r' : tmp2_c;

                int tmp4 = (cur_diag_up > tmp3) ? cur_diag_up : tmp3;
                char tmp4_c = (cur_diag_up > tmp3) ? 'z' : tmp3_c;

                int tmp5 = (cur_diag_left > tmp4) ? cur_diag_left : tmp4;
                char tmp5_c = (cur_diag_left > tmp4) ? 'y' : tmp4_c;

                int tmp6 = (cur_diag_right > tmp5) ? cur_diag_right : tmp5;
                char tmp6_c = (cur_diag_right > tmp5) ? 'x' : tmp5_c;

                point[i][j][k] = tmp6;
                path[i][j][k] = tmp6_c;
            }
        }
    }

    std::cout << point[n][m][l] << std:: endl;

    int i = n;
    int j = m;
    int k = l;
    std::string first_align, second_align, third_align;
    while (i != 0 || j != 0 || k != 0) {
        if (path[i][j][k] == 'r') {
            first_align += '-';
            second_align += second[j - 1];
            third_align += '-';
            j -= 1;
        } else if (path[i][j][k] == 'l') {
            first_align += '-';
            second_align += '-';
            third_align += third[k - 1];
            k -= 1;
        } else if (path[i][j][k] == 'f') {
            first_align += first[i - 1];
            second_align += '-';
            third_align += '-';
            i -= 1;
        } else if (path[i][j][k] == 'x') {
            first_align += first[i - 1];
            second_align += second[j - 1];
            third_align += '-';
            i -= 1;
            j -= 1;
        } else if (path[i][j][k] == 'y') {
            first_align += first[i - 1];
            second_align += '-';
            third_align += third[k - 1];
            i -= 1;
            k -= 1;
        } else if (path[i][j][k] == 'z') {
            first_align += '-';
            second_align += second[j - 1];
            third_align += third[k - 1];
            j -= 1;
            k -= 1;
        } else if (path[i][j][k] == 'd') {
            first_align += first[i - 1];
            second_align += second[j - 1];
            third_align += third[k - 1];
            i -= 1;
            j -= 1;
            k -= 1;
        }
    }

    std::reverse(first_align.begin(), first_align.end());
    std::reverse(second_align.begin(), second_align.end());
    std::reverse(third_align.begin(), third_align.end());
    std::cout << first_align << std::endl;
    std::cout << second_align << std::endl;
    std::cout << third_align << std::endl;
    return 0;
}