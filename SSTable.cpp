#include "SSTable.hpp"
#include <fstream>
#include <filesystem>
#include <vector>

#include <iostream>
#include <string>

using std::ofstream;
using std::ifstream;


SSTable::SSTable(const SSTableId &id)
    : sstbId(id){
}

SSTable::SSTable(const std::map<int, Value> &entries, const SSTableId &id)
    : sstbId(id),space(entries.size()){
    save(entries);
}


Value SSTable::search(int key) const {
    std::map<int, Value> entries = load();
    if (entries.count(key)) {
        return entries[key];
    }
    return Value(false);
}

std::map<int, Value> SSTable::load() const {
    std::map<int, Value> entries;
    ifstream file(sstbId.name());

    std::string line, item, op_string, key_str, visible_str,timestamp_str;
    while (std::getline(file, line))
    {
        std::vector<int> items = std::vector<int>();

        Value v;

        std::stringstream linestream(line);
        std::getline(linestream, key_str, ' '); // First argument is a key
        std::getline(linestream, visible_str, ' '); // Second argument is if visible
        int key = stoi(key_str);
        int ifVisible = stoi(visible_str);

        if (ifVisible == 0){
            v.visible = false;
        } else{
            v.visible = true;
            std::getline(linestream, timestamp_str, ' '); // Third argument is timestamp
            unsigned long int t = stoi(timestamp_str);
            v.timestamp = t;
            while(std::getline(linestream, item, ' '))
            {
                items.push_back(stoi(item));
            }
            v.items = items;
        }

        entries[key] = v;
        // std::cout << key << std::endl;
    }
    return entries;
}


int SSTable::getSpace() const {
    return space;
}

void SSTable::remove() const {
    std::filesystem::remove(std::filesystem::path(sstbId.name()));
}

uint64_t SSTable::number() const {
    return sstbId.no;
}

void SSTable::save(const std::map<int, Value> &entries) {
    std::ofstream file(sstbId.name());
    for (const auto &i : entries) {
        file << i.first << ' ';
        if(i.second.visible){
            file << 1 << ' '; //Visible == True
        } else{
            file << 0 << ' ';
        }
        file << i.second.timestamp << ' ';
        for (const auto &j : i.second.items){
            file << j<< ' ';
        }
        file << std::endl;
    }
}