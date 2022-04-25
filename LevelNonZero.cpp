#include "LevelNonZero.hpp"
#include "Util.hpp"
#include "SSTableId.hpp"
#include "Value.hpp"
#include "Option.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>


LevelNonZero::LevelNonZero(const std::string &dir): dir(dir) {
    if (!std::__fs::filesystem::exists(std::__fs::filesystem::path(dir))) {
        std::__fs::filesystem::create_directories(std::__fs::filesystem::path(dir));
        size = 0;
        byteCnt = 0;
        lastKey = 0;
        save();
    } 
    else {
        std::ifstream ifs(dir + "/index", std::ios::binary);
        ifs.read((char*) &size, sizeof(uint64_t));
        ifs.read((char*) &byteCnt, sizeof(uint64_t));
        ifs.read((char*) &lastKey, sizeof(uint64_t));
        for (uint64_t i = 0; i < size; ++i) {
            uint64_t no;
            ifs.read((char*) &no, sizeof(uint64_t));
            ssts.emplace_back(SSTableId(dir, no));
        }
        ifs.close();
    }
}

Value LevelNonZero::search(uint64_t key) const {
    for (uint64_t i = 1; i <= size; ++i) {
        Value res = ssts[size - i].search(key);
        if (res.visible)
            return res;
    }
    return {false};
}

std::map<int, Value> LevelNonZero::extract() {
    std::map<int, Value> ret;
    if (Option::LEVELING) {
        auto itr = ssts.begin();
        ret = itr->load();
        clear();
    }
    else {
        auto itr = ssts.begin();
        while (itr != ssts.end() && itr->load().rbegin()->first <= lastKey)
            ++itr;
        if (itr == ssts.end())
            itr = ssts.begin();
        byteCnt -= itr->getSpace();
        lastKey = itr->load().rbegin()->first;
        ret = itr->load();
        itr->remove();
        ssts.erase(itr);
        --size;
    }
    save();
    return ret;
}

void LevelNonZero::merge(std::map<int, Value> &&entries1, uint64_t &no) {
    if (Option::LEVELING) {
        if (size) {
            std::map<int, Value> entries = ssts.begin()->load();
            std::vector<std::map<int, Value>> v;
            v.emplace_back(entries);
            v.emplace_back(entries1);
            clear();
            ssts.insert(ssts.begin(), SSTable(Util::compact(v), SSTableId(dir, no++)));
        }
        else {
            ssts.emplace_back(entries1, SSTableId(dir, no++));
        }
        byteCnt = ssts.begin()->getSpace();
        size = 1;
    }
    else {
        ssts.emplace_back(entries1, SSTableId(dir, no++));
        ++size;
        byteCnt += entries1.size();
    }
    save();
}

void LevelNonZero::clear() {
    while (!ssts.empty()) {
        ssts.back().remove();
        ssts.pop_back();
    }
    size = 0;
    byteCnt = 0;
    lastKey = 0;
    save();
}

uint64_t LevelNonZero::space() const {
    return byteCnt;
}

void LevelNonZero::save() const {
    std::ofstream ofs(dir + "/index", std::ios::binary);
    ofs.write((char*) &size, sizeof(uint64_t));
    ofs.write((char*) &byteCnt, sizeof(uint64_t));
    ofs.write((char*) &lastKey, sizeof(uint64_t));
    for (const SSTable &sst : ssts) {
        uint64_t no = sst.number();
        ofs.write((char*) &no, sizeof(uint64_t));
    }
    ofs.close();
}