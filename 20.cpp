//                                         # Problem 20: Implement ConvolutionCyclopeptideSequencing

// Implement ConvolutionCyclopeptideSequencing
// Given: An integer M, an integer N, and a collection of (possibly repeated) integers Spectrum.
// Return: A cyclic peptide LeaderPeptide with amino acids taken only from the top M elements (and ties) of the convolution of Spectrum
// that fall between 57 and 200, and where the size of Leaderboard is restricted to the top N (and ties).


// 20
// 60
// 57 57 71 99 129 137 170 186 194 208 228 265 285 299 307 323 356 364 394 422 493

// 99-71-137-57-72-57

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include <iomanip>

std::vector<int> Amino_Acid_Masses;

int mass(std::vector<int> peptid) {
    int ms = 0;
    for (int i = 0; i < peptid.size(); ++i) {
        ms += peptid[i];
    }
    return ms;
}

std::vector<int> linear_spectrum(std::vector<int> peptid) {
    std::vector<int> prefix{0};
    std::vector<int> lin_spect{0};
    for (int i = 0; i < peptid.size(); ++i) {
        prefix.push_back(prefix[i] + peptid[i]);
    }

    for (int i = 0; i < peptid.size(); ++i) {
        for (int j = i + 1; j < peptid.size() + 1; ++j) {
            lin_spect.push_back(prefix[j] - prefix[i]);
        }
    }
    std::sort(lin_spect.begin(), lin_spect.end());
    return lin_spect;
}

bool not_consistent(std::vector<int> peptid, std::vector<int> spectrum) {
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

std::vector<std::vector<int>> expand(std::vector<std::vector<int>> peptides, std::vector<int> base = Amino_Acid_Masses) {
    std::vector<std::vector<int>> new_peptides;
    for (int i = 0; i < peptides.size(); ++i) {
        for (int j = 0; j < base.size(); ++j) {
            std::vector<int> expand = peptides[i];
            expand.push_back(base[j]);
            new_peptides.push_back(expand);
        }
    }
    return new_peptides;
}

std::vector<int> cyclic_spectrum(std::vector<int> peptid) {
    std::vector<int> prefix{0};
    std::vector<int> cycl_spect{0};
    int len_peptid = peptid.size();
    for (int i = 0; i < len_peptid; ++i) {
        prefix.push_back(prefix[i] + peptid[i]);
    }
    int peptide_mass = prefix[len_peptid];

    for (int i = 0; i < peptid.size(); ++i) {
        for (int j = i + 1; j < peptid.size() + 1; ++j) {
            cycl_spect.push_back(prefix[j] - prefix[i]);
            if (i > 0 && j < len_peptid) {
                cycl_spect.push_back(peptide_mass - cycl_spect.back());
            }
        }
    }
    std::sort(cycl_spect.begin(), cycl_spect.end());
    return cycl_spect;
}

int score(std::vector<int> peptid, std::vector<int> spectrum) {
    std::vector<int> lin_spect = cyclic_spectrum(peptid);
    int scr = 0;
    for (int i = 0; i < lin_spect.size(); ++i) {
        auto it = std::find(spectrum.begin(), spectrum.end(), lin_spect[i]);
        if (it != spectrum.end()) {
            spectrum.erase(it);
            scr++;
        }
    }
    return scr;
}

std::vector<std::vector<int>> cut(std::vector<std::vector<int>> leaderboard, std::vector<int> spectrum, int n) {
    std::vector<std::vector<int>> new_leaderboard;
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

void leaderboard_cyclopeptide_sequencing(std::vector<int> spectrum, int n) {
    std::vector<std::vector<int>> leaderboard, base;
    std::vector<int> leader_peptide, empty;
    leaderboard.push_back(empty);
    int parent_mass = spectrum[spectrum.size() - 1];
    while (!leaderboard.empty()) {
        leaderboard = expand(leaderboard);
        for (int i = leaderboard.size() - 1; i >= 0; --i) {
            std::vector<int> peptid = leaderboard[i];
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
        std::cout << leader_peptide[i] << "-";
    }
    std::cout << leader_peptide[leader_peptide.size() - 1] << std::endl;
}

void spectral_convolution(std::vector<int> spectrum, int m) {
    spectrum.insert(spectrum.begin(), 0);

    std::vector<std::vector<int>> spec_conv;
    spec_conv.resize(spectrum.size());    
    for (int i = 0; i < spec_conv.size(); ++i) {
        spec_conv[i].resize(spectrum.size());
    }

    for (int i = 0; i < spec_conv.size(); ++i) {
        for (int j = 0; j < spec_conv[i].size(); ++j) {
            spec_conv[i][j] = spectrum[i] - spectrum[j];
        }
    }

    std::vector<int> conv_cnt(200, 0);
    for (int i = 0; i < spec_conv.size(); ++i) {
        for (int j = 0; j < spec_conv[i].size(); ++j) {
            if (spec_conv[i][j] >= 57 && spec_conv[i][j] <= 200) {
                conv_cnt[spec_conv[i][j]] += 1;
            }
        }
    }

    std::vector<std::pair<int, int>> acids_cnt;
    for (int i = 57; i < 201; ++i) {
        acids_cnt.push_back(std::make_pair(i, conv_cnt[i]));
    }

    std::sort(acids_cnt.begin(), acids_cnt.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    int threshold = acids_cnt[m - 1].second;

    Amino_Acid_Masses.clear();
    for (int i = 0; i < acids_cnt.size(); ++i) {
        if (acids_cnt[i].second >= threshold)
            Amino_Acid_Masses.push_back(acids_cnt[i].first);
    }

    std::sort(Amino_Acid_Masses.begin(), Amino_Acid_Masses.end());
}

void convolution_cyclopeptide_sequencing(std::vector<int> spectrum, int m, int n) {
    spectral_convolution(spectrum, m);
    leaderboard_cyclopeptide_sequencing(spectrum, n);
}

int main(void) {
    int m, n;
    std::cin >> m >> n;
    int spec_mass;
    std::vector<int> spectrum;
    while (std::cin >> spec_mass) {
        spectrum.push_back(spec_mass);
    }

    std::sort(spectrum.begin(), spectrum.end());

    convolution_cyclopeptide_sequencing(spectrum, m, n);

    return 0;
}