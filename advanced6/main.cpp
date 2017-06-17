// Copyright 2017 olderor (Yevchenko Bohdan)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Compress decimal number to the periodic decimal number.
struct decimal_number_compressor {
 public:
    // Initialize with the given decimal number.
    explicit decimal_number_compressor(std::string &number);

    // Try to compress the data.
    // Return periodic decimal number.
    std::string compress();

 private:
    // Initial data.
    std::string data;

    // Initialize prefix function.
    std::vector<int> get_prefix_function_data();

    // Compress the given data to the new data with periodical part.
    // prefix_function_data - precomputed prefix function data.
    // Return the periodic decimal number.
    std::string compress(std::vector<int> &prefix_function_data) const;
};

// Get data from input stream.
void read_data(std::istream &_Istr, std::string &data);

// Put data to output stream.
void print_data(std::ostream &_Ostr, std::string &data);

// Get answer to the given problem using given data.
std::string solve(std::string &data);

// Entry point.
int main();

decimal_number_compressor::decimal_number_compressor(std::string &number) {
    data = number;
}

std::string decimal_number_compressor::compress() {
    std::vector<int> prefix_function_data = get_prefix_function_data();
    return compress(prefix_function_data);
}

std::vector<int> decimal_number_compressor::get_prefix_function_data() {
    // Finding fractional part delimiter.
    int start_index = 0;
    for (int i = 0; i < data.length(); ++i) {
        if (data[i] == ',' || data[i] == '.') {
            start_index = i;
            break;
        }
    }

    // Initializing prefix function data with default values.
    std::vector<int> prefix_function_data(data.length());
    prefix_function_data[0] = 0;

    // Computing prefix function.
    int matched_prefix, candidate;
    for (int current = 1; current < data.length() - start_index; ++current) {
        matched_prefix = current - 1;
        candidate = prefix_function_data[matched_prefix];
        while (candidate != 0 &&
          data[data.length() - current - 1] !=
            data[data.length() - candidate - 1]) {
            matched_prefix = prefix_function_data[matched_prefix] - 1;
            candidate = prefix_function_data[matched_prefix];
        }

        if (candidate == 0) {
            prefix_function_data[current] =
              data[data.length() - current - 1] == data[data.length() - 1];
        } else {
            prefix_function_data[current] = candidate + 1;
        }
    }
    return prefix_function_data;
}

std::string decimal_number_compressor::compress(
  std::vector<int> &prefix_function_data) const {
    // Finding index of largest value in the prefix function data.
    int prefix_function_index = 0;
    for (int i = 1; i < prefix_function_data.size(); ++i) {
        if (prefix_function_data[i] >
          prefix_function_data[prefix_function_index]) {
            prefix_function_index = i;
        }
    }

    // Creates new string stream and fills it with integer part, delimiter
    // and fractional part which is not included into periodical part.
    std::stringstream compressed_data;
    for (int j = 0; j < data.length() - prefix_function_index - 1; ++j) {
        compressed_data << data[j];
    }
    // Appends periodical part to the stringstream.
    compressed_data << '(';
    for (int j = static_cast<int>(data.length()) - prefix_function_index - 1;
         j < data.length() - prefix_function_data[prefix_function_index];
         ++j) {
        compressed_data << data[j];
    }
    compressed_data << ')';

    return compressed_data.str();
}

void read_data(std::istream &_Istr, std::string &data) {
    _Istr >> data;
}

void print_data(std::ostream &_Ostr, std::string &data) {
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
