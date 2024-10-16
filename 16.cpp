//                                         # Problem 16: Find Substrings of a Genome Encoding a Given Amino Acid String

// Peptide Encoding Problem
// Find substrings of a genome encoding a given amino acid sequence.
// Given: A DNA string Text and an amino acid string Peptide.
// Return: All substrings of Text encoding Peptide (if any such substrings exist).


// ATGGCCATGGCCCCCAGAACTGAGATCAATAGTACCCGTATTAACGGGTGA
// MA

// ATGGCC
// GGCCAT
// ATGGCC

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

#include <termios.h> 
#include <unistd.h>

void complementary(std::string& chain) {
    for (int i = 0; i < chain.size(); ++i) {
        if (chain[i] == 'A') {
            chain[i] = 'U';
        } else if (chain[i] == 'U') {
            chain[i] = 'A';
        } else if (chain[i] == 'G') {
            chain[i] = 'C';
        } else if (chain[i] == 'C') {
            chain[i] = 'G';
        } else {
            std::cout << "Input ERROR" << std::endl;
        }
    }
}

void transcribe_dir(std::string& chain) {
    for (int i = 0; i < chain.size(); ++i) {
        if (chain[i] == 'T') {
            chain[i] = 'U';
        }
    }
}

void transcribe_rev(std::string& chain) {
    for (int i = 0; i < chain.size(); ++i) {
        if (chain[i] == 'U') {
            chain[i] = 'T';
        }
    }
}

void dictionary(std::map<std::string, char>& dict) {
    dict["AAA"] = 'K';
    dict["AAC"] = 'N';
    dict["AAG"] = 'K';
    dict["AAU"] = 'N';
    dict["ACA"] = 'T';
    dict["ACC"] = 'T';
    dict["ACG"] = 'T';
    dict["ACU"] = 'T';
    dict["AGA"] = 'R';
    dict["AGC"] = 'S';
    dict["AGG"] = 'R';
    dict["AGU"] = 'S';
    dict["AUA"] = 'I';
    dict["AUC"] = 'I';
    dict["AUG"] = 'M';
    dict["AUU"] = 'I';
    dict["CAA"] = 'Q';
    dict["CAC"] = 'H';
    dict["CAG"] = 'Q';
    dict["CAU"] = 'H';
    dict["CCA"] = 'P';
    dict["CCC"] = 'P';
    dict["CCG"] = 'P';
    dict["CCU"] = 'P';
    dict["CGA"] = 'R';
    dict["CGC"] = 'R';
    dict["CGG"] = 'R';
    dict["CGU"] = 'R';
    dict["CUA"] = 'L';
    dict["CUC"] = 'L';
    dict["CUG"] = 'L';
    dict["CUU"] = 'L';
    dict["GAA"] = 'E';
    dict["GAC"] = 'D';
    dict["GAG"] = 'E';
    dict["GAU"] = 'D';
    dict["GCA"] = 'A';
    dict["GCC"] = 'A';
    dict["GCG"] = 'A';
    dict["GCU"] = 'A';
    dict["GGA"] = 'G';
    dict["GGC"] = 'G';
    dict["GGG"] = 'G';
    dict["GGU"] = 'G';
    dict["GUA"] = 'V';
    dict["GUC"] = 'V';
    dict["GUG"] = 'V';
    dict["GUU"] = 'V';
    dict["UAA"] = '*';
    dict["UAC"] = 'Y';
    dict["UAG"] = '*';
    dict["UAU"] = 'Y';
    dict["UCA"] = 'S';
    dict["UCC"] = 'S';
    dict["UCG"] = 'S';
    dict["UCU"] = 'S';
    dict["UGA"] = '*';
    dict["UGC"] = 'C';
    dict["UGG"] = 'W';
    dict["UGU"] = 'C';
    dict["UUA"] = 'L';
    dict["UUC"] = 'F';
    dict["UUG"] = 'L';
    dict["UUU"] = 'F';
}

int clear_icanon(void)
{
  struct termios settings;
  int result;
  result = tcgetattr (STDIN_FILENO, &settings);
  if (result < 0)
    {
      perror ("error in tcgetattr");
      return 0;
    }

  settings.c_lflag &= ~ICANON;

  result = tcsetattr (STDIN_FILENO, TCSANOW, &settings);
  if (result < 0)
    {
      perror ("error in tcsetattr");
      return 0;
   }
  return 1;
}


int main(void) {
    clear_icanon();

    std::map<std::string, char> pep_dict;
    dictionary(pep_dict);

    std::string dna;
    std::string peptid;
    std::cin >> dna;
    std::cin >> peptid;

    int n = peptid.size();
    std::vector<std::string> string_peptid_old;
    std::vector<int> cnt;


    std::map <std::string, char>::iterator it;

    int tmp_cnt_0 = 0;
    for (it = pep_dict.begin(); it != pep_dict.end(); ++it) {
        if (peptid[0] == it->second) {
            string_peptid_old.push_back(it->first);
            tmp_cnt_0++;
        }
    }
    cnt.push_back(tmp_cnt_0);
    
    for (int i = 1; i < n; ++i) {
        int tmp_cnt = 0;
        std::vector<std::string> string_peptid_new;
        for (it = pep_dict.begin(); it != pep_dict.end(); ++it) {
            if (peptid[i] == it->second) {
                tmp_cnt++;
                for (int j = 0; j < string_peptid_old.size(); ++j) {
                    string_peptid_new.push_back(string_peptid_old[j] + it->first);
                }
            }
        }
        string_peptid_old.clear();
        string_peptid_old = string_peptid_new;
        cnt.push_back(tmp_cnt);
    }

    std::vector<std::string> peptid_options_dir = string_peptid_old;
    std::vector<std::string> peptid_options_rev = peptid_options_dir;
    for (int i = 0; i < peptid_options_rev.size(); ++i) {
        complementary(peptid_options_rev[i]);
        std::reverse(peptid_options_rev[i].begin(), peptid_options_rev[i].end());
    }

    for (int i = 0; i < peptid_options_dir.size(); ++i) {
        transcribe_rev(peptid_options_dir[i]);
        transcribe_rev(peptid_options_rev[i]);
    }

    std::cout << std::endl;
    for (int i = 0; i < peptid_options_dir.size(); ++i) {
        std::size_t found = dna.find(peptid_options_dir[i]);
        if (found!=std::string::npos)
            std::cout << peptid_options_dir[i] << std::endl;
    }
    for (int i = 0; i < peptid_options_rev.size(); ++i) {
        std::size_t found = dna.find(peptid_options_rev[i]);
        if (found!=std::string::npos)
            std::cout << peptid_options_rev[i] << std::endl;
    }
    return 0;
}