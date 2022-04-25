#ifndef UTIL_H
#define UTIL_H

#include "Value.hpp"
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <iostream>

namespace Util {
    inline std::map<int, Value> compact(const std::vector<std::map<int, Value> > &inputs) {
        size_t n = inputs.size();
        std::map<int, Value> ret;

        for (size_t i = 0; i < n; i++) {
            for (const auto &p : inputs[i]) {
                ret[p.first] = p.second;
            }
        }
        return ret;
    }
}

#endif
