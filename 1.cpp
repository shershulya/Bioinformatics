//                                         # Problem 1: Find Patterns Forming Clumps in a String

// Clump Finding Problem
// Find patterns forming clumps in a string.
// Given: A string Genome, and integers k, L, and t.
// Return: All distinct k-mers forming (L, t)-clumps in Genome.


// CGGACTCGACAGATGTGAAGAAATGTGAAGACTGAGTGAAGAGAAGAGGAAACACGACACGACATTGCGACATAATGTACGAATGTAATGTGCCTATGGC
// 5 75 4

// CGACA GAAGA AATGT

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int PatternCount(std::string text, std::string pattern) {
    int count = 0;
    int pat_len = pattern.length();
    for (int i = 0; i < text.length() - pat_len; ++i) {
        if (text.substr(i, pat_len) == pattern) {
            count++;
        }
    }
    return count;
}

void PatternsFormingClumps(std::string text, int k, int L, int t) {
    std::vector<std::string> frequent_patterns;
    for (int i = 0; i < text.length() - k; ++i) {
        std::vector<int> count;
        std::string window = text.substr(i, L);
        for (int j = 0; j < window.length() - k; ++j) {
            std::string pattern = window.substr(j, k);
            count.push_back(PatternCount(window, pattern));
        }
        for (int j = 0; j < window.length() - k; ++j) {
            if (count[j] >= t) {
                frequent_patterns.push_back(window.substr(j, k));
            }
        }
    }    

    std::sort(frequent_patterns.begin(), frequent_patterns.end());
    auto last = std::unique(frequent_patterns.begin(), frequent_patterns.end());
    frequent_patterns.erase(last, frequent_patterns.end());

    for (int i = 0; i < frequent_patterns.size(); ++i) {
        std::cout << frequent_patterns[i] << std::endl;
    }
    return;
}

int main (void) {
    std::string text;
    std::cin >> text;
    int k, L, t;
    std::cin >> k >> L >> t;
    
    PatternsFormingClumps(text, k, L, t);
    return 0;
}
