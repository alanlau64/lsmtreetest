#ifndef LEVEL_NON_ZERO_H
#define LEVEL_NON_ZERO_H

#include "SSTable.hpp"
#include <string>
#include <cstdint>
#include <vector>
#include <map>

class LevelNonZero {
public:
    explicit LevelNonZero(const std::string &dir);
    Value search(uint64_t key) const;
    std::map<int, Value> extract();
    void merge(std::map<int, Value> &&entries1, uint64_t &no);
    void clear();
    uint64_t space() const;
private:
    std::string dir;
    uint64_t size;
    uint64_t byteCnt;
    uint64_t lastKey;
    std::vector<SSTable> ssts;
    void save() const;
};

#endif