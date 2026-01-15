#ifndef LAB5_H_
#define LAB5_H_

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

struct Toy {
  char name[64];
  std::int32_t price;
  std::int32_t min_age;
  std::int32_t max_age;
};

class Lab5 {
public:
  static void GenerateBinaryNumbers(const std::string &filename,
                                    std::size_t count, int min_value = -100,
                                    int max_value = 100);

  static void GenerateBinaryToys(
      const std::string &filename,
      const std::vector<std::tuple<std::string, int, int, int>> &toys);

  static void GenerateTextIntegersOnePerLine(const std::string &filename,
                                             std::size_t count,
                                             int min_value = -100,
                                             int max_value = 100);

  static void GenerateTextIntegersMultiplePerLine(const std::string &filename,
                                                  std::size_t count,
                                                  int numbers_per_line = 5,
                                                  int min_value = -100,
                                                  int max_value = 100);

  static void GenerateTextFileWithLines(const std::string &filename,
                                        const std::vector<std::string> &lines);

  static void Task1_CumulativePrefixes(const std::string &src,
                                       const std::string &dest);

  static std::size_t Task2_MatrixClosestRow(const std::string &src,
                                            std::size_t n);

  static std::vector<std::string>
  Task3_ToysForAges(const std::string &src, int age1 = 4, int age2 = 10);

  static long long Task4_ProductMinMax(const std::string &filename);

  static std::size_t Task5_CountOdd(const std::string &filename);

  static void Task6_LineLengths(const std::string &src,
                                const std::string &dest);
};

#endif // LAB5_H_
