#include <functional>
#include <iostream>
#include <vector>

#include "hd/hd_keypress.hpp"

#include "fmt/format.h"
#include "fmt/ranges.h" // support printing of (nested) containers & tuples

// implement a little reference wrapper to address a sudoku in row, cols, blocks
//
// reference example is 3x3 sudoku with 3 rows, 3 cols

int main(int argc, char* argv[])
{
    // constexpr size_t total_size = 16;
    // constexpr size_t region_size = 4;
    // constexpr size_t bx_size = 2;
    // constexpr size_t by_size = 2;

    constexpr size_t total_size = 36;
    constexpr size_t region_size = 6;
    constexpr size_t bx_size = 2;
    constexpr size_t by_size = 3;

    static_assert(total_size == region_size * region_size, "total_size and region_size don't match.");
    static_assert(region_size == bx_size * by_size, "region_size and block_sizes don't match.");

    // std::vector<int> cell{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::vector<int> cell{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                          16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

    std::vector<std::reference_wrapper<int>> row, col, blk;

    for (size_t curr_row = 0; curr_row < region_size; ++curr_row)
    {
        size_t initial_element = curr_row * region_size;

        for (size_t cnt = 0; cnt < region_size; ++cnt)
        {
            size_t offset = cnt;

            // row and cell use the same layout, i.e. with a stride of 1
            row.push_back(cell[initial_element + offset]);
        }
    }

    for (size_t curr_col = 0; curr_col < region_size; ++curr_col)
    {

        size_t initial_element = curr_col;

        for (size_t cnt = 0; cnt < region_size; ++cnt)
        {
            size_t offset = cnt * region_size;

            // cols have a stride of region_size
            col.push_back(cell[initial_element + offset]);
        }
    }

    for (size_t curr_blk = 0; curr_blk < region_size; ++curr_blk)
    {
        size_t initial_element = (curr_blk % by_size) * bx_size + (curr_blk / by_size) * by_size * region_size;

        for (size_t cnt = 0; cnt < region_size; ++cnt)
        {
            size_t offset = cnt % bx_size + (cnt / bx_size) * region_size;

            // block elements have a complex stride
            blk.push_back(cell[initial_element + offset]);
        }
    }

    fmt::print("cell: {}\n", fmt::join(cell, ", "));
    fmt::print("row: {}\n", fmt::join(row, ", "));
    fmt::print("col: {}\n", fmt::join(col, ", "));
    fmt::print("blk: {}\n\n", fmt::join(blk, ", "));

    // to assign to a reference_wrapper you must access the reference (.get())
    cell[5] = 80;
    row[0].get() = 85;
    col[3].get() = 90;

    fmt::print("cell[5] = {}\n", cell[5]);
    fmt::print("row[0] = {}\n", row[0].get());
    fmt::print("col[3] = {}\n\n", col[3].get());

    fmt::print("cell: {}\n", fmt::join(cell, ", "));
    fmt::print("row: {}\n", fmt::join(row, ", "));
    fmt::print("col: {}\n", fmt::join(col, ", "));
    fmt::print("blk: {}\n", fmt::join(blk, ", "));

    hd::cmdl_wait_for_enter();

    return 0;
}