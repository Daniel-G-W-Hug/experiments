#include "fmt/format.h"
#include "fmt/ranges.h"

#include "stlab/forest.hpp"

int main() {

  stlab::forest<int> f;

  fmt::print(
      "forest f initialized. f.empty() = {}, f.size() = {}, sizeof(f) = {}\n",
      f.empty(),
      f.size(),
      sizeof(f));
  assert(f.empty());

  // top level nodes (=first level of childs of root level)
  auto one_iter = stlab::trailing_of(f.insert(f.end(), 1));
  auto two_iter = stlab::trailing_of(f.insert(f.end(), 2));
  auto three_iter = stlab::trailing_of(f.insert(f.end(), 3));

  // one child level nodes
  // (to be inserted at trailing edge of parent node)
  auto oneone_iter = stlab::trailing_of(f.insert(one_iter, 11));
  f.insert(one_iter, 12);
  f.insert(one_iter, 13);

  // two child level nodes
  // (to be inserted at trailing edge, otherwise added as leading siblings)
  f.insert(two_iter, 21);
  f.insert(two_iter, 22);
  f.insert(two_iter, 23);
  f.insert(two_iter, 24);

  // oneoneone child level nodes
  f.insert(oneone_iter, 111);
  f.insert(oneone_iter, 112);
  f.insert(oneone_iter, 113);

  f.insert(three_iter, 31);
  f.insert(three_iter, 32);
  f.insert(three_iter, 33);

  fmt::print(
      "forest f initialized. f.empty() = {}, f.size() = {}, sizeof(f) = {}\n",
      f.empty(),
      f.size(),
      sizeof(f));

  // full traversal
  {
    fmt::print("Full traversal:\n");
    int cnt{0};
    for (const auto& iter : f) {
      fmt::print("{}: {}\n", ++cnt, iter);
    }
    fmt::print("\n\n");
  }

  // preorder traversal (parents visited before children)
  {
    fmt::print("Preorder traversal:\n");
    int cnt{0};
    for (const auto& iter : stlab::preorder_range(f)) {
      fmt::print("{}: {}\n", ++cnt, iter);
    }
    fmt::print("\n\n");
  }

  // postorder traversal (children visited before parents)
  {
    fmt::print("Postorder traversal:\n");
    int cnt{0};
    for (const auto& iter : stlab::postorder_range(f)) {
      fmt::print("{}: {}\n", ++cnt, iter);
    }
    fmt::print("\n\n");
  }

  // child-only traversal (parent not visited)
  {
    fmt::print("Child-only traversal (w/o parent):\n");
    int cnt{0};
    for (const auto& iter : stlab::child_range(oneone_iter)) {
      fmt::print("{}: {}\n", ++cnt, iter);
    }
    fmt::print("\n\n");
  }

  // top level child-only traversal (parent not visited)
  {
    fmt::print("Top level child-only traversal (w/o parent):\n");
    int cnt{0};
    for (const auto& iter : stlab::child_range(f.root())) {
      fmt::print("{}: {}\n", ++cnt, iter);
    }
    fmt::print("\n\n");
  }

  return 0;
}