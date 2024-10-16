//                                         # Problem 2: Find a Position in a Genome Minimizing the Skew

// Minimum Skew Problem
// Find a position in a genome minimizing the skew.
// Given: A DNA string Genome.
// Return: All integer(s) i minimizing Skew(Prefixi (Text)) over all values of i (from 0 to |Genome|).


// CCTATCGGTGGATTAGCATGTCCCTGTACGTTTCGCCGCGAACTAGTTCACACGGCTTGATGGCAAATGGTTTTTCCGGCGACCGTAATCGTCCACCGAG

// 53 97

#include <iostream>
#include <vector>
#include <algorithm>

void MinimumSkew(std::string genom) {
    std::vector<int> skew, min_pos;
    int count = 0;
    skew.push_back(count);
    for (int i = 0; i < genom.length(); ++i) {
        if (genom[i] == 'G') {
            ++count;
        }
        if (genom[i] == 'C') {
            --count;
        }
        skew.push_back(count);
    }

    int min_count = *std::min_element(std::begin(skew), std::end(skew));
    std::cout << min_count << std::endl;
    for (int i = 0; i < skew.size(); ++i) {
        if (skew[i] == min_count) {
            min_pos.push_back(i);
        }
    }
    
    for (int i = 0; i < min_pos.size() - 1; ++i) {
        std::cout << min_pos[i] << " ";
    }
    std::cout << min_pos[min_pos.size() - 1] << std::endl;
    return;
}

int main (void) {
    std::string genom;
    std::cin >> genom;
    MinimumSkew(genom);
    return 0;
}