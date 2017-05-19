// Copyright 2017 olderor (Yevchenko Bohdan)

#include <iostream>
#include <vector>
#include <string>

struct decimal_number_compressor {
 public:
    decimal_number_compressor(std::string &number) {
        data = number;
        data_length = data.length();
    }

    std::string compress() {
        const int fractional_part_start_index = find_fractional_part_start_index();
        if (fractional_part_start_index == -1) {
            return data;
        }

        set_prefix_function_data(fractional_part_start_index);
        const int max_index = find_index_with_maximum_prefix_function_value();

        return compress(max_index);
    }

 private:
    std::vector<int> prefix_function_data;
    std::string data;
    int data_length;

    void set_prefix_function_data(const int start_index) {
        prefix_function_data.clear();
        prefix_function_data.resize(data_length);
        prefix_function_data[0] = 0;

        int matched_prefix, candidate;
        for (int current = 1; current < data_length - start_index; ++current) {
            matched_prefix = current - 1;
            candidate = prefix_function_data[matched_prefix];
            while (candidate != 0 && data[data_length - current - 1] != data[data_length - candidate - 1]) {
                matched_prefix = prefix_function_data[matched_prefix] - 1;
                candidate = prefix_function_data[matched_prefix];
            }

            if (candidate == 0) {
                prefix_function_data[current] = data[data_length - current - 1] == data[data_length - 1];
            } else {
                prefix_function_data[current] = candidate + 1;
            }
        }
    }

    const int find_fractional_part_start_index() const {
        for (int i = 0; i < data_length; ++i) {
            if (data[i] == ',' || data[i] == '.') {
                return i;
            }
        }
        return -1;
    }

    const int find_index_with_maximum_prefix_function_value() const {
        int max_prefix_function_index = 0;
        for (int i = 1; i < prefix_function_data.size(); ++i) {
            if (prefix_function_data[i] > prefix_function_data[max_prefix_function_index]) {
                max_prefix_function_index = i;
            }
        }
        return max_prefix_function_index;
    }

    std::string compress(const int best_prefix_func_index) const {
        std::string compressed_data = "";
        for (int j = 0; j < data_length - best_prefix_func_index - 1; ++j) {
            compressed_data += data[j];
        }
        compressed_data += '(';
        for (int j = data_length - best_prefix_func_index - 1;
            j < data_length - prefix_function_data[best_prefix_func_index]; ++j) {

            compressed_data += data[j];
        }
        compressed_data += ')';
    }
};

void read_data(
    std::istream &_Istr,
    std::string &data) {

    _Istr >> data;
}

void print_data(
    std::ostream  &_Ostr,
    std::string &data) {

    _Ostr << data;
}

std::string solve(std::string &data) {
    decimal_number_compressor compressor = decimal_number_compressor(data);
    return compressor.compress();
}

int main() {
    std::string data;

    read_data(std::cin, data);

    std::string result = solve(data);

    print_data(std::cout, result);

    return 0;
}
