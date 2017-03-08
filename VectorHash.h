//
// Created by kamil on 11.01.17.
//

#pragma once

#include <unordered_set>
#include <vector>

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};
using CyclesSet = std::unordered_set<std::vector<int>, VectorHash>;