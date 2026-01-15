#include "lab5.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <tuple>
#include <vector>

int main() {
  try {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    const std::string nums = "numbers.bin";
    const std::string prefixes = "prefixes.bin";
    const std::string toys = "toys.bin";
    const std::string one_per = "one_per_line.txt";
    const std::string multi = "multi_per_line.txt";
    const std::string lines = "lines.txt";
    const std::string lengths = "lengths.txt";

    Lab5::GenerateBinaryNumbers(nums, 12, -20, 20);
    std::vector<std::tuple<std::string, int, int, int>> toylist = {
      {"Teddy", 500, 1, 6}, {"Lego", 1200, 6, 12}, {"Puzzle", 300, 4, 10}
    };
    Lab5::GenerateBinaryToys(toys, toylist);
    Lab5::GenerateTextIntegersOnePerLine(one_per, 10, -50, 50);
    Lab5::GenerateTextIntegersMultiplePerLine(multi, 20, 5, -50, 50);
    Lab5::GenerateTextFileWithLines(lines, {"Hello", "", "C++"});

    Lab5::Task1_CumulativePrefixes(nums, prefixes);
    std::size_t row = Lab5::Task2_MatrixClosestRow(nums, 4);
    auto suitable = Lab5::Task3_ToysForAges(toys, 4, 10);
    long long prod = Lab5::Task4_ProductMinMax(one_per);
    std::size_t oddcnt = Lab5::Task5_CountOdd(multi);
    Lab5::Task6_LineLengths(lines, lengths);

    std::cout << "Row closest to zero: " << row << '\n';
    std::cout << "Toys for 4 and 10:\n";
    for (const auto& s : suitable) std::cout << "  " << s << '\n';
    std::cout << "Min*Max = " << prod << '\n';
    std::cout << "Odd count = " << oddcnt << '\n';
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  return 0;
}
