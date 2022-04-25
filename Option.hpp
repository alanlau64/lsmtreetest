#ifndef OPTION_H
#define OPTION_H

#include <cstdint>

namespace Option {
    const bool COMPRESSION = true;
    const bool COMPACTION = true;
    const bool BLOCK_CACHE = true;
    const bool LEVELING = false;
    const uint64_t MEM_SPACE = (uint64_t) 2;
    const uint64_t NZ_NUM = 3;
    const uint64_t Z_SPACE = (uint64_t) 4;
    const uint64_t NZ_SPACES[] = {
        (uint64_t) 8,
        (uint64_t) 128 * 1024 * 1024,
        UINT64_MAX
    };
    const char *const Z_NAME = "/L0";
    const char *const NZ_NAMES[] = {"/L1", "/L2", "/L3"};
}

#endif
