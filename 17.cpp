//                                         # Problem 17: Compute the Number of Peptides of Given Total Mass

// Counting Peptides with Given Mass Problem
// Compute the number of peptides of given total mass.
// Given: An integer m.
// Return: The number of linear peptides having integer mass m.


// 1024

// 14712706211

#include <iostream>
#include <vector>
#include <map>

int main(void) {
    int mass;
    std::cin >> mass;
    std::vector<int> Amino_Acid_Masses = {57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186};
    std::map<int, long long int> dict;
    dict[0] = 1LL;
    for (int cur_mass = 57; cur_mass <= mass; cur_mass++) {
        for (int amino_acid_mass = 0; amino_acid_mass < Amino_Acid_Masses.size(); amino_acid_mass++) {
            if(dict.count(cur_mass - Amino_Acid_Masses[amino_acid_mass]))
                dict[cur_mass] = dict[cur_mass - Amino_Acid_Masses[amino_acid_mass]] + (dict.count(cur_mass) ? dict[cur_mass] : 0);
        }
    }
    std::cout << dict[mass] << std::endl;
    return 0;
}