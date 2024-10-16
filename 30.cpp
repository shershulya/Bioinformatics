//                                         # Problem 30: Implement 2-BreakOnGenome

// Implement 2-BreakOnGenome
// Solve the 2-Break On Genome Graph Problem.
// Given: A genome P, followed by indices i, i', j, and j'.
// Return: The genome P' resulting from applying the 2-break operation.


// (+1 -2 -4 +3)
// 1, 6, 3, 8

// (+2 -1) (-3 +4)

#include <iostream>
#include <vector>
#include <sstream>

void PrintPermutation(std::vector<int> permutation, std::vector<char> permutation_signs) {
    std::cout << '(';
    int n = permutation.size() - 1;
    for (int i = 0; i < n; ++i) {
        std::cout << permutation_signs[i] << permutation[i] << " ";
    }
    std::cout << permutation_signs[n] << permutation[n] << ')';
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

std::vector<std::vector<int>> ConstructGraph(std::string permutation_p) {
    std::vector<std::vector<int>> edges;
    int begin_cycle;
    char cur_char;
    for(int i = 0; i < permutation_p.length(); ++i){
        cur_char = permutation_p[i];
        if (cur_char == '(' ) {
            begin_cycle = i + 1;
        } else if (cur_char == ')' ) {
            ConstructCircularChromosome(permutation_p.substr(begin_cycle, i - begin_cycle), edges);
        }
    }
    return edges;
}

void graph_to_genome(std::vector<std::vector<int>> &edges) {
    int n = edges.size() * 2;
    int visited[n + 1] = {0};
    std::vector <int> graph[n + 1];
    for(int i = 0; i < edges.size(); ++i){
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 0; i < edges.size(); ++i) {
        int left = edges[i][0];
        if (visited[left] == 0) {
            visited[left] = 1;
            int right = left % 2 ? left + 1 : left - 1;
            std::vector<int> permutation_nums;
            std::vector<char> permutation_signs;
            while (true) {
                if (left % 2) {
                    permutation_signs.push_back('-');
                    permutation_nums.push_back((left + 1) / 2);
                } else {
                    permutation_signs.push_back('+');
                    permutation_nums.push_back(left / 2);
                }
                int cur = graph[left][0];
                visited[cur] = 1;
                if (cur == right) {
                    PrintPermutation(permutation_nums, permutation_signs);
                    break;
                }
                left = cur % 2 ? cur + 1 : cur - 1;
                visited[left] = 1;
            }
        }
    }
    std::cout << std::endl;
}

int main() {
    std::string permutation_p, indices, s;
    std::getline(std::cin, permutation_p);
    std::getline(std::cin, indices);
    std::istringstream iss(indices);
    std::vector<int> idx;
    while (getline(iss, s, ',')) {
        idx.push_back(std::stoi(s));
    }

    std::vector<std::vector<int>> edges = ConstructGraph(permutation_p);


    int first_edge, second_edge;
    for(int i = 0; i < edges.size(); ++i){
        if ((edges[i][0] == idx[0] && edges[i][1] == idx[1])
            || (edges[i][0] == idx[1] && edges[i][1] == idx[0])) {
            first_edge = i;
        }
        if ((edges[i][0] == idx[2] && edges[i][1] == idx[3])
            || (edges[i][0] == idx[3] && edges[i][1] == idx[2])) {
            second_edge = i;
        }
    }

    if (edges[first_edge][0] == idx[0]) {
        if (edges[second_edge][0] == idx[2]) {
            edges[first_edge][1] = idx[2];
            edges[second_edge][0] = idx[1];
        } else {
            edges[first_edge][1] = idx[2];
            edges[second_edge][1] = idx[1];
        }
    } else {
        if (edges[second_edge][0] == idx[2]) {
            edges[first_edge][0] = idx[2];
            edges[second_edge][0] = idx[1];
        } else {
            edges[first_edge][0] = idx[2];
            edges[second_edge][1] = idx[1];
        }
    }

    graph_to_genome(edges);

    return 0;
}