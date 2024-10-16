//                                         # Problem 8: Implement RandomizedMotifSearch

// Implement RandomizedMotifSearch
// Given: Positive integers k and t, followed by a collection of strings Dna.
// Return: A collection BestMotifs resulting from running RandomizedMotifSearch(Dna, k, t) 1000 times. Remember to use pseudocounts!


// 8 5
// CGCCCCTCTCGGGGGTGTTCAGTAAACGGCCA
// GGGCGAGGTATGTGTAAGTGCCAAGGTGCCAG
// TAGTACCGAGACCGAAAGAAGTATACAGGCGT
// TAGATCAAGTTTCAGGTGCACGTCGGTGAACC
// AATCCACCAGCTCCACGTGCAATGTTGGCCTA

// TCTCGGGG
// CCAAGGTG
// TACAGGCG
// TTCAGGTG
// TCCACGTG

#include <iostream>
#include <cstring>
#include <climits>
#include <random>

int Profile (std::string *Motifs, int k, int t, std::string *dna, int len) {
    int prof[4][k] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < k; ++j)
            prof[i][j] = 1;
    }
    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < k; ++j) {
            if (Motifs[i][j] == 'A')
                prof[0][j] += 1;
            if (Motifs[i][j] == 'C')
                prof[1][j] += 1;
            if (Motifs[i][j] == 'G')
                prof[2][j] += 1;
            if (Motifs[i][j] == 'T')
                prof[3][j] += 1;
        }
    }
    
    std::string NewMotifs[t];
    for (int m = 0; m < t; ++m) {
        long long p_max = 0;
        std::string result_k_mer(dna[m], 0, k);
        for (int i = 0; i <= len - k; ++i) {
            std::string k_mer(dna[m], i, k);
            long long p_cur = 1;
            for (int j = 0; j < k; ++j) {
                if (k_mer[j] == 'A')
                    p_cur *= prof[0][j];
                if (k_mer[j] == 'C')
                    p_cur *= prof[1][j];
                if (k_mer[j] == 'G')
                    p_cur *= prof[2][j];
                if (k_mer[j] == 'T')
                    p_cur *= prof[3][j];
            }
            if (p_cur > p_max) {
                p_max = p_cur;
                result_k_mer = k_mer;
            }
        }
        NewMotifs[m] = result_k_mer;
    }
    for (int i = 0; i < t; ++i) {
        Motifs[i] = NewMotifs[i];
    }
    return 0;
}

int Score(std::string *Motifs, int k, int t) {
    int score = 0;
    for (int j = 0; j < k; ++j) {
        int count[4] = {0};
        for (int i = 0; i < t; ++i) {
            if (Motifs[i][j] == 'A')
                count[0] += 1;
            if (Motifs[i][j] == 'C')
                count[1] += 1;
            if (Motifs[i][j] == 'G')
                count[2] += 1;
            if (Motifs[i][j] == 'T')
                count[3] += 1;
        }
        int count_max_idx = 0;
        for (int i = 0; i < 4; ++i) {
            score += count[i];
            if (count[i] > count[count_max_idx])
                count_max_idx = i;
        }
        score -= count[count_max_idx];
    }
    return score;
}

std::string* RandomizedMotifSearch(std::string *dna, int k, int t, std::string *best) {
    int len = dna[0].length();
    std::string Motifs[t];
    std::random_device dev;
    std::mt19937 generator(dev());
    std::uniform_int_distribution<int> distribution(0, len - k);
    for (int i = 0; i < t; ++i) {
        Motifs[i] = std::string (dna[i], distribution(generator), k);
        best[i] = Motifs[i];
    }
    while (true) {
        Profile(Motifs, k, t, dna, len);
        if (Score(Motifs, k, t) < Score(best, k, t)) {
            for (int j = 0; j < t; ++j) {
                best[j] = Motifs[j];
            }
        } else {
            return 0;
        }
    }
}

int main (void) {
    int k, t;
    std::cin >> k >> t;
    std::string s[t];
    for (int i = 0; i < t; ++i) {
        std::cin >> s[i];
    }
    std::string best[t], result[t];
    int max_score = INT_MAX;
    for (int i = 0; i < 1000; ++i) {
        RandomizedMotifSearch(s, k, t, best);
        int cur_score = Score(best, k, t);
        if (cur_score < max_score) {
            max_score = cur_score;
            for (int j = 0; j < t; ++j) {
                result[j] = best[j];
            }
        }
    }
    for (int i = 0; i < t; ++i) {
        std::cout << result[i] << std::endl;
    }
    return 0;
}
