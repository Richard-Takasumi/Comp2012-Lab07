#include "hash_table.h"
#include <cmath>
#include <iostream>

int HashTable::hashFunction(const std::string &name, int base, int table_size) {
  int res = 0;
  for (unsigned int i = 0; i < name.size(); i++) {
    res = (base*res + name[i] - 'a') % table_size;
  }
  return res;
}

int HashTable::getNextHashTableSize(int now_hash_table_size) {
  int res = now_hash_table_size*2;
  bool is_prime = false;
  while (true) {
    is_prime = true;
    int sq = sqrt(res);
    for (int i = 2; i <= sq; i++) {
      if (res % i == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime)
      break;
    res++;
  }
  return res;
}

HashTable::HashTable(int init_size, int maximum_probe_num,
                     ProbeMode probe_mode)  {  // Task 1
  this->base_1_ = 37;
  this->base_2_ = 41;
  this->hash_table_size_ = init_size;
  this->maximum_probe_num_ = maximum_probe_num;
  this->probe_mode_ = probe_mode;
  this->table_ = new HashCell[this->hash_table_size_]; 
  for (int i = 0; i < this->hash_table_size_; i++) {
    this->table_[i].state = HashCellState::Empty;
    this->table_[i].student = nullptr;
  }


  switch (this->probe_mode_) {
    case (ProbeMode::Linear) : 
      probe_func_ = [] (int hash_value1, int hash_value2, int num_probe, int hash_table_size) 
      { std::cout << "Probing for the position: " << 
      (hash_value1 + num_probe) % hash_table_size << std::endl;
      return (hash_value1 + num_probe) % hash_table_size;} ;
      break;

    case (ProbeMode::Quadratic): 
      probe_func_ = [] (int hash_value1, int hash_value2, int num_probe, int hash_table_size)
      { std::cout << "Probing for the position: " << 
      (hash_value1 + num_probe*num_probe) % hash_table_size << std::endl;
      return (hash_value1 + num_probe*num_probe) % hash_table_size;} ; 
      break;

    case (ProbeMode::DoubleHash): 
      probe_func_ = [] (int hash_value1, int hash_value2, int num_probe, int hash_table_size) 
      { std::cout << "Probing for the position: " << 
      (hash_value1 + num_probe*hash_value2) % hash_table_size << std::endl;
        return (hash_value1 + num_probe*hash_value2) % hash_table_size;} ;
      break;

    default:
      std::cerr << "error, probe_mode is invalid" << std::endl;
      break;

  }


}

HashTable::~HashTable() {  // Task 1
  delete[] this->table_;
}

bool HashTable::add(const std::string &name, int score) {  // Task 2 & 5
  int hash_value1 = this->hashFunction(name, this->base_1_, this->hash_table_size_);
  int hash_value2 = 0;
  if (probe_mode_ == ProbeMode::DoubleHash) {
    hash_value2 = this->hashFunction(name, this->base_2_, this->hash_table_size_);
    if (hash_value2 == 0) {
      hash_value2 = 1;
    }
  }
  
  // std::cout << "this->maximum_probe_num_: " << this->maximum_probe_num_ << std::endl;
  for (int i = 0; i < this->maximum_probe_num_ ; i++) {
    int probe_index = this->probe_func_(hash_value1, hash_value2, i, this->hash_table_size_);

    // if the student is already added to the table, we shouldn't try to add it again.
    if (this->table_[probe_index].state == HashCellState::Active 
    && this->table_[probe_index].student->name() == name ) {
      // std::cout << "here1" << std::endl;
      return false; 
    }
    // std::cout << "i: " << i << std::endl;
    if (this->table_[probe_index].state == HashCellState::Empty 
    || this->table_[probe_index].state == HashCellState::Deleted ) {
      
      this->table_[probe_index].state = HashCellState::Active;
      this->table_[probe_index].student = new Student(name, score);
      //  std::cout << "added: " << name << " to " << std::endl;
      return true;
    }
  };
  // std::cout << "here2" << std::endl;
  // now, the hash table should be the same, but expanded to fit more.
  reHashUntilSuccess();
  return add(name, score);
}

int HashTable::search(const std::string &name) const {  // Task 3
  int hash_value1 = this->hashFunction(name, this->base_1_, this->hash_table_size_);
  int hash_value2 = 0;
  if (probe_mode_ == ProbeMode::DoubleHash) {
    hash_value2 = this->hashFunction(name, this->base_2_, this->hash_table_size_);
    if (hash_value2 == 0) {
      hash_value2 = 1;
    }
  }
  
  // might need to change maximum_probe_num_ to hash_table_size_
  for (int i = 0; i < this->hash_table_size_ ; i++) {
    int probe_index = this->probe_func_(hash_value1, hash_value2, i, this->hash_table_size_);

    if (this->table_[probe_index].state == HashCellState::Empty) {
      return -1;
    }

    if (this->table_[probe_index].state == HashCellState::Active 
    && this->table_[probe_index].student->name() == name ) {
      // std::cout << "here1" << std::endl;
      return this->table_[probe_index].student->score(); 
    }
    // std::cout << "i: " << i << std::endl;
    if (this->table_[probe_index].state == HashCellState::Deleted ) {
      continue;
    }
  };
  // std::cout << "here2" << std::endl;
  return -1; 
}

bool HashTable::remove(const std::string &name) {  // Task 4
  int hash_value1 = this->hashFunction(name, this->base_1_, this->hash_table_size_);
  int hash_value2 = 0;
  if (probe_mode_ == ProbeMode::DoubleHash) {
    hash_value2 = this->hashFunction(name, this->base_2_, this->hash_table_size_);
    if (hash_value2 == 0) {
      hash_value2 = 1;
    }
  }
  // std::cout << "this->maximum_probe_num_: " << this->maximum_probe_num_ << std::endl;
  for (int i = 0; i < this->hash_table_size_ ; i++) {
    int probe_index = this->probe_func_(hash_value1, hash_value2, i, this->hash_table_size_);

    if (this->table_[probe_index].state == HashCellState::Empty) {
      return false;
    }

    if (this->table_[probe_index].state == HashCellState::Active 
    && this->table_[probe_index].student->name() == name ) {
      // std::cout << "here1" << std::endl;
      delete this->table_[probe_index].student;
      this->table_[probe_index].student = nullptr;
      this->table_[probe_index].state = HashCellState::Deleted;
      return true; 
    }
    // std::cout << "i: " << i << std::endl;
    if (this->table_[probe_index].state == HashCellState::Deleted ) {
      continue;
    }
  };
  // std::cout << "here2" << std::endl;
  return false; 
}

void HashTable::reHashUntilSuccess() {
  int next_hash_table_size = getNextHashTableSize(hash_table_size_);
  while (true) {
    if (reHash(next_hash_table_size)) {
      return;
    }
    next_hash_table_size = getNextHashTableSize(next_hash_table_size);
  }
}

bool HashTable::reHash(int rehash_table_size) {  // Task 5
  HashCell* temp_table = new HashCell[rehash_table_size];
  for (int i = 0; i < rehash_table_size; i++) {
    temp_table[i].state = HashCellState::Empty;
    temp_table[i].student = nullptr;
  }



  for (int i = 0; i < this->hash_table_size_; i++) {

    // search through entire old table, if the cell is active...
    if (this->table_[i].state == HashCellState::Active) {

      for (int j = 0; j < this->maximum_probe_num_; j++) {
        int hash_value1 = this->hashFunction(this->table_[i].student->name(), this->base_1_, rehash_table_size);
        int hash_value2 = 0;
        if (probe_mode_ == ProbeMode::DoubleHash) {
          hash_value2 = this->hashFunction(this->table_[i].student->name(), this->base_2_, rehash_table_size);
          if (hash_value2 == 0) {
            hash_value2 = 1;
          }
        }
        int probe_index = this->probe_func_(hash_value1, hash_value2, j, rehash_table_size);

        // if reaches last probe, and the probe index slot is full, it means unsuccessful rehash, delete temp_table and return false;      
        // otherwise, if not the last one, just continue;
        if (j+1 == this->maximum_probe_num_ && temp_table[probe_index].state == HashCellState::Active) {
            // std::cout << "deleting table: " << std::endl;
            delete[] temp_table;
            return false;
        } 

        if (temp_table[probe_index].state == HashCellState::Active) {
            continue;
        }


        // calculate probe
        // if temp_table[probe] is full
        // try again...
        // 


        if (temp_table[probe_index].state == HashCellState::Empty) {
          temp_table[probe_index].state = HashCellState::Active;
          temp_table[probe_index].student = new Student(this->table_[i].student->name(), this->table_[i].student->score());
          // std::cout << "added: " << this->table_[i].student->name() << " to index: " << probe_index << std::endl;
          break;
        }
      
      }

    }
    
  }
  // if reach here, it means rehashing is successful
  delete[] this->table_;
  this->table_ = temp_table;
  // std::cout << "increasing hash_table_size from: " << this->hash_table_size_ << " to: " << rehash_table_size << std::endl;
  this->hash_table_size_ = rehash_table_size;

  return true;
}

void HashTable::print() const {
  std::cout << "hash_table_size:" << hash_table_size_ << std::endl;
  for (int i = 0; i < hash_table_size_; i++) {
    std::cout << i << ": state = ";
    if (table_[i].state == HashCellState::Empty) {
      std::cout << "Empty" << std::endl;
    } 
    else if (table_[i].state == HashCellState::Deleted) {
      std::cout << "Deleted" << std::endl;
    } 
    else if (table_[i].state == HashCellState::Active) {
      std::cout << "Active ";
      std::cout << "Student = (" << table_[i].student->name() << ", "
                << table_[i].student->score() << ")" << std::endl;
    }
  }
}

