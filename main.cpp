// Copyright 2017 olderor (Yevchenko Bohdan)

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#pragma warning(disable:4996)

std::vector<int> prefix_func;
std::string str;
int str_len;

int best_prefix_func_index = 0;

void calc_prefix_function() {
    prefix_func.resize(str_len);
    prefix_func[0] = 0;

    int matched_prefix, candidate;
    for (int current = 1; current < str.size() - 2; ++current) {
        matched_prefix = current - 1;
        candidate = prefix_func[matched_prefix];
        while (candidate != 0 && str[str_len - current - 1] != str[str_len - candidate - 1]) {
            matched_prefix = prefix_func[matched_prefix] - 1;
            candidate = prefix_func[matched_prefix];
        }

        if (candidate == 0) {
            prefix_func[current] = str[str_len - current - 1] == str[str_len - 1];
        } else {
            prefix_func[current] = candidate + 1;
        }
        if (prefix_func[best_prefix_func_index] < prefix_func[current]) {
            best_prefix_func_index = current;
        }
    }
}

int main() {
    std::cin >> str;
    str_len = str.length();

    calc_prefix_function();

    for (int j = 0; j < str_len - best_prefix_func_index - 1; ++j) {
        std::cout << str[j];
    }
    std::cout << "(";
    for (int j = str_len - best_prefix_func_index - 1; 
        j < str_len - prefix_func[best_prefix_func_index]; ++j) {
        std::cout << str[j];
    }
    std::cout << ")\n";
    return 0;
}
