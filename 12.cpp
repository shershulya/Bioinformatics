//                                         # Problem 12: Find a k-Universal Circular String

// k-Universal Circular String Problem
// Find a k-universal circular binary string.
// Given: An integer k.
// Return: A k-universal circular string. (If multiple answers exist, you may return any one.)


// 4

// 0000110010111101

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>
#include <bitset>

int main() {
	int k;
    std::cin >> k;

    std::vector<std::string> bin_vec;
    int pow = 1 << k;
    for (int i = 0; i < pow; ++i) {
        bin_vec.push_back(std::bitset<32>(i).to_string());   
    }

    for (int i = 0; i < bin_vec.size(); ++i)
       	bin_vec[i] = bin_vec[i].substr(bin_vec[i].size() - k, bin_vec[i].size());

    for (int i = 0; i < bin_vec.size(); ++i) {
    	std::cout << bin_vec[i] << std::endl;
    }

    std::vector<std::pair<std::string, std::string>> raw_vertexes;
    std::string s;
    for (int i = 0; i < bin_vec.size(); ++i) {
    	std::string prefix (bin_vec[i], 0, k - 1);
    	std::string suffix (bin_vec[i], 1, k - 1);
    	raw_vertexes.push_back(std::make_pair(prefix, suffix));
    }

    std::vector<std::vector<int>> g(4 * raw_vertexes.size(), std::vector<int>(4 * raw_vertexes.size()));
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

	std::cout << std::setw(6);
    for (int i = 0; i < n; ++i) {
    	if (i == 0)
    		std::cout << std::setw(12) << vertexes[i];
    	else
    		std::cout << std::setw(6) << vertexes[i];
    }
    std::cout << std::endl;

    g.resize(n);
    for (int i = 0; i < g.size(); ++i) {
    	g[i].resize(n);
    	std::cout << std::setw(6) << vertexes[i];
    	for (int j = 0; j < g[i].size(); ++j) {
    		std::cout << std::setw(6) << g[i][j];
    	}
    	std::cout << std::endl;
    }

	int v1, v2;
	v1 = v2 = -1;
	for (int i = 0; i < n; ++i) {
		if (deg_in[i] != deg_out[i]) {
			if (v1 == -1) {
				v1 = i;
			} else if (v2 == -1) {
				v2 = i;
				++g[v1][v2];
			}
		}
	}

	int begin = 0;
	while (!deg_out[begin])
		++begin;

	std::vector<int> res;
	std::stack<int> st;
	st.push (begin);
	while (!st.empty()) {
		int v = st.top();
		int i;
		for (i = 0; i < n; ++i)
			if (g[v][i]) {
				std::cout << vertexes[i] << std::endl;
				break;
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
			if (res[i] == v2 && res[i + 1] == v1) {
				std::vector<int> res2;
				for (int j = i + 1; j < res.size(); ++j)
					res2.push_back (res[j]);
				for (int j = 1; j <= i; ++j)
					res2.push_back (res[j]);
				res = res2;
				break;
			}
		}
	}

	std::reverse(res.begin(), res.end());
	std::cout << std::endl;
	for (int i = 0; i < res.size(); ++i)
		std::cout << res[i] << " " << vertexes[res[i]] << std::endl;

	int genom_len = k - 1 + res.size() - 1;
	char genom[genom_len];

	for (int i = 0; i < k; ++i) {
		genom[i] = vertexes[res[0]][i];
		std::cout << genom[i];
	}
	std::cout << std::endl;
	
	for (int i = 1; i < res.size(); ++i)
		genom[k - 2 + i] = vertexes[res[i]][k - 2];

	for (int i = 0; i < pow; ++i)
		std::cout << genom[i];
	std::cout << std::endl;

	return 0;
}