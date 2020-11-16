#pragma once

#include <array>
#include <cassert>

namespace cosma {

enum class Label { A, B, C };

namespace dim {
    enum Dimension { m, n, k };
}
using dim::Dimension;

using Dimensions = std::array<int, 3>;

inline Dimension col(Label l) {
    switch(l) {
    case Label::A:
        return dim::k;
    case Label::B:
        return dim::n;
    case Label::C:
        return dim::n;
    }
    assert(false);
};

inline Dimension row(Label l) {
    switch(l) {
    case Label::A:
        return dim::m;
    case Label::B:
        return dim::k;
    case Label::C:
        return dim::m;
    }
    assert(false);
};

inline bool has(Label l, Dimension d) {
    return col(l) == d || row(l) == d;
}

}