//                                         # Problem 19: Implement LeaderboardCyclopeptideSequencing

// Implement LeaderboardCyclopeptideSequencing
// Given: An integer N and a collection of integers Spectrum.
// Return: LeaderPeptide after running LeaderboardCyclopeptideSequencing(Spectrum, N).


// 10
// 0 71 113 129 147 200 218 260 313 331 347 389 460

// 113-147-71-129

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::vector<std::string> Amino_Acid = { 
    "A",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "K",
    "L",
    "M",
    "N",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "V",
    "W",
    "Y"
};
std::map<char, int> Amino_Acid_Masses = {
    {'G',  57},
    {'A',  71},
    {'S',  87},
    {'P',  97},
    {'V',  99},
    {'T', 101},
    {'C', 103},
    {'I', 113},
    {'L', 113},
    {'N', 114},
    {'D', 115},
    {'K', 128},
    {'Q', 128},
    {'E', 129},
    {'M', 131},
    {'H', 137},
    {'F', 147},
    {'R', 156},
    {'Y', 163},
    {'W', 186}
};

int mass(std::string peptid) {
    int ms = 0;
    for (int i = 0; i < peptid.size(); ++i) {
        ms += Amino_Acid_Masses[peptid[i]];
    }
    return ms;
}

std::vector<int> linear_spectrum(std::string peptid) {
    std::vector<int> prefix{0};
    std::vector<int> lin_spect{0};
    for (int i = 0; i < peptid.length(); ++i) {
        prefix.push_back(prefix[i] + Amino_Acid_Masses[peptid[i]]);
    }

    for (int i = 0; i < peptid.length(); ++i) {
        for (int j = i + 1; j < peptid.length() + 1; ++j) {
            lin_spect.push_back(prefix[j] - prefix[i]);
        }
    }
    std::sort(lin_spect.begin(), lin_spect.end());
    return lin_spect;
}

bool not_consistent(std::string peptid, std::vector<int> spectrum) {
    std::vector<int> pep_spectr = linear_spectrum(peptid);
    for (int i = 0; i < pep_spectr.size(); ++i) {
        std::vector<int>::iterator it;
        it = std::find(spectrum.begin(), spectrum.end(), pep_spectr[i]);
        if (it == spectrum.end())
            return true;
        spectrum.erase(it);
    }
    return false;
}

std::vector<std::string> expand(std::vector<std::string> peptides, std::vector<std::string> base = Amino_Acid) {
    std::vector<std::string> new_peptides;
    for (int i = 0; i < peptides.size(); ++i) {
        for (int j = 0; j < base.size(); ++j) {
            new_peptides.push_back(peptides[i] + base[j]);
        }
    }
    return new_peptides;
}

std::vector<int> cyclic_spectrum(std::string peptid) {
    std::vector<int> prefix{0};
    std::vector<int> cycl_spect{0};
    int len_peptid = peptid.length();
    for (int i = 0; i < len_peptid; ++i) {
        prefix.push_back(prefix[i] + Amino_Acid_Masses[peptid[i]]);
    }
    int peptide_mass = prefix[len_peptid];

    for (int i = 0; i < peptid.length(); ++i) {
        for (int j = i + 1; j < peptid.length() + 1; ++j) {
            cycl_spect.push_back(prefix[j] - prefix[i]);
            if (i > 0 && j < len_peptid) {
                cycl_spect.push_back(peptide_mass - cycl_spect.back());
            }
        }
    }
    std::sort(cycl_spect.begin(), cycl_spect.end());
    return cycl_spect;
}

int score(std::string peptid, std::vector<int> spectrum) {
    std::vector<int> cycl_spect = linear_spectrum(peptid);
    int scr = 0;
    for (int i = 0; i < cycl_spect.size(); ++i) {
        auto it = std::find(spectrum.begin(), spectrum.end(), cycl_spect[i]);
        if (it != spectrum.end()) {
            scr++;
        }
    }
    return scr;
}

std::vector<std::string> cut(std::vector<std::string> leaderboard, std::vector<int> spectrum, int n) {
    std::vector<std::string> new_leaderboard;
    std::vector<int> scores, sort_scores;

    for (int i = 0; i < leaderboard.size(); ++i) {
        scores.push_back(score(leaderboard[i], spectrum));
    }
    sort_scores = scores;
    std::sort(sort_scores.begin(), sort_scores.end(), std::greater<int>());

    int threshold = sort_scores[n - 1];

    for (int i = 0; i < leaderboard.size(); ++i) {
        if (scores[i] >= threshold) {
            new_leaderboard.push_back(leaderboard[i]);
        }
    }

    return new_leaderboard;
}

int main(void) {
    int n;
    std::cin >> n;
    int spec_mass;
    std::vector<int> spectrum;
    while (std::cin >> spec_mass) {
        spectrum.push_back(spec_mass);
    }

    std::vector<std::string> leaderboard, base;
    std::string s, leader_peptide;
    s.clear();
    leader_peptide.clear();
    leaderboard.push_back(s);

    int parent_mass = spectrum[spectrum.size() - 1];
    while (!leaderboard.empty()) {
        leaderboard = expand(leaderboard);
        for (int i = leaderboard.size() - 1; i >= 0; --i) {
            std::string peptid = leaderboard[i];
            if (mass(peptid) == parent_mass) {
                if (score(peptid, spectrum) > score(leader_peptide, spectrum)) {
                    leader_peptide = peptid;
                }
            } else if (mass(peptid) > parent_mass) {
                leaderboard.erase(leaderboard.begin() + i);
            }
        }

        if (leaderboard.size() > 0 && n < leaderboard.size()) {
            leaderboard = cut(leaderboard, spectrum, n);
        }
    }

    for (int i = 0; i < leader_peptide.size() - 1; ++i) {
        std::cout << Amino_Acid_Masses[leader_peptide[i]] << "-";
    }
    std::cout << Amino_Acid_Masses[leader_peptide[leader_peptide.size() - 1]] << std::endl;

    return 0;
}