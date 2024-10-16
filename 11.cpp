//                                         # Problem 11: Reconstruct a String from its k-mer Composition

// String Reconstruction Problem
// Reconstruct a string from its k-mer composition.
// Given: An integer k followed by a list of k-mers Patterns.
// Return: A string Text with k-mer composition equal to Patterns. (If multiple answers exist, you may return any one.)


// 4
// CTTA
// ACCA
// TACC
// GGCT
// GCTT
// TTAC

// GGCTTACCA

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

int main() {
	int k;
    std::cin >> k;
    std::vector<std::pair<std::string, std::string>> raw_vertexes;
    std::string s;
    while (std::cin >> s) {
    	std::string prefix (s, 0, k - 1);
    	std::string suffix (s, 1, k - 1);
    	raw_vertexes.push_back(std::make_pair(prefix, suffix));
    }

    std::vector<std::vector<int>> g(4 * raw_vertexes.size(), std::vector<int>(4 * raw_vertexes.size(), 0));
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
	int genom_len = k - 1 + res.size();
	char genom[genom_len];

	for (int i = 0; i < k; ++i)
		genom[i] = vertexes[res[0]][i];
	
	for (int i = 1; i < res.size(); ++i)
		genom[k - 1 + i] = vertexes[res[i]][k - 2];

	for (int i = 0; i < genom_len; ++i)
		std::cout << genom[i];
	std::cout << std::endl;

	return 0;
}