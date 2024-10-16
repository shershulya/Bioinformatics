//                                         # Problem 10: Implement DistanceBetweenPatternAndStrings

// Compute DistanceBetweenPatternAndStrings
// Find the distance between a pattern and a set of strings.
// Given: A DNA string Pattern and a collection of DNA strings Dna.
// Return: DistanceBetweenPatternAndStrings(Pattern, Dna).


// AAA
// TTACCTTAAC GATATCTGTC ACGGCGTTCG CCCTAAAGAG CGTCAGAGGT

// 5

#include <iostream>
#include <cstring>
#include <climits>
#include <vector>

int HammingDistance(std::string pattern, std::string k_mer) {
    int i = 0, dist = 0;
    while(pattern[i] != '\0') {
        if (pattern[i] != k_mer[i])
            dist++;
        i++;
    }
    return dist;
}


int DistanceBetweenPatternAndStrings(std::string pattern, std::vector<std::string> dna) {
    int k = pattern.length();
    int len = dna[0].length();
    int distance = 0;
    for (int i = 0; i < dna.size(); ++i) {
        int HammDist = INT_MAX;
        for (int j = 0; j <= len - k; ++j) {
            std::string k_mer(dna[i], j, k);
            int CurHammDist = HammingDistance(pattern, k_mer);
            if (HammDist > CurHammDist) {
                HammDist = CurHammDist;
            }
        }
        distance = distance + HammDist;
    }
    return distance;
}


int main (void) {
    std::string pattern, s;
    std::cin >> pattern;
    std::vector<std::string> dna;
    while (std::cin >> s) {
        dna.push_back(s);
    }
    std::cout << DistanceBetweenPatternAndStrings(pattern, dna) << std::endl;
    return 0;
}
