//                                         # Problem 14: Generate Contigs from a Collection of Reads

// Contig Generation Problem
// Generate the contigs from a collection of reads (with imperfect coverage).
// Given: A collection of k-mers Patterns.
// Return: All contigs in DeBruijn(Patterns). (You may return the strings in any order.)


// ATG
// ATG
// TGT
// TGG
// CAT
// GGA
// GAT
// AGA

// AGA ATG ATG CAT GAT TGGA TGT

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

int main() {
    std::string s;
    int k;
    std::cin >> s;
    k = s.length();
    std::vector<std::string> k_mers;
    std::vector<std::pair<std::string, std::string>> raw_vertexes;
    do {
        std::string prefix (s, 0, k - 1);
        std::string suffix (s, 1, k - 1);
        k_mers.push_back(s);
        raw_vertexes.push_back(std::make_pair(prefix, suffix));
    } while (std::cin >> s);



    std::vector<std::vector<int>> g(3 * raw_vertexes.size(), std::vector<int>(3 * raw_vertexes.size(), 0));
    std::vector<std::string> vertexes;

    //Constructing De Bruijn Graph
    for (int i = 0; i < raw_vertexes.size(); ++i) {
        auto iter1 = std::find(vertexes.begin(), vertexes.end(), raw_vertexes[i].first);
        if (iter1 != vertexes.end()) {
            int inx1 = iter1 - vertexes.begin();
            auto iter2 = std::find(vertexes.begin(), vertexes.end(), raw_vertexes[i].second);
            if (iter2 != vertexes.end()) {
                g[inx1][iter2 - vertexes.begin()] += 1;
            } else {
                vertexes.push_back(raw_vertexes[i].second);
                g[inx1][vertexes.size() - 1] += 1;
            }
        } else {
            vertexes.push_back(raw_vertexes[i].first);
            auto iter2 = std::find(vertexes.begin(), vertexes.end(), raw_vertexes[i].second);
            if (iter2 != vertexes.end()) {
                g[vertexes.size() - 1][iter2 - vertexes.begin()] += 1;
            } else {
                vertexes.push_back(raw_vertexes[i].second);
                g[vertexes.size() - 2][vertexes.size() - 1] += 1;
            }
        }
        
    }

    int n = vertexes.size();

    g.resize(n);
    for (int i = 0; i < g.size(); ++i) {
        g[i].resize(n);
    }

    std::vector<int> deg_in(n);
    std::vector<int> deg_out(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            deg_in[i] += g[j][i];
            deg_out[i] += g[i][j];
        }
    }

    std::vector<std::string> contigs;
    for (int i = 0; i < n; ++i) {
        if (!(deg_in[i] == 1 && deg_out[i] == 1)) {
            if (deg_out[i] > 0) {
                for (int j = 0; j < n; ++j) {
                    // if (g[i][j]) {
                    while (g[i][j]) {
                        g[i][j]--;
                        std::string contig = vertexes[i] + vertexes[j][k - 2];
                        int w = j;
                        while (deg_in[w] == 1 && deg_out[w] == 1) {
                            int u = 0;
                            while (g[w][u] == 0)
                                ++u;
                            --g[w][u];
                            contig += vertexes[u][k - 2];
                            w = u;
                        }
                        contigs.push_back(contig);
                    }
                    // }
                }
            }
        }
    }

    // for (each isolated cycle in graph) {
    //  contigs.push_back(cycle);
    // }

    // for (int i = 0; i < n; ++i) {
    //     if (deg_in[i] == 1 && deg_out[i] == 1) {
    //         for (int j = 0; j < n; ++j) {
    //             while (g[i][j]) {
    //                 g[i][j]--;
    //                 std::string cycle = vertexes[i] + vertexes[j][k - 2];
    //                 int w = j;
    //                 while (deg_in[w] == 1 && deg_out[w] == 1) {
    //                     int u = 0;
    //                     for (u; u < n; ++u)
    //                         if (g[w][u])
    //                             break;
    //                     --g[w][u];
    //                     cycle += vertexes[u][k - 2];
    //                     w = u;
    //                 }
    //                 contigs.push_back(cycle);
    //             }
    //         }
    //     }
    // }


    // for (int i = 0; i < n; ++i) {
    //     if (i == 0)
    //         std::cout << std::setw(8) << vertexes[i];
    //     else
    //         std::cout << std::setw(4) << vertexes[i];
    // }
    // std::cout << std::endl;
    // for (int i = 0; i < n; ++i) {
    //     std::cout << std::setw(4) << vertexes[i];
    //     for (int j = 0; j < n; ++j) {
    //         std::cout << std::setw(4) << g[i][j];
    //     }
    //     std::cout << std::endl;
    // }


    std::sort(contigs.begin(), contigs.end());
    for (int i = 0; i < contigs.size(); ++i) {
        std::cout << contigs[i] << std::endl;
    }
    return 0;
}