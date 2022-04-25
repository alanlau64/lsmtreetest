#ifndef LEVEL_ZERO_H
#define LEVEL_ZERO_H
#include "Value.hpp"
#include "SSTable.hpp"
#include <string>
#include <cstdint>
#include <vector>

class LevelZero {
public:
    explicit LevelZero(const std::string &dir);
    Value search(uint64_t key) const;
    void add(const std::map<int, Value> &mem, uint64_t &no);
    std::map<int, Value> extract();
    void clear();
    uint64_t space() const;
private:
    std::string dir;
    uint64_t size;
    uint64_t byteCnt;
    std::vector<SSTable> ssts;
    void save() const;

};

#endif