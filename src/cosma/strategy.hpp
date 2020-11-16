#pragma once

#include <vector>

#include <cosma/defs.hpp>

namespace cosma {

struct Split {
    int divisor;
    Dimension dimension;
    bool parallel;

    bool is(Dimension d) const { return dimension == d; }
    bool is(Label l) const { return has(l, dimension); }
    Dimensions divisors() const {
        switch (dimension) {
        case dim::m:
            return {divisor, 1, 1};
        case dim::n:
            return {1, divisor, 1};
        case dim::k:
            return {1, 1, divisor};
        }
    }
};

struct Strategy {
    // matrix dimensions
    Dimensions dimensions;
    // number of processors
    int P;

    std::vector<Split> splits;

    bool should_overlap_comm_and_comp;

    // the strategy is considered irregular if any dimension
    // (at any step) is divided by a divisor that does not perfectly
    // divide that dimension
    bool irregular;
};

// TODO(Marko): add a family of make_strategy functions here

} // namespace cosma
