//                                         # Problem 28: Compute the 2-Break Distance Between a Pair of Genomes

// 2-Break Distance Problem
// Find the 2-break distance between two genomes.
// Given: Two genomes with circular chromosomes on the same set of synteny blocks.
// Return: The 2-break distance between these two genomes.


// (+1 +2 +3 +4 +5 +6)
// (+1 -3 -6 -5)(+2 -4)

// 3

#include <iostream>
#include <vector>
#include <sstream>

void DFS(int node, std::vector<int> graph[], std::vector<bool>& visited) {
    if(visited[node])
        return;
    
    visited[node] = true;
    
    for(int i = 0; i < graph[node].size(); ++i){
        DFS(graph[node][i], graph, visited);
    }
}
int CountConnectedComponents(int n, std::vector<std::vector<int>>& edges) {
    if(!n)
        return 0;
    
    std::vector <int> graph[n + 1];
    for(int i = 0; i < edges.size(); ++i){
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    int number_cc = 0;
    std::vector <bool> visited(n);
    for(int i = 1; i <= n; ++i){
        if(!visited[i]){
            DFS(i, graph, visited);
            number_cc++;
        }
    }
    
    return number_cc;
}

void ConstructCircularChromosome(std::string permutation, std::vector<std::vector<int>> &edges) {
    std::vector<int> permutation_nums;
    std::vector<char> permutation_signs;
    std::istringstream iss(permutation);
    std::string s;
    while (getline(iss, s, ' ')) {
        permutation_signs.push_back(s[0]);
        permutation_nums.push_back(std::stoi(s.substr(1, s.size() - 1)));
    }
    
    int perm_len = permutation_nums.size();

    char prev_sign = permutation_signs[perm_len - 1];
    int prev_num = permutation_nums[perm_len - 1];
    for(int i = 0; i < perm_len; i++){
        char curr_sign = permutation_signs[i];
        int curr_num = permutation_nums[i];
        if (curr_sign == '+' && prev_sign == '+') {
            edges.push_back({2 * prev_num, 2 * curr_num - 1});
        } else if (curr_sign == '+' && prev_sign == '-') {
            edges.push_back({2 * prev_num - 1, 2 * curr_num - 1});
        } else if (curr_sign == '-' && prev_sign == '-') {
            edges.push_back({2 * prev_num - 1, 2 * curr_num});
        } else if (curr_sign == '-' && prev_sign == '+') {
            edges.push_back({2 * prev_num, 2 * curr_num});
        }
        prev_sign = curr_sign;
        prev_num = curr_num;
    }
}

void ConstructGraph(std::string permutation_p, std::string permutation_q, int &max_vertex,
            std::vector<std::vector<int>> &edges_p, std::vector<std::vector<int>> &edges_q) {
    int begin_cycle;
    char cur_char;
    for(int i = 0; i < permutation_p.length(); ++i){
        cur_char = permutation_p[i];
        if (cur_char == '(' ) {
            begin_cycle = i + 1;
        }
        if (cur_char == ')' ) {
            ConstructCircularChromosome(permutation_p.substr(begin_cycle, i - begin_cycle), edges_p);
        }
    }

    for (int i = 0; i < edges_p.size(); ++i) {
        if (edges_p[i][0] > max_vertex) {
            max_vertex = edges_p[i][0];
        }
        if (edges_p[i][1] > max_vertex) {
            max_vertex = edges_p[i][1];
        }
    }

    for(int i = 0; i < permutation_q.length(); ++i){
        cur_char = permutation_q[i];
        if (cur_char == '(' ) {
            begin_cycle = i + 1;
        } else if (cur_char == ')' ) {
            ConstructCircularChromosome(permutation_q.substr(begin_cycle, i - begin_cycle), edges_q);
        }
    }
    return;
}

int main() {
    std::string permutation_p, permutation_q;
    std::getline(std::cin, permutation_p);
    std::getline(std::cin, permutation_q);

    int max_vertex = 0;
    std::vector<std::vector<int>> edges_p, edges_q;
    ConstructGraph(permutation_p, permutation_q, max_vertex, edges_p, edges_q);
    
    edges_p.insert(edges_p.end(), edges_q.begin(), edges_q.end());

    int number_cc = CountConnectedComponents(max_vertex, edges_p);
    int number_of_blocks = max_vertex / 2;
    std::cout << number_of_blocks - number_cc << std::endl;

    return 0;
}