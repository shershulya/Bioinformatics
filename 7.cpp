//                                         # Problem 7: Implement GreedyMotifSearch with Pseudocounts

// Implement GreedyMotifSearch with Pseudocounts
// Given: Integers k and t, followed by a collection of strings Dna.
// Return: A collection of strings BestMotifs resulting from running GreedyMotifSearch(Dna, k, t) with pseudocounts.
// If at any step you find more than one Profile-most probable k-mer in a given string, use the one occurring first.


// 3 5
// GGCGTTCAGGCA
// AAGAATCAGTCA
// CAAGGAGTTCGC
// CACGTCAATCAC
// CAATAATATTCG

// TTC
// ATC
// TTC
// ATC
// TTC

#include <iostream>
#include <cstring>

std::string Profile (std::string *Motifs, int inx, int k, std::string *dna, int len) {
    int prof[4][k] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < k; ++j)
            prof[i][j] = 1;
    }
    for (int i = 0; i < inx; ++i) {
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
    
    long long p_max = 0;
    std::string result_k_mer(dna[inx], 0, k);
    for (int i = 0; i <= len - k; ++i) {
        std::string k_mer(dna[inx], i, k);
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
    
    return result_k_mer;
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

int GreedyMotifSearch(std::string *dna, int k, int t) {
    std::string best[t];
    for (int i = 0; i < t; ++i) {
        best[i] = std::string (dna[i], 0, k);
    }
    
    int len = dna[0].length();
    for (int i = 0; i <= len - k; ++i) {
        std::string motif_cur(dna[0], i, k);
        std::string Motifs[t];
        Motifs[0] = motif_cur;
        for (int j = 1; j < t; ++j) {
            Motifs[j] = Profile(Motifs, j, k, dna, len);
        }
        if (Score(Motifs, k, t) < Score(best, k, t)) {
            for (int j = 0; j < t; ++j) {
                best[j] = Motifs[j];
            }
        }
    }
    
    for (int i = 0; i < t; ++i) {
        std::cout << best[i] << std::endl;
    }
    return 0;
}

int main (void) {
    int k, t;
    std::cin >> k >> t;
    std::string s[t];
    for (int i = 0; i < t; ++i) {
        std::cin >> s[i];
    }
    GreedyMotifSearch(s, k, t);
    return 0;
}
