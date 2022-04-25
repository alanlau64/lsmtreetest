#ifndef SSTABLE_ID_H
#define SSTABLE_ID_H

#include <string>

struct SSTableId {
    std::string dir;
    int no;
    SSTableId() = default;
    SSTableId(const std::string &dir, int no);
    std::string name() const;
};

#endif