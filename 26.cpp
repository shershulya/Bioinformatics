//                                         # Problem 26: Implement GreedySorting to Sort a Permutation by Reversals

// Implement GreedySorting
// Given: A signed permutation P.
// Return: The sequence of permutations corresponding to applying GreedySorting to P, ending with the identity permutation.


// (-3 +4 +1 +5 -2)

// (-1 -4 +3 +5 -2)
// (+1 -4 +3 +5 -2)
// (+1 +2 -5 -3 +4)
// (+1 +2 +3 +5 +4)
// (+1 +2 +3 -4 -5)
// (+1 +2 +3 +4 -5)
// (+1 +2 +3 +4 +5)

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

void PrintPermutation(std::vector<std::string> permutation) {
    std::cout << '(';
    for (int i = 0; i < permutation.size() - 1; ++i) {
        std::cout << permutation[i] << " ";
    }
    std::cout << permutation[permutation.size() - 1] << ')' << std::endl;
}

void GreedySorting(std::string input) {
    std::vector<std::string> permutation;
    std::istringstream iss(input);
    std::string s;
    while (getline(iss, s, ' ')) {
        permutation.push_back(s);
    }

    int perm_len = permutation.size();
    for (int i = 0; i < perm_len; ++i)  {
        if (('+' + std::to_string(i + 1)) == permutation[i]) {
            continue;
        }
        for (int j = i; j < perm_len; ++j) {
            if (std::to_string(i + 1) == permutation[j].substr(1, permutation[j].size() - 1)) {
                std::reverse(permutation.begin() + i, permutation.begin() + j + 1);
                for (int k = i; k <= j; ++k) {
                    if (permutation[k][0] == '-') {
                        permutation[k][0] = '+';
                    } else {
                        permutation[k][0] = '-';
                    }
                }
                break;
            }
        }
        PrintPermutation(permutation);
        if (permutation[i][0] == '-') {
            permutation[i][0] = '+';
            PrintPermutation(permutation);
        }
    }
}

int main(void) {
    std::string permutation, s;
    std::getline(std::cin, permutation);
    permutation = permutation.substr(1, permutation.size() - 2);
    
    GreedySorting(permutation);
    
    return 0;
}