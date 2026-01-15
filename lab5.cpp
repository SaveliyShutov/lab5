#include "lab5.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <vector>

int RandomInt(int min_value, int max_value) {
  if (min_value > max_value)
    return min_value;
  int range = max_value - min_value + 1;
  return min_value + (std::rand() % range);
}

void Lab5::GenerateBinaryNumbers(const std::string &filename, std::size_t count,
                                 int min_value, int max_value) {
  std::ofstream out(filename, std::ios::binary);
  if (!out)
    throw std::runtime_error("Cannot open file for writing: " + filename);
  for (std::size_t i = 0; i < count; ++i) {
    std::int32_t v = static_cast<std::int32_t>(RandomInt(min_value, max_value));
    out.write(reinterpret_cast<const char *>(&v), sizeof(v));
  }
}

void Lab5::GenerateBinaryToys(
    const std::string &filename,
    const std::vector<std::tuple<std::string, int, int, int>> &toys) {
  std::ofstream out(filename, std::ios::binary);
  if (!out)
    throw std::runtime_error("Cannot open file for writing: " + filename);
  for (const auto &t : toys) {
    Toy rec{};
    std::strncpy(rec.name, std::get<0>(t).c_str(), sizeof(rec.name) - 1);
    rec.price = static_cast<std::int32_t>(std::get<1>(t));
    rec.min_age = static_cast<std::int32_t>(std::get<2>(t));
    rec.max_age = static_cast<std::int32_t>(std::get<3>(t));
    out.write(reinterpret_cast<const char *>(&rec), sizeof(rec));
  }
}

void Lab5::GenerateTextIntegersOnePerLine(const std::string &filename,
                                          std::size_t count, int min_value,
                                          int max_value) {
  std::ofstream out(filename);
  if (!out)
    throw std::runtime_error("Cannot open file for writing: " + filename);
  for (std::size_t i = 0; i < count; ++i)
    out << RandomInt(min_value, max_value) << '\n';
}

void Lab5::GenerateTextIntegersMultiplePerLine(const std::string &filename,
                                               std::size_t count,
                                               int numbers_per_line,
                                               int min_value, int max_value) {
  if (numbers_per_line <= 0)
    throw std::invalid_argument("numbers_per_line must be > 0");
  std::ofstream out(filename);
  if (!out)
    throw std::runtime_error("Cannot open file for writing: " + filename);
  std::size_t written = 0;
  while (written < count) {
    int per = static_cast<int>(
        std::min<std::size_t>(numbers_per_line, count - written));
    for (int i = 0; i < per; ++i) {
      if (i > 0)
        out << ' ';
      out << RandomInt(min_value, max_value);
      ++written;
    }
    out << '\n';
  }
}

void Lab5::GenerateTextFileWithLines(const std::string &filename,
                                     const std::vector<std::string> &lines) {
  std::ofstream out(filename);
  if (!out)
    throw std::runtime_error("Cannot open file for writing: " + filename);
  for (const auto &l : lines)
    out << l << '\n';
}

void Lab5::Task1_CumulativePrefixes(const std::string &src,
                                    const std::string &dest) {
  std::ifstream in(src, std::ios::binary);
  if (!in) {
    throw std::runtime_error("Cannot open source file: " + src);
  }

  std::vector<std::int32_t> vals;

  std::int32_t x;

  while (in.read((char *)&x, sizeof(x))) {
    vals.push_back(x);
  }

  std::ofstream out(dest, std::ios::binary);
  if (!out) {
    throw std::runtime_error("Cannot open destination file: " + dest);
  }

  for (std::size_t count = 1; count <= vals.size(); ++count) {
    for (std::size_t i = 0; i < count; ++i) {
      out.write((char *)&vals[i], sizeof(vals[i]));
    }
  }
}

std::size_t Lab5::Task2_MatrixClosestRow(const std::string& src,
                                        std::size_t n) {
  if (n == 0) {
    throw std::invalid_argument("n must be > 0");
  }

  std::ifstream in(src, std::ios::binary);
  if (!in) {
    throw std::runtime_error("Cannot open source file: " + src);
  }

  std::vector<std::int32_t> data;
  std::int32_t x;

  while (in.read((char*)&x, sizeof(x))) {
    data.push_back(x);
  }

  while (data.size() < n * n) {
    data.push_back(0);
  }

  std::size_t best_row = 0;
  long long best_abs_sum = -1;

  for (std::size_t row = 0; row < n; ++row) {
    long long sum = 0;

    for (std::size_t col = 0; col < n; ++col) {
      sum += data[row * n + col];
    }

    long long abs_sum = (sum < 0) ? -sum : sum;

    if (row == 0 || abs_sum < best_abs_sum) {
      best_abs_sum = abs_sum;
      best_row = row;
    }
  }

  return best_row + 1;
}


std::vector<std::string> Lab5::Task3_ToysForAges(const std::string &src,
                                                 int age1, int age2) {
  std::ifstream in(src, std::ios::binary);
  if (!in)
    throw std::runtime_error("Cannot open toys file: " + src);
  std::vector<std::string> res;
  Toy t;
  while (in.read(reinterpret_cast<char *>(&t), sizeof(t))) {
    if (t.min_age <= age1 && age1 <= t.max_age && t.min_age <= age2 &&
        age2 <= t.max_age) {
      t.name[sizeof(t.name) - 1] = '\0';
      res.emplace_back(t.name);
    }
  }
  return res;
}

long long Lab5::Task4_ProductMinMax(const std::string &filename) {
  std::ifstream in(filename);
  if (!in)
    throw std::runtime_error("Cannot open file: " + filename);
  long long minv = std::numeric_limits<long long>::max();
  long long maxv = std::numeric_limits<long long>::min();
  long long x;
  bool found = false;
  while (in >> x) {
    found = true;
    if (x < minv)
      minv = x;
    if (x > maxv)
      maxv = x;
  }
  if (!found)
    throw std::runtime_error("No integers in file: " + filename);
  return minv * maxv;
}

std::size_t Lab5::Task5_CountOdd(const std::string &filename) {
  std::ifstream in(filename);
  if (!in)
    throw std::runtime_error("Cannot open file: " + filename);
  std::size_t cnt = 0;
  long long x;
  while (in >> x)
    if ((x & 1LL) != 0)
      ++cnt;
  return cnt;
}

void Lab5::Task6_LineLengths(const std::string &src, const std::string &dest) {
  std::ifstream in(src);
  if (!in)
    throw std::runtime_error("Cannot open file: " + src);
  std::ofstream out(dest);
  if (!out)
    throw std::runtime_error("Cannot open file for writing: " + dest);
  std::string line;
  while (std::getline(in, line))
    out << line.size() << '\n';
}
