//                                         # Problem 18: Find a Cyclic Peptide with Theoretical Spectrum Matching an Ideal Spectrum

// Cyclopeptide Sequencing Problem
// Given an ideal experimental spectrum, find a cyclic peptide whose theoretical spectrum matches the experimental spectrum.
// Given: A collection of (possibly repeated) integers Spectrum corresponding to an ideal experimental spectrum.
// Return: Every amino acid string Peptide such that Cyclospectrum(Peptide) = Spectrum (if such a string exists).


// 0 113 128 186 241 299 314 427

// 186-128-113 186-113-128 128-186-113 128-113-186 113-186-128 113-128-186

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::vector<std::string> Amino_Acid = { 
    "G",
    "A",
    "S",
    "P",
    "V",
    "T",
    "C",
    "I",
    "L",
    "N",
    "D",
    "K",
    "Q",
    "E",
    "M",
    "H",
    "F",
    "R",
    "Y",
    "W"
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

bool is_cyclic_spectrum(std::string peptid, std::vector<int> spectrum) {
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

    for (int i = 0; i < cycl_spect.size(); ++i) {
        if (cycl_spect[i] != spectrum[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int spec_mass;
    std::vector<int> spectrum;
    while (std::cin >> spec_mass) {
        spectrum.push_back(spec_mass);
    }

    std::vector<std::string> peptides, base;
    std::string s;
    s.clear();
    peptides.push_back(s);

    std::vector<std::string> start_peptides = expand(peptides);
    for (int i = 0; i < start_peptides.size(); ++i) {
        if (!not_consistent(start_peptides[i], spectrum)) {
            base.push_back(start_peptides[i]);
        }
    }
    int parent_mass = spectrum[spectrum.size() - 1];
    std::vector<std::vector<int>> result;
    while (!peptides.empty()) {
        peptides = expand(peptides, base);
        for (int i = peptides.size() - 1; i >= 0; --i) {
            std::string peptid = peptides[i];
            if (mass(peptid) == parent_mass) {
                if (is_cyclic_spectrum(peptid, spectrum)) {
                    std::vector<int> spectr_peptid;
                    for (int j = 0; j < peptid.size(); ++j) {
                        spectr_peptid.push_back(Amino_Acid_Masses[peptid[j]]);
                    }
                    result.push_back(spectr_peptid);
                }
                peptides.erase(peptides.begin() + i);
            } else if (not_consistent(peptid, spectrum)) {
                peptides.erase(peptides.begin() + i);
            }
        }
    }

    std::vector<std::vector<int>> unique_result;
    for (int i = 0; i < result.size(); ++i) {
        auto it = std::find(unique_result.begin(), unique_result.end(), result[i]);
        if (it == unique_result.end()) {
            unique_result.push_back(result[i]);
        }
    }

    for (int i = 0 ; i < unique_result.size(); ++i) {
        for (int j = 0; j < unique_result[i].size() - 1; ++j) {
            std::cout << unique_result[i][j] << "-";
        }
        std::cout << unique_result[i][unique_result[i].size() - 1] << " ";
    }
    std::cout << std::endl;
    return 0;
}