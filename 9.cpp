//                                         # Problem 9: Implement GibbsSampler

// Implement GibbsSampler
// Given: Integers k, t, and N, followed by a collection of strings Dna.
// Return: The strings BestMotifs resulting from running GibbsSampler(Dna, k, t, N) with 20 random starts. Remember to use pseudocounts!


// 8 5 100
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

int Profile (std::string *Motifs, int k, int t, std::string *dna, int len, int inx) {
    int prof[4][k] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < k; ++j)
            prof[i][j] = 1;
    }
    for (int i = 0; i < t; ++i) {
        if (i == inx) {
            continue;
        }
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
    
    std::vector<float> p;
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
        p.push_back(p_cur / static_cast<float>(2 * t - 1));
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d(p.begin(), p.end());
    Motifs[inx] = dna[inx].substr(d(gen), k);
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

int GibbsSampler(std::string *dna, int k, int t, int N, std::string *best) {
    int len = dna[0].length();
    std::string Motifs[t];
    std::random_device dev;
    std::mt19937 generator(dev());
    std::uniform_int_distribution<int> distribution(0, len - k);
    for (int i = 0; i < t; ++i) {
        Motifs[i] = std::string (dna[i], distribution(generator), k);
        best[i] = Motifs[i];
    }
    std::uniform_int_distribution<int> distr(0, t - 1);
    for (int i = 0; i < N; ++i) {
        int inx = distr(generator);
        Profile(Motifs, k, t, dna, len, inx);
        if (Score(Motifs, k, t) < Score(best, k, t)) {
            for (int j = 0; j < t; ++j) {
                best[j] = Motifs[j];
            }
        }
    }
    return 0;
}

int main (void) {
    int k, t, N;
    std::cin >> k >> t >> N;
    std::string s[t];
    for (int i = 0; i < t; ++i) {
        std::cin >> s[i];
    }
    std::string best[t], result[t];
    int max_score = INT_MAX;
    for (int i = 0; i < 20; ++i) {
        GibbsSampler(s, k, t, N, best);
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
