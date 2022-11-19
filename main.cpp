#include "hash_table.h"
#include <iostream>

void TestAdd(HashTable &hash_table, const std::string &name, int score) {
  std::cout << "Add (" << name << ", " << score << ")." << std::endl;
  if (hash_table.add(name, score)) {
    std::cout << "Add successfully." << std::endl;
  } else {
    std::cout << "Add unsuccessfully. The hash table contain a student "
                 "with the same name."
              << std::endl;
  }
  std::cout << "Current hash table:" << std::endl;
  hash_table.print();
  std::cout << std::endl;
}

void TestSearch(HashTable &hash_table, const std::string &name) {
  std::cout << "Search " << name << "." << std::endl;
  int res = hash_table.search(name);
  if (res != -1) {
    std::cout << "The score is " << res << "." << std::endl;
  } else {
    std::cout << "Cannot find the student in the hash table." << std::endl;
  }
  std::cout << "Current hash table:" << std::endl;
  hash_table.print();
  std::cout << std::endl;
}

void TestDelete(HashTable &hash_table, const std::string &name) {
  std::cout << "Delete " << name << "." << std::endl;
  if (hash_table.remove(name)) {
    std::cout << "Delete successfully." << std::endl;
  } else {
    std::cout
        << "Delete unsuccessfully. Cannot find the student in the hash table."
        << std::endl;
  }
  std::cout << "Current hash table:" << std::endl;
  hash_table.print();
  std::cout << std::endl;
}

void Test(std::string name) {
  std::cout << name << ":" << HashTable::hashFunction(name, 37, 7) << std::endl;
}

int main() {
  int testcase;
  std::cin >> testcase;

  if (testcase < 1 || testcase > 7) {
    std::cout << "test case should be in [1,7]! " << testcase << " found\n";
    return 0;
  }
  if (testcase == 1) {
    HashTable ht(7, 3, ProbeMode::Linear);
    TestAdd(ht, "kiwi", 60);
    TestAdd(ht, "rebecca", 70);
    TestAdd(ht, "maine", 80);
    TestAdd(ht, "david", 90);
    TestAdd(ht, "maine", 100);
    TestAdd(ht, "maine", 100);
    TestSearch(ht, "maine");
    TestDelete(ht, "kiwi");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestAdd(ht, "maine", 100);
  }
  else if (testcase == 2) {
    HashTable ht(7, 3, ProbeMode::Quadratic);
    TestAdd(ht, "kiwi", 60);
    TestAdd(ht, "rebecca", 70);
    TestAdd(ht, "maine", 80);
    TestAdd(ht, "david", 90);
    TestAdd(ht, "maine", 100);
    TestAdd(ht, "maine", 100);
    TestSearch(ht, "maine");
    TestDelete(ht, "kiwi");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestAdd(ht, "maine", 100);
  }
  else if (testcase == 3) {
    HashTable ht(7, 3, ProbeMode::DoubleHash);
    TestAdd(ht, "kiwi", 60);
    TestAdd(ht, "rebecca", 70);
    TestAdd(ht, "maine", 80);
    TestAdd(ht, "david", 90);
    TestAdd(ht, "maine", 100);
    TestAdd(ht, "maine", 100);
    TestSearch(ht, "maine");
    TestDelete(ht, "kiwi");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestAdd(ht, "maine", 100);
  }
  else if (testcase == 4) {
    HashTable ht(3, 3, ProbeMode::Linear);
    TestAdd(ht, "kiwi", 60);
    TestAdd(ht, "rebecca", 70);
    TestAdd(ht, "maine", 80);
    TestAdd(ht, "falco", 90);
    TestAdd(ht, "david", 91);
    TestAdd(ht, "lucy", 92);
    TestAdd(ht, "dorio", 93);
    TestAdd(ht, "pilar", 94);
    TestAdd(ht, "pilar", 94);
    TestSearch(ht, "maine");
    TestDelete(ht, "kiwi");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestAdd(ht, "maine", 100);
  }
  else if (testcase == 5) {
    HashTable ht(3, 3, ProbeMode::Quadratic);
    TestAdd(ht, "kiwi", 60);
    TestAdd(ht, "rebecca", 70);
    TestAdd(ht, "maine", 80);
    TestAdd(ht, "falco", 90);
    TestAdd(ht, "david", 91);
    TestAdd(ht, "lucy", 92);
    TestAdd(ht, "dorio", 93);
    TestAdd(ht, "pilar", 94);
    TestAdd(ht, "pilar", 94);
    TestSearch(ht, "maine");
    TestDelete(ht, "kiwi");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestAdd(ht, "maine", 100);
  }
  else if (testcase == 6) {
    HashTable ht(3, 3, ProbeMode::DoubleHash);
    TestAdd(ht, "kiwi", 60);
    TestAdd(ht, "rebecca", 70);
    TestAdd(ht, "maine", 80);
    TestAdd(ht, "falco", 90);
    TestAdd(ht, "david", 91);
    TestAdd(ht, "lucy", 92);
    TestAdd(ht, "dorio", 93);
    TestAdd(ht, "pilar", 94);
    TestAdd(ht, "pilar", 94);
    TestSearch(ht, "maine");
    TestDelete(ht, "kiwi");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestSearch(ht, "maine");
    TestDelete(ht, "maine");
    TestAdd(ht, "maine", 100);
  }
  return 0;
}
