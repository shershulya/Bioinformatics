//                                         # Problem 21: Find the Minimum Number of Coins Needed to Make Change

// The Change Problem
// Find the minimum number of coins needed to make change.
// Given: An integer money and an array Coins of positive integers.
// Return: The minimum number of coins with denominations Coins that changes money.


// 40
// 1,5,10,20,25,50

// 2

#include <iostream>
#include <vector>
#include <sstream>

#include <climits>

int change(int money, std::vector<int> coins) {
    std::vector<int> min_num_coins(money + 1, 0);
    for (int m = 1; m <= money; ++m) {
        min_num_coins[m] = INT_MAX;
        for (int i = 0; i < coins.size(); ++i) {
            int coin = coins[i];
            if (m >= coin) {
                int new_min_num_coins = min_num_coins[m - coin] + 1;
                if (new_min_num_coins < min_num_coins[m]) {
                    min_num_coins[m] = new_min_num_coins;
                }
            }
        }
    }

    return min_num_coins[money];
}


int main(void) {
    int money;
    std::cin >> money;
    
    std::string s, tmp; 
    std::cin >> s;
    std::stringstream ss(s);
    std::vector<int> coins;

    while(getline(ss, tmp, ',')){
        coins.push_back(std::stoi(tmp));
    }

    std::cout << change(money, coins) << std::endl;
    return 0;
}