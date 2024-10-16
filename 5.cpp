//                                         # Problem 5: Find Frequent Words with Mismatches and Reverse Complements

// Frequent Words with Mismatches and Reverse Complements Problem
// Find the most frequent k-mers (with mismatches and reverse complements) in a DNA string.
// Given: A DNA string Text as well as integers k and d.
// Return: All k-mers Pattern maximizing the sum Countd(Text, Pattern) + Countd(Text, Pattern) over all possible k-mers.


// ACGTTGCATGTCGCATGATGCATGAGAGCT
// 4 1

// ATGT ACAT

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int HammingDist(std::string str1, std::string str2) {
    int count = 0;
    for (int i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i]) {
            count++;
        }
    }
    return count;
}

int ApproximatePatternCount(std::string text, std::string pattern, int d) {
    int count = 0;
    int pat_len = pattern.length();
    std::vector<int> occ_pos;
    for (int i = 0; i < text.length() - pat_len; ++i) {
        std::string approx_pattern = text.substr(i, pat_len);
        if (HammingDist(pattern, approx_pattern) <= d) {
            ++count;
            occ_pos.push_back(i);
        }
    }
    return count;
}

int SymbolToNumber(char x) {
    if (x == 'A') {
        return 0;
    }
    if (x == 'C') {
        return 1;
    }
    if (x == 'G') {
        return 2;
    }
    if (x == 'T') {
        return 3;
    }
    return -1;
}

int PatternToNumber(std::string pattern) {
    int pat_len = pattern.length();
    if (pat_len == 0) {
        return 0;
    }
    char symbol = pattern[pat_len - 1];
    std::string prefix = pattern.substr(0, pat_len - 1);
    return 4 * PatternToNumber(prefix) + SymbolToNumber(symbol);
}

std::string NumberToSymbol(int x) {
    if (x == 0) {
        return "A";
    }
    if (x == 1) {
        return "C";
    }
    if (x == 2) {
        return "G";
    }
    if (x == 3) {
        return "T";
    }
    return "X";
}

std::string NumberToPattern(int index, int k) {
    if (k == 1) {
        return NumberToSymbol(index);
    }
    int prefix_index = index / 4;
    int remainder = index % 4;
    std::string symbol = NumberToSymbol(remainder);
    std::string prefix_pattern = NumberToPattern(prefix_index, k - 1);
    return prefix_pattern + symbol;
}

std::vector<std::string> Neighbors(std::string pattern, int d) {
    std::vector<std::string> neighborhood;
    if (d == 0) {
        neighborhood.push_back(pattern);
        return neighborhood;
    }
    if (pattern.length() == 1) {
        neighborhood.push_back("A");
        neighborhood.push_back("C");
        neighborhood.push_back("G");
        neighborhood.push_back("T");
        return neighborhood;
    }
    std::vector<std::string> suffix_neighbors = Neighbors(pattern.substr(1, pattern.length() - 1), d);
    for (int i = 0; i < suffix_neighbors.size(); ++i) {
        if (HammingDist(pattern.substr(1, pattern.length() - 1), suffix_neighbors[i]) < d) {
            neighborhood.push_back("A" + suffix_neighbors[i]);
            neighborhood.push_back("C" + suffix_neighbors[i]);
            neighborhood.push_back("G" + suffix_neighbors[i]);
            neighborhood.push_back("T" + suffix_neighbors[i]);
        } else {
            neighborhood.push_back(pattern[0] + suffix_neighbors[i]);
        }
    }
    return neighborhood;
}

std::string complement(std::string pattern) {
    std::string comp_pattern = pattern;
    for (int i = 0; i < pattern.length(); ++i) {
        char x = pattern[i];
        if (x == 'A') {
            comp_pattern[i] = 'T';
        }
        if (x == 'C') {
            comp_pattern[i] = 'G';
        }
        if (x == 'G') {
            comp_pattern[i] = 'C';
        }
        if (x == 'T') {
            comp_pattern[i] = 'A';
        }
    }
    std::reverse(comp_pattern.begin(), comp_pattern.end());
    return comp_pattern;
}

void FrequentWordsWithMismatchesAndComplements(std::string text, int k, int d) {
    std::vector<std::string> frequent_patterns;
    int close[(int)pow(4, k) - 1] = {0};
    std::vector<int> frequency((int)pow(4, k) - 1, 0);

    for (int i = 0; i < text.length() - k; ++i) {
        std::vector<std::string> neighborhood = Neighbors(text.substr(i, k), d);
        for (int pat = 0; pat < neighborhood.size(); ++pat) {
            int index = PatternToNumber(neighborhood[pat]);
            close[index] = 1;
        }
    }

    for (int i = 0; i < pow(4, k) - 1; ++i) {
        if (close[i]) {
            std::string pattern = NumberToPattern(i, k);
            frequency[i] = ApproximatePatternCount(text, pattern, d) + ApproximatePatternCount(text, complement(pattern), d);
        }
    }
    int max_count = *std::max_element(std::begin(frequency), std::end(frequency));

    for (int i = 0; i < pow(4, k) - 1; ++i) {
        if (frequency[i] == max_count) {
            std::string pattern = NumberToPattern(i, k);
            frequent_patterns.push_back(pattern);
        }
    }

    for (int i = 0; i < frequent_patterns.size() - 1; ++i) {
        std::cout << frequent_patterns[i] << " ";
    }
    std::cout << frequent_patterns[frequent_patterns.size() - 1] << std::endl;

}

int main (void) {
    std::string text;
    int k, d;
    std::cin >> text >> k >> d;
    FrequentWordsWithMismatchesAndComplements(text, k, d);
    return 0;
}