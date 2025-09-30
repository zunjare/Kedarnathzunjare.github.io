#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<vector<string>>> recipes;
unordered_map<string, int> memo;

// Recursive function to calculate minimum cost
int get_cost(const string &potion) {
    if (memo.count(potion)) 
        return memo[potion];
    
    if (!recipes.count(potion))  // Raw ingredient
        return 0;
    
    int min_cost = INT_MAX;
    
    for (const auto &ing_list : recipes[potion]) {
        int total = ing_list.size() - 1; // base cost (k-1)
        for (const auto &ing : ing_list) {
            total += get_cost(ing);  // add ingredient preparation cost
        }
        min_cost = min(min_cost, total);
    }

    memo[potion] = min_cost;
    return min_cost;
}

int main() {
    int n;
    cin >> n;
    cin.ignore(); // to skip newline after number

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        
        int eq_pos = line.find('=');
        string res = line.substr(0, eq_pos);
        string ing_str = line.substr(eq_pos + 1);
        
        vector<string> ingredients;
        stringstream ss(ing_str);
        string item;
        while (getline(ss, item, '+')) {
            ingredients.push_back(item);
        }
        
        recipes[res].push_back(ingredients);
    }
    
    string target;
    cin >> target;
    
    cout << get_cost(target) << endl;
    return 0;
}
