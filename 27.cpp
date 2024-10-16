//                                         # Problem 27: Compute the Number of Breakpoints in a Permutation

// Number of Breakpoints Problem
// Find the number of breakpoints in a permutation.
// Given: A signed permutation P.
// Return: The number of breakpoints in P.


// (+3 +4 +5 -12 -8 -7 -6 +1 +2 +10 +9 -11 +13 +14)

// 8

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

void PrintPermutation(std::vector<int> permutation, std::vector<char> permutation_signs) {
    std::cout << '(';
    int n = permutation.size() - 1;
    for (int i = 0; i < n; ++i) {
        std::cout << permutation_signs[i] << permutation[i] << " ";
    }
    std::cout << permutation_signs[n] << permutation[n] << ')' << std::endl;
}

void NumberOfBreakpoints(std::string input) {
    std::vector<int> permutation;
    std::vector<char> permutation_signs;
    permutation_signs.push_back('+');
    permutation.push_back(0);
    std::istringstream iss(input);
    std::string s;
    while (getline(iss, s, ' ')) {
        permutation_signs.push_back(s[0]);
        permutation.push_back(std::stoi(s.substr(1, s.size() - 1)));
    }
    int perm_len = permutation.size();
    permutation_signs.push_back('+');
    permutation.push_back(perm_len);

    int number_of_breakpoints = 0;
    char prev_sign = '+';
    int prev_x = 0;
    for (int i = 1; i < perm_len; ++i)  {
        char curr_sign = permutation_signs[i];
        int curr_x = permutation[i];
        if (prev_sign == '+' && curr_sign == prev_sign && curr_x == prev_x + 1 ||
            prev_sign == '-' && curr_sign == prev_sign && curr_x == prev_x - 1) {
            // nothing to do
        } else {
            number_of_breakpoints++;
        }
        prev_sign = curr_sign;
        prev_x = curr_x;
    }

    PrintPermutation(permutation, permutation_signs);

    std::cout << number_of_breakpoints << std::endl;
}

int main(void) {
    std::string permutation, s;
    std::getline(std::cin, permutation);
    permutation = permutation.substr(1, permutation.size() - 2);
    
    NumberOfBreakpoints(permutation);
    
    return 0;
}