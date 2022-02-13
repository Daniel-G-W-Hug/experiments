#include <functional>
#include <vector>

#include "fmt/format.h"
#include "fmt/ranges.h" // support printing of (nested) containers & tuples

// implement a little reference wrapper to address a sudoku in row, cols, blocks
//
// reference example is 3x3 sudoku with 3 rows, 3 cols

int main(int argc, char* argv[])
{
    constexpr size_t total_size = 16;
    constexpr size_t region_size = 4;

    std::vector<int> cell{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    std::vector<std::reference_wrapper<int>> row, col;

    for (size_t cnt = 0; cnt < total_size; ++cnt)
    {
        // row and cell use the same layout
        row.push_back(cell[cnt]);
    }

    for (size_t curr_col = 0; curr_col < region_size; ++curr_col)
    {
        for (size_t cnt = 0; cnt < region_size; ++cnt)
        {
            // cols have a stride of region_size
            col.push_back(cell[cnt * region_size + curr_col]);
        }
    }

    fmt::print("cell: {}\n", fmt::join(cell, ", "));
    fmt::print("row: {}\n", fmt::join(row, ", "));
    fmt::print("col: {}\n\n", fmt::join(col, ", "));

    // to assign to a reference_wrapper you must access the reference (.get())
    cell[5] = 12;
    row[0].get() = 7;
    col[8].get() = 1;

    fmt::print("cell: {}\n", fmt::join(cell, ", "));
    fmt::print("row: {}\n", fmt::join(row, ", "));
    fmt::print("col: {}\n", fmt::join(col, ", "));

    return 0;
}