#ifndef DISK_STORAGE_H
#define DISK_STORAGE_H

#include "Value.hpp"
#include "LevelZero.hpp"
#include "LevelNonZero.hpp"
#include <string>
#include <cstdint>
#include <vector>
#include <map>
#include <filesystem>
#include <fstream>

class DiskStorage {
public:
    explicit DiskStorage();
    explicit DiskStorage(const std::string &dir);
    void add(const std::map<int, Value> &mem);
    Value search(int key);
    void clear();
private:
    std::string dir;
    uint64_t no;
    LevelZero level0;
    std::vector<LevelNonZero> levels;
    void save() const;
};

#endif