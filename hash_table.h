#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <string>
class Student {
  public:
    Student(const std::string &name, int score)
        : name_(name), score_(score) {}
    Student(const Student &student)
        : name_(student.name()), score_(student.score()) {}

    const std::string& name() const {return name_;}
    int score() const {return score_;}

  private:
    std::string name_;
    int score_;
};

enum class HashCellState {
  Empty,
  Active,
  Deleted
};

struct HashCell {
  HashCell() = default;
  ~HashCell() {
    delete student;
    student = nullptr;
  }
  HashCellState state;
  Student *student;
};

enum class ProbeMode {
  Linear,
  Quadratic,
  DoubleHash
};

class HashTable {
  public:
    HashTable(int init_size, int maximum_probe_num,
              ProbeMode probe_mode);
    ~HashTable();

    bool add(const std::string &name, int score);
    int search(const std::string &name) const;
    bool remove(const std::string &name);

    static int hashFunction(const std::string &name, int base, int mod);
    static int getNextHashTableSize(int now_hash_table_size);
    void print() const;

  private:
    void reHashUntilSuccess();
    bool reHash(int rehash_table_size);

    HashCell *table_;

    int base_1_;
    int base_2_;

    int hash_table_size_;
    int maximum_probe_num_;
    ProbeMode probe_mode_;

    int (*probe_func_)(int hash_value1, int hash_value2, int num_probe, int hash_table_size);
};

#endif