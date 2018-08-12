#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <random>
#include <vector>

bool IsNotPrime(int x, int y);

void MapFiller(std::map<int, std::vector<int>> &primeWithVal,
               std::vector<int> &primeNum, std::vector<int> &randoNum);

void PrintPrimesAndValues(std::map<int, std::vector<int>> &primeWithVal);

std::vector<int> RandomNumbersGenerator(int M, int N);

std::vector<int> PrimeNumbersGenerator(int M);

int main() {
  std::srand(std::time(nullptr));
  int N, M;
  std::cin >> N;
  std::cin.get();
  std::cin >> M;

  std::vector<int> randoNum = RandomNumbersGenerator(M, N);
  std::vector<int> primeNum = PrimeNumbersGenerator(M);

  std::map<int, std::vector<int>> primeWithVal;
  MapFiller(primeWithVal, primeNum, randoNum);
  PrintPrimesAndValues(primeWithVal);
  return 0;
}

std::vector<int> PrimeNumbersGenerator(int M) {
  std::vector<int> allNum(M);
  std::iota(allNum.begin(), allNum.end(), 1);
  std::vector<int> primeNum(allNum.begin(), allNum.end());
  primeNum.erase(std::remove_if(primeNum.begin(), primeNum.end(),
                                [](int x) { return IsNotPrime(x, x - 1); }),
                 primeNum.end());
  return primeNum;
}

std::vector<int> RandomNumbersGenerator(int M, int N) {
  std::vector<int> randoNum(N);
  std::generate_n(randoNum.begin(), N, [M]() { return rand() % M; });
  std::sort(randoNum.begin(), randoNum.end());
  randoNum.erase(std::unique(randoNum.begin(), randoNum.end()), randoNum.end());
  return randoNum;
}

void PrintPrimesAndValues(std::map<int, std::vector<int>> &primeWithVal) {
  for (auto n : primeWithVal) {
    std::cout << n.first << " - ";
    auto m = n.second;
    std::copy(m.begin(), m.end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;
  }
}

void MapFiller(std::map<int, std::vector<int>> &primeWithVal,
               std::vector<int> &primeNum, std::vector<int> &randoNum) {

  for (auto n : primeNum) {
    std::vector<int> val;
    std::copy_if(randoNum.begin(), randoNum.end(), std::back_inserter(val),
                 [n](int num) { return num % n == 0; });
    primeWithVal.insert(std::make_pair(n, val));
  }
}

bool IsNotPrime(int x, int y) {
  if (y == 1 || x == 1)
    return false;
  if (x % y == 0)
    return true;
  else
    return IsNotPrime(x, y - 1);
}
