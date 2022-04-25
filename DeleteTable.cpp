//
// Created by Junchen Liu on 4/24/2022.
//

#include "DeleteTable.h"
#include <filesystem>
#include <fstream>

DeleteTable::DeleteTable() {
    //Find if there exist dt file, if so load
    if (std::filesystem::exists(std::filesystem::path(fileName))){
        this->load();
    }
}

void DeleteTable::del(int min_key, int max_key){
    vec.emplace_back(min_key,max_key);
}

unsigned long int DeleteTable::getTimeInt(int key) {
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
    {
        if(key < it->maxKey && key > it->minKey){
            return it->t;
        }
    }
    return 0;
}

void DeleteTable::close() {
    this->save();
}

void DeleteTable::load() {
    ifstream file(fileName);
    std::string line, item, op_string, min_str, max_str,timestamp_str;
    while (std::getline(file, line))
    {
        std::stringstream linestream(line);
        std::getline(linestream, min_str, ' '); // First argument is a key
        std::getline(linestream, max_str, ' '); // Second argument is if visible
        std::getline(linestream, timestamp_str, ' '); // Second argument is if visible
        int min_key = stoi(min_str);
        int max_key = stoi(max_str);
        unsigned long int t = stoi(timestamp_str);

        vec.emplace_back(min_key,max_key,t);
    }
}

void DeleteTable::save() {
    std::ofstream file(fileName);
    for (const auto &i : vec) {
        file << i.minKey << ' ' << i.maxKey << ' '<< i.t << ' ' << std::endl;
    }
}



