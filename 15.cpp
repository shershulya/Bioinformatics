//                                         # Problem 15: Construct a String Spelled by a Gapped Genome Path

// Gapped Genome Path String Problem
// Reconstruct a string from a sequence of (k,d)-mers corresponding to a path in a paired de Bruijn graph.
// Given: A sequence of (k, d)-mers (a_1|b_1), ... , (a_n|b_n) such that Suffix(a_i|b_i) = Prefix(a_i+1|b_i+1) for all i from 1 to n-1.
// Return: A string Text where the i-th k-mer in Text is equal to Suffix(a_i|b_i) for all i from 1 to n, if such a string exists.


// 4 2
// GACC|GCGC
// ACCG|CGCC
// CCGA|GCCG
// CGAG|CCGG
// GAGC|CGGA

// GACCGAGCGCCGGA

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

int main() {
	int k, d;
    std::cin >> k >> d;
    std::vector<std::pair< std::pair<std::string, std::string>, std::pair<std::string, std::string> >> raw_vertexes;
    std::string s;
    while (std::cin >> s) {
    	std::string prefix1 (s, 0, k - 1);
    	std::string suffix1 (s, 1, k - 1);

    	std::string prefix2 (s, k + 1, k - 1);
    	std::string suffix2 (s, k + 2, k - 1);

    	raw_vertexes.push_back(std::make_pair(std::make_pair(prefix1, prefix2), std::make_pair(suffix1, suffix2)));
    }

    std::vector<std::vector<int>> g(4 * raw_vertexes.size(), std::vector<int>(4 * raw_vertexes.size(), 0));
    std::vector<std::pair<std::string, std::string>> vertexes;

    // Constructing De Bruijn Graph
    for (int i = 0; i < raw_vertexes.size(); ++i) {
		auto iter1 = std::find(vertexes.begin(), vertexes.end(), raw_vertexes[i].first);
    	if (iter1 != vertexes.end()) {
		    int inx1 = iter1 - vertexes.begin();
    		auto iter2 = std::find(vertexes.begin(), vertexes.end(), raw_vertexes[i].second);
			if (iter2 != vertexes.end()) {
				g[inx1][iter2 - vertexes.begin()] += 1;
			} else {
				vertexes.push_back(std::make_pair(raw_vertexes[i].second.first, raw_vertexes[i].second.second));
				g[inx1][vertexes.size() - 1] += 1;
			}
		} else {
		    vertexes.push_back(std::make_pair(raw_vertexes[i].first.first, raw_vertexes[i].first.second));
		    auto iter2 = std::find(vertexes.begin(), vertexes.end(), raw_vertexes[i].second);
			if (iter2 != vertexes.end()) {
				g[vertexes.size() - 1][iter2 - vertexes.begin()] += 1;
			} else {
				vertexes.push_back(std::make_pair(raw_vertexes[i].second.first, raw_vertexes[i].second.second));
		    	g[vertexes.size() - 2][vertexes.size() - 1] += 1;
			}
		}
    }

    int n = vertexes.size();
	std::vector<int> deg_in(n);
	std::vector<int> deg_out(n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			deg_in[i] += g[j][i];
			deg_out[i] += g[i][j];
		}
	}

	int v1, v2;
	v1 = v2 = -1;
	for (int i = 0; i < n; ++i) {
		if (deg_in[i] != deg_out[i]) {
			if (v1 == -1) {
				v1 = i;
			} else if (v2 == -1) {
				v2 = i;
				g[v2][v1] += 1;
			}
		}
	}

	int begin = 0;
	while (!deg_out[begin]) {
		++begin;
	}

	std::vector<int> res;
	std::stack<int> st;
	st.push (begin);
	while (!st.empty()) {
		int v = st.top();
		int i;
		for (i = 0; i < n; ++i) {
			if (g[v][i]) {
				break;
			}
		}
		if (i == n) {
			res.push_back(v);
			st.pop();
		} else {
			--g[v][i];
			st.push(i);
		}
	}

	if (v1 != -1) {
		for (int i = 0; i + 1 < res.size(); ++i) {
			if (res[i] == v1 && res[i + 1] == v2) {
				std::vector<int> res2;
				for (int j = i + 1; j < res.size(); ++j) {
					res2.push_back (res[j]);
				}
				for (int j = 1; j <= i; ++j) {
					res2.push_back (res[j]);
				}
				res = res2;
				break;
			}
		}
	}

	std::reverse(res.begin(), res.end());

	int genom_len = k - 1 + res.size() + d + k;
	char genom[genom_len];

	for (int i = 0; i < k; ++i) {
		genom[i] = vertexes[res[0]].first[i];
		genom[k + d + i] = vertexes[res[0]].second[i];
	}
	
	for (int i = 1; i < res.size(); ++i) {
		genom[k - 1 + i] = vertexes[res[i]].first[k - 2];
		genom[k - 1 + i + k + d] = vertexes[res[i]].second[k - 2];
	}

	for (int i = 0; i < genom_len; ++i)
		std::cout << genom[i];
	std::cout << std::endl;

	return 0;
}