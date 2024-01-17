#include <iostream>
#include <vector>

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
    // std::vector<int> data;
    // std::vector<std::vector<int>> triangle; // No auto triangle! It will cause error.

    // for (int row = 0; row < rows; row++)
    // {
    //     data = get_next_row(data); // Have to use data due to using push_back below. With emplace back we could have called the function in emplace_back's parameter.
    //     triangle.push_back(data);
    // }
    // return triangle;

    std::vector<std::vector<int>> triangle({1});
    for (int row = 0; row < rows; row++)
    {
        triangle.push_back(get_next_row(triangle.back())); // Overloaded push_back that takes in a rvalue reference.
    }
    return triangle;
    
}


auto main() -> int {
    generate_triangle(5);
    std::cout << std::numeric_limits<int>::max() << std::endl;
}