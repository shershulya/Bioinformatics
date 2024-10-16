//                                         # Problem 3: Find All Approximate Occurrences of a Pattern in a String

// Approximate Pattern Matching Problem
// Find all approximate occurrences of a pattern in a string.
// Given: Strings Pattern and Text along with an integer d.
// Return: All starting positions where Pattern appears as a substring of Text with at most d mismatches.


// ATTCTGGA
// CGCCCGAATCCAGAACGCATTCCCATATTTCGGGACCACTGGCCTCCACGGTACGGACGTCAATCAAATGCCTAGCGGCTTGTGGTTTCTCCTACGCTCC
// 3

// 6 7 26 27 78

#include <iostream>
#include <vector>
#include <algorithm>

int HammingDist(std::string str1, std::string str2) {
    int count = 0;
    for (int i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i]) {
            count++;
        }
    }
    return count;
}

void ApproximatePatternCount(std::string text, std::string pattern, int d) {
    int count = 0;
    int pat_len = pattern.length();
    std::vector<int> occ_pos;
    for (int i = 0; i < text.length() - pat_len; ++i) {
        std::string approx_pattern = text.substr(i, pat_len);
        if (HammingDist(pattern, approx_pattern) <= d) {
            occ_pos.push_back(i);
        }
    }
    for (int i = 0; i < occ_pos.size() - 1; ++i) {
        std::cout << occ_pos[i] << " ";
    }
    std::cout << occ_pos[occ_pos.size() - 1] << std::endl;
    return;
}

int main (void) {
    std::string pattern, text;
    int d;
    std::cin >> pattern >> text >> d;
    ApproximatePatternCount(text, pattern, d);
    return 0;
}