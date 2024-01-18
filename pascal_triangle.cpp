#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <ranges>
#include <format>

std::vector<int> get_next_row(const std::vector<int> & last_row) {
    std::vector next_row{1};
    if (last_row.empty()) {
        return next_row;
    }

    for (size_t idx = 0; idx + 1 < last_row.size(); idx++) {
        next_row.emplace_back(last_row[idx] + last_row[idx + 1]);
    }
    next_row.emplace_back(1);
    return next_row;
}

auto generate_triangle(int rows) {

    // No perfect forwarding
    // std::vector<int> data;
    // std::vector<std::vector<int>> triangle; // No auto triangle! It will cause error.

    // for (int row = 0; row < rows; row++)
    // {
    //     data = get_next_row(data); // Have to use data due to using push_back below. With emplace back we could have called the function in emplace_back's parameter.
    //     triangle.push_back(data);
    // }
    // return triangle;


    // With perfect forwarding
    std::vector<std::vector<int>> triangle{{1}};
    for (int row = 1; row < rows; row++)
    {
        triangle.emplace_back(get_next_row(triangle.back())); // Overloaded push_back that takes in a rvalue reference.
    }
    return triangle;
    
}


// Bad practice to overlaod << but it is ok for small projects
template<typename T>
std::ostream& operator << (std::ostream& s, const std::vector<std::vector<T>>& triangle) {
    for (const auto &row : triangle) {
        std::ranges::copy(row, std::ostream_iterator<T>(s, " "));
        s << '\n';
    }
    return s;
}

void show_vectors(std::ostream& s, const std::vector<std::vector<int>>& v) {
    size_t final_row_size = v.back().size();
    std::string spaces(final_row_size * 3, ' ');
    for (const auto& row : v) 
    {
        s << spaces;
        if (spaces.size() > 3) {
            spaces.resize(spaces.size() - 3);
        }
        for (const auto& data : row) {
            s << std::format("{: ^{}}", data, 6);
        }
        s << '\n';
    } 
    

}

auto main() -> int {
    auto triangle = generate_triangle(16);
    show_vectors(std::cout, triangle);
}