#include "SSTableId.hpp"

SSTableId::SSTableId(const std::string &dir,int no) :dir(dir),no(no) {}

std::string SSTableId::name() const {
    return dir + '/' + std::to_string(no);
}